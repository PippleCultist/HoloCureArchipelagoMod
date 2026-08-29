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

extern CallbackManagerInterface* callbackManagerInterfacePtr;
extern std::unordered_map<itemIndexEnum, int> curObtainedItems;
extern std::deque<itemIndexEnum> itemIndexReceiveQueue;
extern std::unordered_set<locationIndexEnum> obtainedLocationSet;

extern bool newConnectSendChecks;

std::unordered_map<itemIndexEnum, std::string> weaponToIDMap
{
	{ itemIndexEnum_WamyWater, "WamyWater" },
	{ itemIndexEnum_PsychoAxe, "PsychoAxe" },
	{ itemIndexEnum_XPotato, "XPotato" },
	{ itemIndexEnum_BounceBall, "BounceBall" },
	{ itemIndexEnum_Sausage, "Sausage" },
	{ itemIndexEnum_Glowstick, "Glowstick" },
	{ itemIndexEnum_SpiderCooking, "SpiderCooking" },
	{ itemIndexEnum_PlugTypeAsacoco, "Tailplug" },
	{ itemIndexEnum_BLBook, "BLBook" },
	{ itemIndexEnum_EliteLava, "EliteLava" },
	{ itemIndexEnum_HoloBomb, "HoloBomb" },
	{ itemIndexEnum_CuttingBoard, "CuttingBoard" },
	{ itemIndexEnum_FanBeam, "HoloLaser" },
	{ itemIndexEnum_IdolSong, "IdolSong" },
	{ itemIndexEnum_CEOTears, "CEOTears" },
	{ itemIndexEnum_ENCurse, "ENCurse" },
	{ itemIndexEnum_OwlDagger, "OwlDagger" },
};

std::unordered_map<itemIndexEnum, std::string> itemToIDMap
{
	{ itemIndexEnum_EnergyDrink, "EnergyDrink" },
	{ itemIndexEnum_Plushie, "Plushie" },
	{ itemIndexEnum_Limiter, "Limiter" },
	{ itemIndexEnum_Beetle, "Beetle" },
	{ itemIndexEnum_Shackles, "Shacklesss" },
	{ itemIndexEnum_NinjaHeadband, "NinjaHeadband" },
	{ itemIndexEnum_ChickenFeather, "ChickensFeather" },
	{ itemIndexEnum_RavenFeather, "RavenFeather" },
	{ itemIndexEnum_BodyPillow, "BodyPillow" },
	{ itemIndexEnum_FullMeal, "FullMeal" },
	{ itemIndexEnum_PikiPikiPiman, "PikiPikiPiman" },
	{ itemIndexEnum_NurseHorn, "SuccubusHorn" },
	{ itemIndexEnum_Headphones, "Headphones" },
	{ itemIndexEnum_UberSheep, "UberSheep" },
	{ itemIndexEnum_KnightlyMilk, "HolyMilk" },
	{ itemIndexEnum_Sake, "Sake" },
	{ itemIndexEnum_FaceMask, "FaceMask" },
	{ itemIndexEnum_CreditCard, "CreditCard" },
	{ itemIndexEnum_GorillaPaw, "GorillasPaw" },
	{ itemIndexEnum_SuperChattoTime, "SuperChattoTime" },
	{ itemIndexEnum_Halu, "Halu" },
	{ itemIndexEnum_InjectionTypeAsacoco, "InjectionAsacoco" },
	{ itemIndexEnum_IdolCostume, "IdolCostume" },
	{ itemIndexEnum_GWSPill, "GWSPill" },
	{ itemIndexEnum_JustBandage, "Bandaid" },
	{ itemIndexEnum_Breastplate, "Breastplate" },
	{ itemIndexEnum_StudyGlasses, "StudyGlasses" },
	{ itemIndexEnum_BlacksmithGear, "BlacksmithsGear" },
	{ itemIndexEnum_HopeSoda, "HopeSoda" },
	{ itemIndexEnum_StolenPiggyBank, "PiggyBank" },
	{ itemIndexEnum_CandyKingdomSweets, "Candy" },
	{ itemIndexEnum_ResearcherCoat, "LabCoat" },
	{ itemIndexEnum_Membership, "Membership" },
	{ itemIndexEnum_DevilHat, "DevilHat" },
	{ itemIndexEnum_FocusShades, "FocusShades" },
	{ itemIndexEnum_CorporationPin, "CorporationPin" },
	{ itemIndexEnum_PromiseTiara, "PromiseTiara" },
};

