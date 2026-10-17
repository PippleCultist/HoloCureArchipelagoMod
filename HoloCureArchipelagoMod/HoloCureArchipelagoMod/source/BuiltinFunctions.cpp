#include "BuiltinFunctions.h"
#include "ModuleMain.h"
#include "ScriptFunctions.h"

extern CallbackManagerInterface* callbackManagerInterfacePtr;
extern bool isInInitialPlayerSaveLoad;
extern bool isInSelectChar;
extern bool isLoadingAPSave;

void FileExistsBefore(RValue& Result, CInstance* Self, CInstance* Other, int numArgs, RValue* Args)
{
	if (isLoadingAPSave && Args[0].ToString().compare("save_n.dat") == 0)
	{
		callbackManagerInterfacePtr->CancelOriginalFunction();
		Result = true;
		return;
	}
	if (Args[0].ToString().compare("save.dat") == 0 || Args[0].ToString().compare("save_n.dat") == 0 || Args[0].ToString().compare("backup.dat") == 0 || Args[0].ToString().compare("backup_save_n.dat") == 0)
	{
		callbackManagerInterfacePtr->CancelOriginalFunction();
		Result = false;
	}
}

void FileDeleteBefore(RValue& Result, CInstance* Self, CInstance* Other, int numArgs, RValue* Args)
{
	callbackManagerInterfacePtr->CancelOriginalFunction();
}

void DsMapFindValueBefore(RValue& Result, CInstance* Self, CInstance* Other, int numArgs, RValue* Args)
{
	if (isInSelectChar)
	{
		if (Args[1].ToString().compare("armorUnlock") == 0)
		{
			RValue argsArr[2];
			argsArr[0] = Args[0];
			argsArr[1] = "AP_unlockedPrism";
			origDSMapFindValueFunc(Result, Self, Other, numArgs, argsArr);
			if (Result.IsUndefined())
			{
				RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
				Result = g_ModuleInterface->CallBuiltin("array_create", { 6 });
				g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, argsArr[1], Result });
			}
			callbackManagerInterfacePtr->CancelOriginalFunction();
		}
	}
}