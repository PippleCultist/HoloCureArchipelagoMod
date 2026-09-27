#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "CommonFunctions.h"
#include "CodeEvents.h"
#include "ScriptFunctions.h"
#include "ArchipelagoMenu.h"
#include <random>
#include <queue>
#include <numbers>
#include <unordered_set>

#include "APCpp/Archipelago.h"
#include "Constants.h"

extern CallbackManagerInterface* callbackManagerInterfacePtr;
extern std::unordered_map<itemIndexEnum, int> curObtainedItems;
extern std::deque<itemIndexEnum> itemIndexReceiveQueue;
extern std::unordered_set<locationIndexEnum> obtainedLocationSet;
extern std::map<locationIndexEnum, std::string> locationToNameMap;
extern std::unordered_set<locationIndexEnum> grindyLocations;
extern std::unordered_set<locationIndexEnum> stageLocations;
extern std::unordered_map<goalIndexEnum, std::unordered_set<locationIndexEnum>> goalIndexToLocationListMap;
extern std::unordered_set<locationIndexEnum> holoHouseRandomizationLocations;
extern std::unordered_map<itemIndexEnum, std::string> holoHouseItemToIDMap;
extern std::unordered_set<locationIndexEnum> enemyCheckLocations;
extern std::unordered_set<std::string> hololiveMemberWhiteList;
extern std::map<locationIndexEnum, std::vector<std::string>> locationToCharacterNameMap;

extern std::string apPlayerName;
extern bool newConnectSendChecks;
extern bool isGrindyChecksEnabled;
extern bool isStageEnabled;
extern bool isHoloHouseRandomizationEnabled;
extern bool isUniqueEnemyCheckEnabled;
extern bool is2xStageTimer;
extern int hololiveMemberGoal;
extern int achievementGoal;
extern int endGoal;

std::random_device rd;
std::default_random_engine randomGenerator(rd());

std::unordered_map<locationIndexEnum, AP_NetworkItem> locationItemHintMap;

void TitleScreenCreateBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
}

bool hasSentGoal = false;
int locationHintTimer = 300;
bool hasLoadedSave = false;
int serverSaveIDRequestTimer = -1;
int serverSaveID = 0;
AP_GetServerDataRequest saveIDRequest;

void InputManagerStepBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	bool hasUpdated = false;
	CInstance* Self = std::get<0>(Args);

	if (AP_GetConnectionStatus() == AP_ConnectionStatus::Authenticated)
	{
		if (locationItemHintMap.empty())
		{
			locationHintTimer++;
			if (locationHintTimer >= 300)
			{
				std::set<int64_t> locations;

				for (auto& locationPair : locationToNameMap)
				{
					if (!isGrindyChecksEnabled && grindyLocations.contains(locationPair.first))
					{
						continue;
					}
					if (!isStageEnabled && (endGoal != goalIndexEnum_BeatAllNormalStages && endGoal != goalIndexEnum_BeatAllHardStages) && (stageLocations.contains(locationPair.first) || enemyCheckLocations.contains(locationPair.first)))
					{
						continue;
					}
					if (!isHoloHouseRandomizationEnabled && holoHouseRandomizationLocations.contains(locationPair.first))
					{
						continue;
					}
					if (!isUniqueEnemyCheckEnabled && enemyCheckLocations.contains(locationPair.first))
					{
						continue;
					}
					if (!hololiveMemberWhiteList.empty() && hololiveMemberWhiteList.size() != 47 && locationToCharacterNameMap.contains(locationPair.first))
					{
						bool isInWhiteList = false;
						for (auto& curCharName : locationToCharacterNameMap[locationPair.first])
						{
							if (hololiveMemberWhiteList.contains(curCharName))
							{
								isInWhiteList = true;
								break;
							}
						}

						if (!isInWhiteList)
						{
							continue;
						}
					}
					locations.insert(locationPair.first);
				}

				callbackManagerInterfacePtr->LogToFile(MODNAME, "Send location scout");

				AP_SendLocationScouts(locations, 0);
				locationHintTimer = 0;
			}
		}
		
		if (!hasLoadedSave)
		{
			if (serverSaveIDRequestTimer == -1)
			{
				saveIDRequest.key = "HoloCureArchipelagoModSave" + std::to_string(AP_GetPlayerID());
				saveIDRequest.type = AP_DataType::Int;
				saveIDRequest.value = &serverSaveID;

				AP_GetServerData(&saveIDRequest);
			}
			serverSaveIDRequestTimer++;
			if (serverSaveIDRequestTimer >= 60)
			{
				if (saveIDRequest.status == AP_RequestStatus::Done)
				{
					if (serverSaveID == 0)
					{
						AP_SetServerDataRequest serverSaveIDSetRequest;
						RValue saveDir;
						g_ModuleInterface->GetBuiltin("game_save_id", nullptr, NULL_INDEX, saveDir);
						std::set<int> saveIndexSet;
						for (const auto& dir : std::filesystem::directory_iterator(saveDir.ToString()))
						{
							if (dir.is_regular_file())
							{
								std::string fileName = dir.path().filename().string();
								int firstIndex = fileName.find_first_of('_');
								int lastIndex = fileName.find_last_of('_');
								if (apPlayerName.compare(fileName.substr(firstIndex + 1, lastIndex - firstIndex - 1)) == 0)
								{
									saveIndexSet.insert(stoi(fileName.substr(lastIndex + 1, fileName.size() - 5)));
								}
							}
						}
						
						int minSaveIndex = 1;
						for (auto curIndex : saveIndexSet)
						{
							if (curIndex != minSaveIndex)
							{
								break;
							}
							minSaveIndex++;
						}
						serverSaveID = minSaveIndex;
						std::string apSaveName = std::format("ArchipelagoSave_{}_{}.dat", apPlayerName, minSaveIndex);
						loggingCallback(std::format("Server save not found. Creating new save {}", apSaveName));

						serverSaveIDSetRequest.key = "HoloCureArchipelagoModSave" + std::to_string(AP_GetPlayerID());
						serverSaveIDSetRequest.operations = { { "replace", &serverSaveID } };
						serverSaveIDSetRequest.default_value = 0;
						serverSaveIDSetRequest.type = AP_DataType::Int;
						serverSaveIDSetRequest.want_reply = false;

						AP_SetServerData(&serverSaveIDSetRequest);
					}
					else
					{
						std::string apSaveName = std::format("ArchipelagoSave_{}_{}.dat", apPlayerName, serverSaveID);
						RValue result;
						RValue saveName[1];
						saveName[0] = apSaveName.c_str();
						origFileExistsFunc(result, Self, nullptr, 1, saveName);
						if (result.ToBoolean())
						{
							loggingCallback(std::format("Loading save {}", apSaveName));
							RValue** args = new RValue * [1];
							RValue saveName = apSaveName.c_str();
							args[0] = &saveName;
							origNewDSMapMapSecureLoadScript(Self, nullptr, result, 1, args);
							g_ModuleInterface->CallBuiltin("variable_global_set", { "PlayerSave", result });
						}
						else
						{
							loggingCallback(std::format("{} not found. Creating new save", apSaveName));
							origSavePlayerSaveScript(Self, nullptr, result, 0, nullptr);
						}
					}
					hasLoadedSave = true;
				}
				else if (saveIDRequest.status == AP_RequestStatus::Error)
				{
					loggingCallback(std::format("Failed to get server save id. Retrying..."));
					saveIDRequest.key = "HoloCureArchipelagoModSave" + std::to_string(AP_GetPlayerID());
					saveIDRequest.type = AP_DataType::Int;
					saveIDRequest.value = &serverSaveID;

					AP_GetServerData(&saveIDRequest);
				}
				serverSaveIDRequestTimer = 0;
			}
		}
		else
		{
			if (newConnectSendChecks)
			{
				RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
				RValue archipelagoChecks = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "archipelagoChecks" });
				if (archipelagoChecks.m_Kind != VALUE_UNDEFINED)
				{
					RValue apCheckArr = g_ModuleInterface->CallBuiltin("struct_get_names", { archipelagoChecks });
					int arrLen = g_ModuleInterface->CallBuiltin("array_length", { apCheckArr }).ToInt32();
					for (int i = 0; i < arrLen; i++)
					{
						sendAPCheck(Self, static_cast<locationIndexEnum>(std::stoi(apCheckArr[i].ToString().substr(3))));
					}
				}
				newConnectSendChecks = false;
			}

			if (endGoal != -1)
			{
				auto& curGoalLocations = goalIndexToLocationListMap[static_cast<goalIndexEnum>(endGoal)];
				bool isGoalReached = true;
				if (endGoal == goalIndexEnum_HololiveMemberStageClear || endGoal == goalIndexEnum_Achievement)
				{
					int obtainedLocationCount = 0;
					for (auto curLocation : curGoalLocations)
					{
						if (obtainedLocationSet.contains(curLocation))
						{
							obtainedLocationCount++;
						}
					}
					if (endGoal == goalIndexEnum_HololiveMemberStageClear)
					{
						isGoalReached = obtainedLocationCount >= hololiveMemberGoal;
					}
					else if (endGoal == goalIndexEnum_Achievement)
					{
						isGoalReached = obtainedLocationCount >= achievementGoal;
					}
				}
				else
				{
					for (auto curLocation : curGoalLocations)
					{
						if (!obtainedLocationSet.contains(curLocation))
						{
							isGoalReached = false;
							break;
						}
					}
				}
				
				if (isGoalReached)
				{
					if (!hasSentGoal)
					{
						AP_StoryComplete();
						hasSentGoal = true;
					}
				}
			}

			// TODO: Only do a few at a time to prevent freezing

			while (!itemIndexReceiveQueue.empty())
			{
				itemIndexEnum itemID = itemIndexReceiveQueue.front();
				itemIndexReceiveQueue.pop_front();
				if (!curObtainedItems.contains(itemID))
				{
					curObtainedItems[itemID] = 1;
				}
				else
				{
					curObtainedItems[itemID]++;
				}
				RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
				RValue archipelagoItems = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "archipelagoItems" });
				int savedItemCount = 0;
				if (archipelagoItems.m_Kind == VALUE_UNDEFINED)
				{
					RValue apItemStruct;
					g_RunnerInterface.StructCreate(&apItemStruct);
					g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "archipelagoItems", apItemStruct });
					archipelagoItems = apItemStruct;
				}
				else
				{
					RValue apItemStruct = g_ModuleInterface->CallBuiltin("struct_get", { archipelagoItems, std::format("ap_{}", static_cast<int>(itemID)).c_str() });
					if (apItemStruct.m_Kind != VALUE_UNDEFINED)
					{
						savedItemCount = apItemStruct.ToInt32();
					}
				}

				bool hasObtained = (savedItemCount >= curObtainedItems[itemID]);

				if (!hasObtained)
				{
					g_ModuleInterface->CallBuiltin("struct_set", { archipelagoItems, std::format("ap_{}", static_cast<int>(itemID)).c_str(), curObtainedItems[itemID] });
					if (itemID >= itemIndexEnum_HoloHouse && itemID <= itemIndexEnum_TimeStage1)
					{
						// Stages + HoloCoin
						if (itemID == itemIndexEnum_HoloCoin)
						{
							int holoCoins = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "holoCoins" }).ToInt32();
							g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "holoCoins", holoCoins + 1000 });
						}
						else if (itemID == itemIndexEnum_ProgressiveStage || itemID == itemIndexEnum_ProgressiveStageHard)
						{
							RValue** args = new RValue * [3];
							RValue unlockedStages = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "unlockedStages" });
							RValue stageName;
							bool isUnlock = true;

							if (itemID == itemIndexEnum_ProgressiveStage)
							{
								if (curObtainedItems[itemID] >= 1 && curObtainedItems[itemID] <= 5)
								{
									stageName = std::format("STAGE {}", curObtainedItems[itemID]).c_str();
								}
								else
								{
									isUnlock = false;
								}
							}
							else
							{
								if (curObtainedItems[itemID] >= 1 && curObtainedItems[itemID] <= 4)
								{
									stageName = std::format("STAGE {} (HARD)", curObtainedItems[itemID]).c_str();
								}
								else
								{
									isUnlock = false;
								}
							}

							if (isUnlock)
							{
								RValue stageStr = "STAGE";
								args[0] = &unlockedStages;
								args[1] = &stageName;
								args[2] = &stageStr;
								RValue result;
								origUnlockThingScript(Self, nullptr, result, 3, args);
							}
							else
							{
								int holoCoins = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "holoCoins" }).ToInt32();
								g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "holoCoins", holoCoins + 1000 });
							}
						}
						else if (itemID == itemIndexEnum_HoloHouse)
						{
							RValue** args = new RValue * [3];
							RValue unlockedStages = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "unlockedStages" });
							RValue stageName = "HOLO HOUSE";
							RValue stageStr = "STAGE";
							args[0] = &unlockedStages;
							args[1] = &stageName;
							args[2] = &stageStr;
							RValue result;
							origUnlockThingScript(Self, nullptr, result, 3, args);
						}
						else if (itemID == itemIndexEnum_TimeStage1)
						{
							RValue** args = new RValue * [3];
							RValue unlockedStages = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "unlockedStages" });
							g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "timeModeUnlocked", true });
							RValue stageName = "TIME STAGE 1";
							RValue stageStr = "STAGE";
							args[0] = &unlockedStages;
							args[1] = &stageName;
							args[2] = &stageStr;
							RValue result;
							origUnlockThingScript(Self, nullptr, result, 3, args);
						}
					}
					else if (itemID >= itemIndexEnum_AmeliaWatson && itemID <= itemIndexEnum_HimemoriLuna)
					{
						// Characters
						RValue charArr = g_ModuleInterface->CallBuiltin("array_create", { 2 });
						RValue characterList = g_ModuleInterface->CallBuiltin("variable_global_get", { "characterList" });
						charArr[0] = characterList[itemID - itemIndexEnum_AmeliaWatson];
						charArr[1] = 1;
						RValue characters = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "characters" });
						g_ModuleInterface->CallBuiltin("array_push", { characters, charArr });
					}
					else if (itemID >= itemIndexEnum_WamyWater && itemID <= itemIndexEnum_OwlDagger)
					{
						// Weapons
						RValue** args = new RValue * [3];
						RValue unlockedWeapons = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "unlockedWeapons" });
						RValue weaponName = weaponToIDMap[itemID].c_str();
						RValue weaponStr = "WEAPON";
						args[0] = &unlockedWeapons;
						args[1] = &weaponName;
						args[2] = &weaponStr;
						RValue result;
						origUnlockThingScript(Self, nullptr, result, 3, args);
					}
					else if (itemID >= itemIndexEnum_EnergyDrink && itemID <= itemIndexEnum_PromiseTiara)
					{
						// Items
						RValue** args = new RValue * [3];
						RValue unlockedItems = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "unlockedItems" });
						RValue itemName = itemToIDMap[itemID].c_str();
						RValue itemStr = "ITEM";
						args[0] = &unlockedItems;
						args[1] = &itemName;
						args[2] = &itemStr;
						RValue result;
						origUnlockThingScript(Self, nullptr, result, 3, args);
					}
					else if (itemID >= itemIndexEnum_SpecialAttackShopUpgrade && itemID <= itemIndexEnum_MarketingProgressiveShopUpgrade)
					{
						int saveLevel = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, shopToIDMap[itemID].c_str() }).ToInt32();
						g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, shopToIDMap[itemID].c_str(), saveLevel + 1 });
					}
					else if (itemID >= itemIndexEnum_StandardSoil && itemID <= itemIndexEnum_GarlicSeed)
					{
						RValue AP_unlockedFarm = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "AP_unlockedFarm" });
						if (AP_unlockedFarm.m_Kind == VALUE_UNDEFINED)
						{
							g_RunnerInterface.StructCreate(&AP_unlockedFarm);
							g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "AP_unlockedFarm", AP_unlockedFarm });
						}
						g_ModuleInterface->CallBuiltin("struct_set", { AP_unlockedFarm, holoHouseItemToIDMap[itemID].c_str(), true});
					}
					else if (itemID >= itemIndexEnum_ProgressiveRod && itemID <= itemIndexEnum_ProgressivePickaxe)
					{
						switch (itemID)
						{
							case itemIndexEnum_ProgressiveRod:
							{
								RValue rodUnlock = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "rodUnlock" });
								rodUnlock[curObtainedItems[itemID]] = true;
								break;
							}
							case itemIndexEnum_ProgressiveAxe:
							{
								g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "usingAxe", curObtainedItems[itemID] });
								break;
							}
							case itemIndexEnum_ProgressivePickaxe:
							{
								g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "usingPick", curObtainedItems[itemID] });
								break;
							}
						}
					}
					hasUpdated = true;
				}
			}
			if (hasUpdated)
			{
				RValue result;
				origSavePlayerSaveScript(Self, nullptr, result, 0, nullptr);
			}
		}
	}

	renderImguiWindow(Self);
}

