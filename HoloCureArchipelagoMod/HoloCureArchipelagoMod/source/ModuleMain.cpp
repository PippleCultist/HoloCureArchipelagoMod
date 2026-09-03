#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>
#include "CodeEvents.h"
#include "ScriptFunctions.h"
#include "ModuleMain.h"
#include "CallbackManager/CallbackManagerInterface.h"
#include "ArchipelagoMenu.h"
#include "BuiltinFunctions.h"
#include <semaphore>
using namespace Aurie;
using namespace YYTK;

RValue GMLVarIndexMapGMLHash[1001];

TRoutine origStructGetFromHashFunc;
TRoutine origStructSetFromHashFunc;
TRoutine origFileExistsFunc;

CallbackManagerInterface* callbackManagerInterfacePtr = nullptr;
YYTKInterface* g_ModuleInterface = nullptr;
YYRunnerInterface g_RunnerInterface;

PFUNC_YYGMLScript origCanSubmitScoreScript = nullptr;
PFUNC_YYGMLScript origExecuteAttackScript = nullptr;
PFUNC_YYGMLScript origUnlockThingScript = nullptr;
PFUNC_YYGMLScript origNewDSMapMapSecureSaveScript = nullptr;
PFUNC_YYGMLScript origNewDSMapMapSecureLoadScript = nullptr;
PFUNC_YYGMLScript origSavePlayerSaveScript = nullptr;
PFUNC_YYGMLScript origLevelPlayerStatUpScript = nullptr;

CInstance* globalInstance = nullptr;

int objInputManagerIndex = -1;
int objAttackControllerIndex = -1;
int objPlayerManagerIndex = -1;
int objPlayerIndex = -1;

AurieStatus FindMemoryPatternAddress(const unsigned char* Pattern, const char* PatternMask, PVOID& outMemoryAddress)
{
	AurieStatus status = AURIE_SUCCESS;
	std::wstring gameName;
	if (!AurieSuccess(status = MdGetImageFilename(g_ArInitialImage, gameName)))
	{
		return status;
	}

	// Scan for pattern
	size_t patternMatch = MmSigscanModule(
		gameName.c_str(),
		Pattern,
		PatternMask
	);
	if (!patternMatch)
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Couldn't find pattern %s", Pattern);
		return AURIE_OBJECT_NOT_FOUND;
	}

	outMemoryAddress = reinterpret_cast<PVOID>(patternMatch);
	return AURIE_SUCCESS;
}

AurieStatus moduleInitStatus = AURIE_MODULE_INITIALIZATION_FAILED;

typedef void (*LPFNDLL_AP_Init)(const char*);

