#pragma once
#include <YYToolkit/YYTK_Shared.hpp>
#include "ModuleMain.h"

void FileExistsBefore(RValue& Result, CInstance* Self, CInstance* Other, int numArgs, RValue* Args);
void FileDeleteBefore(RValue& Result, CInstance* Self, CInstance* Other, int numArgs, RValue* Args);