void CharSelectCreateAfter(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	CInstance* Self = std::get<0>(Args);
	RValue charInfo = getInstanceVariable(Self, GML_characterInfo);
	RValue charListByGen = getInstanceVariable(Self, GML_charListByGen);
	RValue empty = g_ModuleInterface->CallBuiltin("ds_map_find_value", { g_ModuleInterface->CallBuiltin("variable_global_get", { "characterData" }), "empty" });
	// TODO: Populate curObtainedItems with save data when game loads
	if (!curObtainedItems.contains(itemIndexEnum_AmeliaWatson))
	{
		charInfo[itemIndexEnum_AmeliaWatson - itemIndexEnum_AmeliaWatson] = empty;
		charListByGen[0][itemIndexEnum_AmeliaWatson - itemIndexEnum_AmeliaWatson] = empty;
	}
	if (!curObtainedItems.contains(itemIndexEnum_GawrGura))
	{
		charInfo[itemIndexEnum_GawrGura - itemIndexEnum_AmeliaWatson] = empty;
		charListByGen[0][itemIndexEnum_GawrGura - itemIndexEnum_AmeliaWatson] = empty;
	}
	if (!curObtainedItems.contains(itemIndexEnum_NinomaeInanis))
	{
		charInfo[itemIndexEnum_NinomaeInanis - itemIndexEnum_AmeliaWatson] = empty;
		charListByGen[0][itemIndexEnum_NinomaeInanis - itemIndexEnum_AmeliaWatson] = empty;
	}
	if (!curObtainedItems.contains(itemIndexEnum_TakanashiKiara))
	{
		charInfo[itemIndexEnum_TakanashiKiara - itemIndexEnum_AmeliaWatson] = empty;
		charListByGen[0][itemIndexEnum_TakanashiKiara - itemIndexEnum_AmeliaWatson] = empty;
	}
	if (!curObtainedItems.contains(itemIndexEnum_MoriCalliope))
	{
		charInfo[itemIndexEnum_MoriCalliope - itemIndexEnum_AmeliaWatson] = empty;
		charListByGen[0][itemIndexEnum_MoriCalliope - itemIndexEnum_AmeliaWatson] = empty;
	}
}