void initHooks()
{
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterBuiltinFunctionCallback(MODNAME, "struct_get_from_hash", nullptr, nullptr, &origStructGetFromHashFunc)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "struct_get_from_hash");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterBuiltinFunctionCallback(MODNAME, "struct_set_from_hash", nullptr, nullptr, &origStructSetFromHashFunc)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "struct_set_from_hash");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterBuiltinFunctionCallback(MODNAME, "file_exists", FileExistsBefore, nullptr, &origFileExistsFunc)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "file_exists");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterBuiltinFunctionCallback(MODNAME, "file_delete", FileDeleteBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "file_delete");
		return;
	}

	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_CanSubmitScore@gml_Object_obj_PlayerManager_Create_0", CanSubmitScoreFuncBefore, nullptr, &origCanSubmitScoreScript)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_CanSubmitScore@gml_Object_obj_PlayerManager_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_DoAchievement", DoAchievementBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_DoAchievement");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_UnlockThing", UnlockThingBefore, nullptr, &origUnlockThingScript)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_UnlockThing");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_new_ds_map_secure_load", newDSMapSecureLoadBefore, nullptr, &origNewDSMapMapSecureLoadScript)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_new_ds_map_secure_load");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_new_ds_map_secure_save", newDSMapSecureSaveBefore, nullptr, &origNewDSMapMapSecureSaveScript)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_new_ds_map_secure_load");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_InitialPlayerSaveLoad", InitialPlayerSaveLoadBefore, InitialPlayerSaveLoadAfter, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_InitialPlayerSaveLoad");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_CheckPlayerSave", CheckPlayerSaveBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_CheckPlayerSave");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_SetFirstCharacterData", SetFirstCharacterDataBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_SetFirstCharacterData");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_SavePlayerSave", nullptr, nullptr, &origSavePlayerSaveScript)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_SavePlayerSave");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_CheckPastAchievements@gml_Object_obj_Achievements_Create_0", CheckPastAchievementsBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_CheckPastAchievements@gml_Object_obj_Achievements_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_TotalRefund@gml_Object_obj_Shop_Create_0", TotalRefundShopCreateBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_TotalRefund@gml_Object_obj_Shop_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_RefundPlayerStatUp@gml_Object_obj_Shop_Create_0", RefundPlayerStatUpShopCreateBefore, nullptr, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_RefundPlayerStatUp@gml_Object_obj_Shop_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_LevelPlayerStatUp@gml_Object_obj_Shop_Create_0", LevelPlayerStatUpShopCreateBefore, nullptr, &origLevelPlayerStatUpScript)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_LevelPlayerStatUp@gml_Object_obj_Shop_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterScriptFunctionCallback(MODNAME, "gml_Script_Confirmed@gml_Object_obj_Shop_Create_0", nullptr, ConfirmedShopCreateAfter, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Script_Confirmed@gml_Object_obj_Shop_Create_0");
		return;
	}
	

	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterCodeEventCallback(MODNAME, "gml_Object_obj_TitleScreen_Create_0", TitleScreenCreateBefore, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Object_obj_TitleScreen_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterCodeEventCallback(MODNAME, "gml_Object_obj_InputManager_Step_0", InputManagerStepBefore, nullptr)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Object_obj_InputManager_Step_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterCodeEventCallback(MODNAME, "gml_Object_obj_CharSelect_Create_0", nullptr, CharSelectCreateAfter)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Object_obj_CharSelect_Create_0");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterCodeEventCallback(MODNAME, "gml_Object_obj_Achievements_Other_10", nullptr, AchievementsOther10After)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Object_obj_Achievements_Other_10");
		return;
	}
	if (!AurieSuccess(callbackManagerInterfacePtr->RegisterCodeEventCallback(MODNAME, "gml_Object_obj_Shop_Create_0", nullptr, ShopCreateAfter)))
	{
		DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to register callback for %s", "gml_Object_obj_Shop_Create_0");
		return;
	}

	g_RunnerInterface = g_ModuleInterface->GetRunnerInterface();
	g_ModuleInterface->GetGlobalInstance(&globalInstance);

	objInputManagerIndex = static_cast<int>(g_ModuleInterface->CallBuiltin("asset_get_index", { "obj_InputManager" }).ToInt32());
	objAttackControllerIndex = static_cast<int>(g_ModuleInterface->CallBuiltin("asset_get_index", { "obj_AttackController" }).ToInt32());
	objPlayerManagerIndex = static_cast<int>(g_ModuleInterface->CallBuiltin("asset_get_index", { "obj_PlayerManager" }).ToInt32());
	objPlayerIndex = static_cast<int>(g_ModuleInterface->CallBuiltin("asset_get_index", { "obj_Player" }).ToInt32());

	AurieStatus status = AURIE_SUCCESS;

	for (int i = 0; i < std::extent<decltype(VariableNamesStringsArr)>::value; i++)
	{
		if (!AurieSuccess(status))
		{
			DbgPrintEx(LOG_SEVERITY_ERROR, "Failed to get hash for %s", VariableNamesStringsArr[i]);
		}
		GMLVarIndexMapGMLHash[i] = std::move(g_ModuleInterface->CallBuiltin("variable_get_hash", { VariableNamesStringsArr[i] }));
	}

	moduleInitStatus = AURIE_SUCCESS;

	loadModImguiMenu();

	callbackManagerInterfacePtr->LogToFile(MODNAME, "Finished initializing");
}

void runnerInitCallback(FunctionWrapper<void(int)>& dummyWrapper)
{
	AurieStatus status = AURIE_SUCCESS;
	status = ObGetInterface("callbackManager", (AurieInterfaceBase*&)callbackManagerInterfacePtr);
	if (!AurieSuccess(status))
	{
		printf("Failed to get callback manager interface. Make sure that CallbackManagerMod is located in the mods/Aurie directory.\n");
		return;
	}

	callbackManagerInterfacePtr->RegisterInitFunction(initHooks);
}


EXPORTED AurieStatus ModulePreinitialize(
	IN AurieModule* Module,
	IN const fs::path& ModulePath
)
{
	AurieStatus status = AURIE_SUCCESS;
	// Gets a handle to the interface exposed by YYTK
	// You can keep this pointer for future use, as it will not change unless YYTK is unloaded.
	g_ModuleInterface = GetInterface();

	// If we can't get the interface, we fail loading.
	if (!AurieSuccess(status))
	{
		callbackManagerInterfacePtr->LogToFile(MODNAME, "Failed to get YYTK Interface");
		printf("Failed to get YYTK Interface\n");
		return AURIE_MODULE_DEPENDENCY_NOT_RESOLVED;
	}

	g_ModuleInterface->CreateCallback(
		Module,
		EVENT_RUNNER_INIT,
		runnerInitCallback,
		0
	);

	return AURIE_SUCCESS;
}

EXPORTED AurieStatus ModuleInitialize(
	IN AurieModule* Module,
	IN const fs::path& ModulePath
)
{
	// TODO: Somehow check if the AP server has changed or not to prompt to delete and reset the save
	// TODO: Add goal in holohouse with new checks
	// TODO: Add checks for unique mob kills
	// TODO: Find a way to integrate gacha
	// TODO: Set buying out shop as a goal
	// TODO: Consider setting an option in the gui to increase the in game timer speed
	// TODO: Add location scouts
	// TODO: See if the holocure client can be integrated with archipelago directly

	return moduleInitStatus;
}