#include "BuiltinFunctions.h"
#include "ModuleMain.h"
#include "ScriptFunctions.h"

extern CallbackManagerInterface* callbackManagerInterfacePtr;
extern bool isInInitialPlayerSaveLoad;

void FileExistsBefore(RValue& Result, CInstance* Self, CInstance* Other, int numArgs, RValue* Args)
{
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