std::unordered_map<itemIndexEnum, std::string> shopToIDMap
{
	{ itemIndexEnum_SpecialAttackShopUpgrade, "specUnlock" },
	{ itemIndexEnum_GrowthProgressiveShopUpgrade, "growth" },
	{ itemIndexEnum_RerollProgressiveShopUpgrade, "reroll" },
	{ itemIndexEnum_EliminateProgressiveShopUpgrade, "eliminate" },
	{ itemIndexEnum_HoldProgressiveShopUpgrade, "holdOption" },
	{ itemIndexEnum_CustomizeShopUpgrade, "canDisable" },
	{ itemIndexEnum_SupportsShopUpgrade, "supports" },
	{ itemIndexEnum_MaterialShopUpgrade, "materialDrops" },
	{ itemIndexEnum_StampsShopUpgrade, "stamps" },
	{ itemIndexEnum_EnchantmentsShopUpgrade, "enchantments" },
	{ itemIndexEnum_FandomShopUpgrade, "fandom" },
	{ itemIndexEnum_FanLettersShopUpgrade, "fanLetterUnlock" },
	{ itemIndexEnum_MaxHPProgressiveShopUpgrade, "HP" },
	{ itemIndexEnum_ATKProgressiveShopUpgrade, "ATK" },
	{ itemIndexEnum_SPDProgressiveShopUpgrade, "SPD" },
	{ itemIndexEnum_CritProgressiveShopUpgrade, "crit" },
	{ itemIndexEnum_PickUpProgressiveShopUpgrade, "pickupRange" },
	{ itemIndexEnum_HasteProgressiveShopUpgrade, "haste" },
	{ itemIndexEnum_RegenProgressiveShopUpgrade, "regen" },
	{ itemIndexEnum_DefenseProgressiveShopUpgrade, "DR" },
	{ itemIndexEnum_SpecialCooldownProgressiveShopUpgrade, "specCDR" },
	{ itemIndexEnum_SkillUpProgressiveShopUpgrade, "skillDamage" },
	{ itemIndexEnum_EXPGainProgressiveShopUpgrade, "EXP" },
	{ itemIndexEnum_FoodDropProgressiveShopUpgrade, "food" },
	{ itemIndexEnum_MoneyGainProgressiveShopUpgrade, "moneyGain" },
	{ itemIndexEnum_EnhancementProgressiveShopUpgrade, "enhanceUp" },
	{ itemIndexEnum_MarketingProgressiveShopUpgrade, "mobUp" },
};

std::unordered_map<std::string, itemIndexEnum> shopIDToIndexMap
{
	{ "specUnlock", itemIndexEnum_SpecialAttackShopUpgrade },
	{ "growth", itemIndexEnum_GrowthProgressiveShopUpgrade },
	{ "reroll", itemIndexEnum_RerollProgressiveShopUpgrade },
	{ "eliminate", itemIndexEnum_EliminateProgressiveShopUpgrade },
	{ "holdOption", itemIndexEnum_HoldProgressiveShopUpgrade },
	{ "armorUnlock", itemIndexEnum_CustomizeShopUpgrade },
	{ "supports", itemIndexEnum_SupportsShopUpgrade },
	{ "materialDrops", itemIndexEnum_MaterialShopUpgrade },
	{ "stamps", itemIndexEnum_StampsShopUpgrade },
	{ "enchantments", itemIndexEnum_EnchantmentsShopUpgrade },
	{ "fandom", itemIndexEnum_FandomShopUpgrade },
	{ "fanLetterUnlock", itemIndexEnum_FanLettersShopUpgrade },
	{ "HP", itemIndexEnum_MaxHPProgressiveShopUpgrade },
	{ "ATK", itemIndexEnum_ATKProgressiveShopUpgrade },
	{ "SPD", itemIndexEnum_SPDProgressiveShopUpgrade },
	{ "crit", itemIndexEnum_CritProgressiveShopUpgrade },
	{ "pickupRange", itemIndexEnum_PickUpProgressiveShopUpgrade },
	{ "haste", itemIndexEnum_HasteProgressiveShopUpgrade },
	{ "regen", itemIndexEnum_RegenProgressiveShopUpgrade },
	{ "DR", itemIndexEnum_DefenseProgressiveShopUpgrade },
	{ "specCDR", itemIndexEnum_SpecialCooldownProgressiveShopUpgrade },
	{ "skillDamage", itemIndexEnum_SkillUpProgressiveShopUpgrade },
	{ "EXP", itemIndexEnum_EXPGainProgressiveShopUpgrade },
	{ "food", itemIndexEnum_FoodDropProgressiveShopUpgrade },
	{ "moneyGain", itemIndexEnum_MoneyGainProgressiveShopUpgrade },
	{ "enhanceUp", itemIndexEnum_EnhancementProgressiveShopUpgrade },
	{ "mobUp", itemIndexEnum_MarketingProgressiveShopUpgrade },
};

void TitleScreenCreateBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	/*
	{
		RValue map = g_ModuleInterface->CallBuiltin("variable_global_get", { "achievementsMap" });
		RValue arr = g_ModuleInterface->CallBuiltin("ds_map_values_to_array", { map });
		int len = g_ModuleInterface->CallBuiltin("array_length", { arr }).ToInt32();
		for (int i = 0; i < len; i++)
		{
			RValue achievementNumber = getInstanceVariable(arr[i], GML_achievementNumber);
			RValue achievementID = getInstanceVariable(arr[i], GML_id);
			RValue achievementDesc = getInstanceVariable(arr[i], GML_achievementDescription);
			callbackManagerInterfacePtr->LogToFile(MODNAME, "%s %s %s", achievementNumber.ToCString(), achievementID.ToCString(), achievementDesc.ToCString());
		}
	}
	{
		RValue map = g_ModuleInterface->CallBuiltin("variable_global_get", { "attacksLibrary" });
		RValue arr = g_ModuleInterface->CallBuiltin("ds_map_values_to_array", { map });
		int len = g_ModuleInterface->CallBuiltin("array_length", { arr }).ToInt32();
		for (int i = 0; i < len; i++)
		{
			callbackManagerInterfacePtr->LogToFile(MODNAME, "%s", arr[i].ToCString());
		}
	}
	{
		RValue map = g_ModuleInterface->CallBuiltin("variable_global_get", { "itemsLibrary" });
		RValue arr = g_ModuleInterface->CallBuiltin("ds_map_values_to_array", { map });
		int len = g_ModuleInterface->CallBuiltin("array_length", { arr }).ToInt32();
		for (int i = 0; i < len; i++)
		{
			callbackManagerInterfacePtr->LogToFile(MODNAME, "%s", arr[i].ToCString());
		}
	}
	*/
}

void InputManagerStepBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args)
{
	bool hasUpdated = false;
	CInstance* Self = std::get<0>(Args);

	if (AP_GetConnectionStatus() == AP_ConnectionStatus::Connected)
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
	}

	if (obtainedLocationSet.contains(locationIndexEnum_DefeatStage1Boss) && obtainedLocationSet.contains(locationIndexEnum_DefeatStage2Boss) && obtainedLocationSet.contains(locationIndexEnum_DefeatStage3Boss) && obtainedLocationSet.contains(locationIndexEnum_DefeatStage4Boss) && obtainedLocationSet.contains(locationIndexEnum_DefeatStage5Boss))
	{
		AP_StoryComplete();
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
				else if (itemID == itemIndexEnum_ProgressiveStage)
				{
					RValue** args = new RValue * [3];
					RValue unlockedStages = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "unlockedStages" });
					RValue stageName;

					switch (curObtainedItems[itemID])
					{
						case 1:
						{
							stageName = "STAGE 2";
							break;
						}
						case 2:
						{
							stageName = "STAGE 3";
							break;
						}
						case 3:
						{
							stageName = "STAGE 4";
							break;
						}
						case 4:
						{
							stageName = "STAGE 5";
							break;
						}
						case 5:
						{
							stageName = "STAGE 1 (HARD)";
							break;
						}
						case 6:
						{
							stageName = "STAGE 2 (HARD)";
							break;
						}
						case 7:
						{
							stageName = "STAGE 3 (HARD)";
							break;
						}
						case 8:
						{
							stageName = "STAGE 4 (HARD)";
							break;
						}
						default:
						{
							callbackManagerInterfacePtr->LogToFile(MODNAME, "Unhandled progressive stage amount %d", curObtainedItems[itemID]);
						}
					}

					RValue stageStr = "STAGE";
					args[0] = &unlockedStages;
					args[1] = &stageName;
					args[2] = &stageStr;
					RValue result;
					origUnlockThingScript(Self, nullptr, result, 3, args);
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
			//	a;
				// TODO: Need to figure out how to separate progressive upgrades from actual shop upgrades
				// Shop
				int saveLevel = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, shopToIDMap[itemID].c_str() }).ToInt32();
				g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, shopToIDMap[itemID].c_str(), saveLevel + 1 });
			}
			hasUpdated = true;
		}
	}
	if (hasUpdated)
	{
		RValue result;
		origSavePlayerSaveScript(Self, nullptr, result, 0, nullptr);
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