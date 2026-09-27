#pragma once
#include "ModuleMain.h"
#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>

RValue& CanSubmitScoreFuncBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& DoAchievementBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& UnlockThingBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& newDSMapSecureLoadBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& newDSMapSecureSaveBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& InitialPlayerSaveLoadBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& InitialPlayerSaveLoadAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& CheckPlayerSaveBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& SetFirstCharacterDataBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& CheckPastAchievementsBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& TotalRefundShopCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& RefundPlayerStatUpShopCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& LevelPlayerStatUpShopCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& ConfirmedShopCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& InitRodsBloopCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& InitSoilAndSeedsNemuCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& InventoryAddAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& ConfirmCookingPotCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& ConfirmCkiaCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& CheckLevelingForgeGatherCreateAfter(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);
RValue& DieEnemyCreateBefore(CInstance* Self, CInstance* Other, RValue& ReturnValue, int numArgs, RValue** Args);