void AchievementsOther10After(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	CInstance* Self = std::get<0>(Args);
	RValue achievementMap = getInstanceVariable(Self, GML_ACHIEVEMENTS);
	RValue achievementArr = g_ModuleInterface->CallBuiltin("ds_map_values_to_array", { achievementMap });
	int arrLen = g_ModuleInterface->CallBuiltin("array_length", { achievementArr }).ToInt32();
	for (int i = 0; i < arrLen; i++)
	{
		RValue curAchievement = achievementArr[i];
		RValue curReward = getInstanceVariable(curAchievement, GML_reward);
		if (curReward.m_Kind == VALUE_ARRAY)
		{
			curReward[1] = 0;
		}
	}
}

void ShopCreateAfter(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	CInstance* Self = std::get<0>(Args);
	RValue shopItems = getInstanceVariable(Self, GML_shopItems);
	RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
	int arrLen = g_ModuleInterface->CallBuiltin("array_length", { shopItems }).ToInt32();
	for (int i = 0; i < arrLen; i++)
	{
		RValue optionID = getInstanceVariable(shopItems[i], GML_optionID);
		if (!shopIDToIndexMap.contains(optionID.ToCString()))
		{
			continue;
		}
		RValue newOptionID = std::format("AP_{}", optionID.ToCString()).c_str();
		RValue shopItemData = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, newOptionID });
		if (shopItemData.m_Kind == VALUE_UNDEFINED)
		{
			g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, newOptionID, 0 });
		}
		setInstanceVariable(shopItems[i], GML_optionID, newOptionID);
	}
	RValue result;
	origSavePlayerSaveScript(Self, nullptr, result, 0, nullptr);
}

void PlayerManagerStepBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	if (is2xStageTimer)
	{
		RValue timePause = g_ModuleInterface->CallBuiltin("variable_global_get", { "timePause" });
		if (!timePause.ToBoolean())
		{
			RValue timeArr = g_ModuleInterface->CallBuiltin("variable_global_get", { "time" });
			timeArr[3] = timeArr[3].ToInt32() + 1;
		}
	}
}