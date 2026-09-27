#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>
#include "ScriptFunctions.h"
#include "CommonFunctions.h"
#include "CodeEvents.h"
#include "ModuleMain.h"
#include "APCpp/Archipelago.h"
#include "ArchipelagoMenu.h"
#include "Constants.h"
#include <unordered_set>

extern CallbackManagerInterface* callbackManagerInterfacePtr;

extern std::unordered_map<std::string, itemIndexEnum> shopIDToIndexMap;
extern int serverSaveID;
extern bool hasLoadedSave;
extern std::string apPlayerName;
extern std::unordered_map<std::string, locationIndexEnum> itemNameToLocationMap;
extern std::unordered_map<std::string, locationIndexEnum> enemyIDToLocationMap;
extern std::unordered_map<itemIndexEnum, int> curObtainedItems;

std::unordered_set<locationIndexEnum> obtainedLocationSet;

int curFrameNum = 0;
bool isInInitialPlayerSaveLoad = false;

RValue& CanSubmitScoreFuncBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	ReturnValue.m_Kind = VALUE_BOOL;
	ReturnValue.m_Real = 0;
	callbackManagerInterfacePtr->CancelOriginalFunction();
	return ReturnValue;
}

RValue& DoAchievementBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue achievementsMap = g_ModuleInterface->CallBuiltin("variable_global_get", { "achievementsMap" });
	if (achievementsMap.m_Kind != VALUE_UNDEFINED)
	{
		RValue curAchievement = g_ModuleInterface->CallBuiltin("ds_map_find_value", { achievementsMap, *Args[0] });
		if (curAchievement.m_Kind == VALUE_UNDEFINED)
		{
			callbackManagerInterfacePtr->LogToFile(MODNAME, "ERROR: achievement %s is named incorrectly. Attempting to fix", Args[0]->ToCString());
			if (Args[0]->ToString().compare("payday") == 0)
			{
				curAchievement = g_ModuleInterface->CallBuiltin("ds_map_find_value", { achievementsMap, "payDay" });
			}
			else
			{
				callbackManagerInterfacePtr->LogToFile(MODNAME, "ERROR: couldn't fix achievement name");
				return ReturnValue;
			}
		}
		locationIndexEnum locationNumber = static_cast<locationIndexEnum>(getInstanceVariable(curAchievement, GML_achievementNumber).ToInt32() + 1);

		sendAPCheck(Self, locationNumber);
	}
	return ReturnValue;
}

RValue& UnlockThingBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	callbackManagerInterfacePtr->CancelOriginalFunction();
	return ReturnValue;
}

RValue& newDSMapSecureLoadBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	if (Args[0]->ToString().compare("save_n.dat") == 0)
	{
		RValue** args = new RValue * [1];
		RValue saveName = std::format("ArchipelagoSave_{}_{}.dat", apPlayerName, serverSaveID).c_str();
		args[0] = &saveName;
		callbackManagerInterfacePtr->CancelOriginalFunction();
		return origNewDSMapMapSecureLoadScript(Self, Other, ReturnValue, numArgs, args);
	}

	return ReturnValue;
}

RValue& newDSMapSecureSaveBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	if (Args[1]->ToString().compare("save_n.dat") == 0)
	{
		if (!hasLoadedSave)
		{
			return ReturnValue;
		}
		RValue** args = new RValue*[2];
		RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
		RValue saveName = std::format("ArchipelagoSave_{}_{}.dat", apPlayerName, serverSaveID).c_str();
		args[0] = &playerSave;
		args[1] = &saveName;
		callbackManagerInterfacePtr->CancelOriginalFunction();
		return origNewDSMapMapSecureSaveScript(Self, Other, ReturnValue, numArgs, args);
	}
	
	return ReturnValue;
}

RValue& InitialPlayerSaveLoadBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	isInInitialPlayerSaveLoad = true;
	return ReturnValue;
}

RValue& InitialPlayerSaveLoadAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	isInInitialPlayerSaveLoad = false;
	return ReturnValue;
}

RValue& CheckPlayerSaveBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue defaultPlayerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "defaultPlayerSave" });
	RValue emptyWeaponArr = g_ModuleInterface->CallBuiltin("array_create", { 0 });
	g_ModuleInterface->CallBuiltin("ds_map_set", { defaultPlayerSave, "unlockedWeapons", emptyWeaponArr });
	RValue emptyItemArr = g_ModuleInterface->CallBuiltin("array_create", { 0 });
	g_ModuleInterface->CallBuiltin("ds_map_set", { defaultPlayerSave, "unlockedItems", emptyItemArr });
	RValue emptyStageArr = g_ModuleInterface->CallBuiltin("array_create", { 0 });
	g_ModuleInterface->CallBuiltin("ds_map_set", { defaultPlayerSave, "unlockedStages", emptyStageArr });
	return ReturnValue;
}

RValue& SetFirstCharacterDataBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	callbackManagerInterfacePtr->CancelOriginalFunction();
	return ReturnValue;
}

RValue& CheckPastAchievementsBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	callbackManagerInterfacePtr->CancelOriginalFunction();
	return ReturnValue;
}

RValue& TotalRefundShopCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	callbackManagerInterfacePtr->CancelOriginalFunction();
	return ReturnValue;
}

RValue& RefundPlayerStatUpShopCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	if (numArgs < 2 || Args[1]->ToInt32() != 0)
	{
		callbackManagerInterfacePtr->CancelOriginalFunction();
	}
	return ReturnValue;
}

RValue& LevelPlayerStatUpShopCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	std::string removePrefixStr = Args[0]->ToString().substr(3);
	auto find = shopIDToIndexMap.find(removePrefixStr);
	if (find != shopIDToIndexMap.end())
	{
		RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
		int saveLevel = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, *Args[0] }).ToInt32();
		sendAPCheck(Self, static_cast<locationIndexEnum>(shopItemToLocationMap[find->second] + saveLevel));
	}
	
	return ReturnValue;
}

RValue& ConfirmedShopCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	int shopMode = getInstanceVariable(Self, GML_shopMode).ToInt32();
	if (shopMode == 0)
	{
		setInstanceVariable(Self, GML_shopMode, -1);
	}
	return ReturnValue;
}

RValue& InitRodsBloopCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue rodArray = getInstanceVariable(Self, GML_rodArray);
	int arrLen = g_ModuleInterface->CallBuiltin("array_length", { rodArray }).ToInt32();
	for (int i = 0; i < arrLen; i++)
	{
		setInstanceVariable(rodArray[i], GML_inventoryValue, 100000000);
	}
	return ReturnValue;
}

RValue& InitSoilAndSeedsNemuCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
	RValue AP_unlockedFarm = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "AP_unlockedFarm" });
	RValue itemArray = getInstanceVariable(Self, GML_itemArray);
	int arrLen = g_ModuleInterface->CallBuiltin("array_length", { itemArray }).ToInt32();
	for (int i = 0; i < arrLen; i++)
	{
		if (AP_unlockedFarm.m_Kind == VALUE_UNDEFINED || !g_ModuleInterface->CallBuiltin("struct_exists", { AP_unlockedFarm, getInstanceVariable(itemArray[i], GML_inventoryID) }).ToBoolean())
		{
			setInstanceVariable(itemArray[i], GML_inventoryValue, 100000000);
		}
	}
	return ReturnValue;
}

RValue& InventoryAddAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
	RValue inventory = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "inventory" });
	int inventoryLen = g_ModuleInterface->CallBuiltin("array_length", { inventory }).ToInt32();
	RValue updatedItem;
	int foundIndex = -1;

	for (int i = 0; i < inventoryLen; i++)
	{
		if (Args[0]->ToString().compare(inventory[i][0].ToString()) == 0)
		{
			foundIndex = i;
			updatedItem = inventory[i];
			break;
		}
	}

	if (foundIndex == -1)
	{
		loggingCallback(std::format("Couldn't find item {}", Args[0]->ToString()));
		return ReturnValue;
	}

	int updatedItemMaxCount = updatedItem[2].ToInt32();

	if (updatedItemMaxCount >= 50)
	{
		sendAPCheck(Self, itemNameToLocationMap[updatedItem[0].ToString()]);
	}

	return ReturnValue;
}

RValue& ConfirmCookingPotCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue interacting = getInstanceVariable(Self, GML_interacting);
	RValue canControl = getInstanceVariable(Self, GML_canControl);
	if (interacting.ToBoolean() && canControl.ToBoolean())
	{
		RValue pauseMenu = getInstanceVariable(Self, GML_pauseMenu);
		if (pauseMenu.ToInt32() == 3)
		{
			RValue cookConfirm = getInstanceVariable(Self, GML_cookConfirm);
			if (cookConfirm.ToBoolean())
			{
				RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
				RValue displayingInventory = getInstanceVariable(Self, GML_displayingInventory);
				RValue inventorySelect = getInstanceVariable(Self, GML_inventorySelect);
				RValue optionID = getInstanceVariable(displayingInventory[inventorySelect.ToInt32()], GML_optionID);
				std::string cookingName = std::format("AP_Cook{}", optionID.ToString());
				RValue saveData = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, cookingName.c_str() });
				int newCount = saveData.m_Kind == VALUE_UNDEFINED ? 1 : saveData.ToInt32() + 1;
				g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, cookingName.c_str(), newCount });
				if (newCount >= 10)
				{
					sendAPCheck(Self, itemNameToLocationMap[cookingName]);
				}
			}
		}
	}
	
	return ReturnValue;
}

