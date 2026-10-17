#pragma once
#include "ModuleMain.h"
#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>

void TitleScreenCreateBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void InputManagerStepBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void CharSelectCreateBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void CharSelectCreateAfter(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void CharSelectDrawBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void CharSelectDrawAfter(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void AchievementsOther10After(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void ShopCreateAfter(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);
void PlayerManagerStepBefore(std::tuple<CInstance*, CInstance*, CCode*, int, RValue*>& Args);