RValue& ConfirmCkiaCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
	g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "usingAxe", curObtainedItems[itemIndexEnum_ProgressiveAxe] });
	g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "usingPick", curObtainedItems[itemIndexEnum_ProgressivePickaxe] });
	RValue axeUnlock = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "axeUnlock" });
	RValue pickUnlock = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "pickUnlock" });
	RValue armorUnlock = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "armorUnlock" });
	int axeUnlockLen = g_ModuleInterface->CallBuiltin("array_length", { axeUnlock }).ToInt32();
	int pickUnlockLen = g_ModuleInterface->CallBuiltin("array_length", { pickUnlock }).ToInt32();
	int armorUnlockLen = g_ModuleInterface->CallBuiltin("array_length", { armorUnlock }).ToInt32();
	for (int i = 1; i < axeUnlockLen; i++)
	{
		if (axeUnlock[i].ToBoolean())
		{
			locationIndexEnum locationIndex = static_cast<locationIndexEnum>(locationIndexEnum_MakeStoneAxe + i - 1);
			if (locationIndex > locationIndexEnum_MakeHololiteAxe)
			{
				loggingCallback(std::format("Invalid Axe Check {}", static_cast<int>(locationIndex)));
			}
			else
			{
				sendAPCheck(Self, locationIndex);
			}
		}
	}
	for (int i = 1; i < pickUnlockLen; i++)
	{
		if (pickUnlock[i].ToBoolean())
		{
			locationIndexEnum locationIndex = static_cast<locationIndexEnum>(locationIndexEnum_MakeStonePickaxe + i - 1);
			if (locationIndex > locationIndexEnum_MakeHololitePickaxe)
			{
				loggingCallback(std::format("Invalid Pickaxe Check {}", static_cast<int>(locationIndex)));
			}
			else
			{
				sendAPCheck(Self, locationIndex);
			}
		}
	}
	for (int i = 1; i < armorUnlockLen; i++)
	{
		if (armorUnlock[i].ToBoolean())
		{
			locationIndexEnum locationIndex = static_cast<locationIndexEnum>(locationIndexEnum_MakeBasicPrism + i - 1);
			if (locationIndex > locationIndexEnum_MakeHololitePrism)
			{
				loggingCallback(std::format("Invalid Prism Check {}", static_cast<int>(locationIndex)));
			}
			else
			{
				sendAPCheck(Self, locationIndex);
			}
		}
	}
	return ReturnValue;
}

RValue& CheckLevelingForgeGatherCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
	int woodLevel = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "woodLevel" }).ToInt32();
	int mineLevel = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "mineLevel" }).ToInt32();
	for (int i = 1; i < woodLevel; i++)
	{
		locationIndexEnum locationIndex = static_cast<locationIndexEnum>(locationIndexEnum_ReachWoodcuttingLevel2 + i - 1);
		if (locationIndex > locationIndexEnum_ReachWoodcuttingLevel9)
		{
			loggingCallback(std::format("Invalid Woodcutting Level Check {}", static_cast<int>(locationIndex)));
		}
		else
		{
			sendAPCheck(Self, locationIndex);
		}
	}
	for (int i = 1; i < mineLevel; i++)
	{
		locationIndexEnum locationIndex = static_cast<locationIndexEnum>(locationIndexEnum_ReachMiningLevel2 + i - 1);
		if (locationIndex > locationIndexEnum_ReachMiningLevel9)
		{
			loggingCallback(std::format("Invalid Mining Level Check {}", static_cast<int>(locationIndex)));
		}
		else
		{
			sendAPCheck(Self, locationIndex);
		}
	}
	return ReturnValue;
}

RValue& DieEnemyCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args)
{
	RValue fanLetterID = getInstanceVariable(Self, GML_fanLetterID);
	auto find = enemyIDToLocationMap.find(fanLetterID.ToString());

	if (find == enemyIDToLocationMap.end())
	{
		loggingCallback(std::format("Couldn't find enemy id for {}", fanLetterID.ToString()));
		return ReturnValue;
	}

	sendAPCheck(Self, find->second);

	return ReturnValue;
}