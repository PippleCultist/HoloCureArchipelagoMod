#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>
#include "ScriptFunctions.h"
#include "CommonFunctions.h"
#include "CodeEvents.h"
#include "ModuleMain.h"
#include "APCpp/Archipelago.h"
#include "ArchipelagoMenu.h"
#include <unordered_set>

extern CallbackManagerInterface* callbackManagerInterfacePtr;

extern std::unordered_map<std::string, itemIndexEnum> shopIDToIndexMap;

std::map<locationIndexEnum, std::string> locationToNameMap
{
	{ locationIndexEnum_AmeliaWastonStageClear, "Clear a Stage with Amelia Watson" },
	{ locationIndexEnum_AmeliaWastonGachikoi, "Reach Gachikoi with Amelia Watson" },
	{ locationIndexEnum_GawrGuraStageClear, "Clear a Stage with Gawr Gura" },
	{ locationIndexEnum_GawrGuraGachikoi, "Reach Gachikoi with Gawr Gura" },
	{ locationIndexEnum_NinomaeInanis10Minutes, "Reach 10 minutes with Ninomae Inanis" },
	{ locationIndexEnum_NinomaeInanisStageClear, "Clear a Stage with Ninomae Inanis" },
	{ locationIndexEnum_NinomaeInanisGachikoi, "Reach Gachikoi with Ninomae Inanis" },
	{ locationIndexEnum_TakanshiKiara10Minutes, "Reach 10 minutes with Takanashi Kiara" },
	{ locationIndexEnum_TakanshiKiaraStageClear, "Clear a Stage with Takanashi Kiara" },
	{ locationIndexEnum_TakanshiKiaraGachikoi, "Reach Gachikoi with Takanashi Kiara" },
	{ locationIndexEnum_MoriCalliope10Minutes, "Reach 10 minutes with Mori Calliope" },
	{ locationIndexEnum_MoriCalliopeStageClear, "Clear a Stage with Mori Calliope" },
	{ locationIndexEnum_MoriCalliopeGachikoi, "Reach Gachikoi with Mori Calliope" },
	{ locationIndexEnum_HakosBaelz10Minutes, "Reach 10 minutes with Hakos Baelz" },
	{ locationIndexEnum_HakosBaelzStageClear, "Clear a Stage with Hakos Baelz" },
	{ locationIndexEnum_HakosBaelzGachikoi, "Reach Gachikoi with Hakos Baelz" },
	{ locationIndexEnum_OuroKroniiStageClear, "Clear a Stage with Ouro Kronii" },
	{ locationIndexEnum_OuroKroniiGachikoi, "Reach Gachikoi with Ouro Kronii" },
	{ locationIndexEnum_CeresFaunaStageClear, "Clear a Stage with Ceres Fauna" },
	{ locationIndexEnum_CeresFaunaGachikoi, "Reach Gachikoi with Ceres Fauna" },
	{ locationIndexEnum_NanashiMumeiStageClear, "Clear a Stage with Nanashi Mumei" },
	{ locationIndexEnum_NanashiMumeiGachikoi, "Reach Gachikoi with Nanashi Mumei" },
	{ locationIndexEnum_TsukumoSana10Minutes, "Reach 10 minutes with Tsukumo Sana" },
	{ locationIndexEnum_TsukumoSanaStageClear, "Clear a Stage with Tsukumo Sana" },
	{ locationIndexEnum_TsukumoSanaGachikoi, "Reach Gachikoi with Tsukumo Sana" },
	{ locationIndexEnum_IRyS10Minutes, "Reach 10 minutes with IRyS" },
	{ locationIndexEnum_IRySStageClear, "Clear a Stage with IRyS" },
	{ locationIndexEnum_IRySGachikoi, "Reach Gachikoi with IRyS" },
	{ locationIndexEnum_ShirakamiFubukiStageClear, "Clear a Stage with Shirakami Fubuki" },
	{ locationIndexEnum_ShirakamiFubukiGachikoi, "Reach Gachikoi with Shirakami Fubuki" },
	{ locationIndexEnum_OokamiMioStageClear, "Clear a Stage with Ookami Mio" },
	{ locationIndexEnum_OokamiMioGachikoi, "Reach Gachikoi with Ookami Mio" },
	{ locationIndexEnum_NekomataOkayuStageClear, "Clear a Stage with Nekomata Okayu" },
	{ locationIndexEnum_NekomataOkayuGachikoi, "Reach Gachikoi with Nekomata Okayu" },
	{ locationIndexEnum_InugamiKorone10Minutes, "Reach 10 minutes with Inugami Korone" },
	{ locationIndexEnum_InugamiKoroneStageClear, "Clear a Stage with Inugami Korone" },
	{ locationIndexEnum_InugamiKoroneGachikoi, "Reach Gachikoi with Inugami Korone" },
	{ locationIndexEnum_TokinoSoraStageClear, "Clear a Stage with Tokino Sora" },
	{ locationIndexEnum_TokinoSoraGachikoi, "Reach Gachikoi with Tokino Sora" },
	{ locationIndexEnum_AZkiStageClear, "Clear a Stage with AZki" },
	{ locationIndexEnum_AZkiGachikoi, "Reach Gachikoi with AZki" },
	{ locationIndexEnum_RobocoStageClear, "Clear a Stage with Roboco-san" },
	{ locationIndexEnum_RobocoGachikoi, "Reach Gachikoi with Roboco-san" },
	{ locationIndexEnum_HoshimachiSuiseiStageClear, "Clear a Stage with Hoshimachi Suisei" },
	{ locationIndexEnum_HoshimachiSuiseiGachikoi, "Reach Gachikoi with Hoshimachi Suisei" },
	{ locationIndexEnum_SakuraMikoStageClear, "Clear a Stage with Sakura Miko" },
	{ locationIndexEnum_SakuraMikoGachikoi, "Reach Gachikoi with Sakura Miko" },
	{ locationIndexEnum_AkaiHaatoStageClear, "Clear a Stage with Akai Haato" },
	{ locationIndexEnum_AkaiHaatoGachikoi, "Reach Gachikoi with Akai Haato" },
	{ locationIndexEnum_YozoraMelStageClear, "Clear a Stage with Yozora Mel" },
	{ locationIndexEnum_YozoraMelGachikoi, "Reach Gachikoi with Yozora Mel" },
	{ locationIndexEnum_NatsuiroMatsuriStageClear, "Clear a Stage with Natsuiro Matsuri" },
	{ locationIndexEnum_NatsuiroMatsuriGachikoi, "Reach Gachikoi with Natsuiro Matsuri" },
	{ locationIndexEnum_AkiRosenthalStageClear, "Clear a Stage with Aki Rosenthal" },
	{ locationIndexEnum_AkiRosenthalGachikoi, "Reach Gachikoi with Aki Rosenthal" },
	{ locationIndexEnum_YuzukiChocoStageClear, "Clear a Stage with Yuzuki Choco" },
	{ locationIndexEnum_YuzukiChocoGachikoi, "Reach Gachikoi with Yuzuki Choco" },
	{ locationIndexEnum_OozoraSubaruStageClear, "Clear a Stage with Oozora Subaru" },
	{ locationIndexEnum_OozoraSubaruGachikoi, "Reach Gachikoi with Oozora Subaru" },
	{ locationIndexEnum_MurasakiShion10Minutes, "Reach 10 minutes with Murasaki Shion" },
	{ locationIndexEnum_MurasakiShionStageClear, "Clear a Stage with Murasaki Shion" },
	{ locationIndexEnum_MurasakiShionGachikoi, "Reach Gachikoi with Murasaki Shion" },
	{ locationIndexEnum_NakiriAyameStageClear, "Clear a Stage with Nakiri Ayame" },
	{ locationIndexEnum_NakiriAyameGachikoi, "Reach Gachikoi with Nakiri Ayame" },
	{ locationIndexEnum_MinatoAquaStageClear, "Clear a Stage with Minato Aqua" },
	{ locationIndexEnum_MinatoAquaGachikoi, "Reach Gachikoi with Minato Aqua" },
	{ locationIndexEnum_MoonaHoshinovaStageClear, "Clear a Stage with Moona Hoshinova" },
	{ locationIndexEnum_MoonaHoshinovaGachikoi, "Reach Gachikoi with Moona Hoshinova" },
	{ locationIndexEnum_AiraniIofifteenStageClear, "Clear a Stage with Airani Iofifteen" },
	{ locationIndexEnum_AiraniIofifteenGachikoi, "Reach Gachikoi with Airani Iofifteen" },
	{ locationIndexEnum_AyundaRisuStageClear, "Clear a Stage with Ayunda Risu" },
	{ locationIndexEnum_AyundaRisuGachikoi, "Reach Gachikoi with Ayunda Risu" },
	{ locationIndexEnum_KureijiOllieStageClear, "Clear a Stage with Kureiji Ollie" },
	{ locationIndexEnum_KureijiOllie10Minutes, "Reach 10 minutes with Kureiji Ollie" },
	{ locationIndexEnum_KureijiOllieGachikoi, "Reach Gachikoi with Kureiji Ollie" },
	{ locationIndexEnum_PavoliaReineStageClear, "Clear a Stage with Pavolia Reine" },
	{ locationIndexEnum_PavoliaReineGachikoi, "Reach Gachikoi with Pavolia Reine" },
	{ locationIndexEnum_AnyaMelfissaStageClear, "Clear a Stage with Anya Melfissa" },
	{ locationIndexEnum_AnyaMelfissaGachikoi, "Reach Gachikoi with Anya Melfissa" },
	{ locationIndexEnum_KoboKanaeruStageClear, "Clear a Stage with Kobo Kanaeru" },
	{ locationIndexEnum_KoboKanaeruGachikoi, "Reach Gachikoi with Kobo Kanaeru" },
	{ locationIndexEnum_KaelaKovalskiaStageClear, "Clear a Stage with Kaela Kovalskia" },
	{ locationIndexEnum_KaelaKovalskiaGachikoi, "Reach Gachikoi with Kaela Kovalskia" },
	{ locationIndexEnum_VestiaZeta10Minutes, "Reach 10 minutes with Vestia Zeta" },
	{ locationIndexEnum_VestiaZetaStageClear, "Clear a Stage with Vestia Zeta" },
	{ locationIndexEnum_VestiaZetaGachikoi, "Reach Gachikoi with Vestia Zeta" },
	{ locationIndexEnum_UsadaPekoraStageClear, "Clear a Stage with Usada Pekora" },
	{ locationIndexEnum_UsadaPekoraGachikoi, "Reach Gachikoi with Usada Pekora" },
	{ locationIndexEnum_ShiroganeNoelStageClear, "Clear a Stage with Shirogane Noel" },
	{ locationIndexEnum_ShiroganeNoelGachikoi, "Reach Gachikoi with Shirogane Noel" },
	{ locationIndexEnum_ShiranuiFlareStageClear, "Clear a Stage with Shiranui Flare" },
	{ locationIndexEnum_ShiranuiFlareGachikoi, "Reach Gachikoi with Shiranui Flare" },
	{ locationIndexEnum_HoushouMarineStageClear, "Clear a Stage with Houshou Marine" },
	{ locationIndexEnum_HoushouMarineGachikoi, "Reach Gachikoi with Houshou Marine" },
	{ locationIndexEnum_KiryuCocoStageClear, "Clear a Stage with Kiryu Coco" },
	{ locationIndexEnum_KiryuCocoGachikoi, "Reach Gachikoi with Kiryu Coco" },
	{ locationIndexEnum_AmaneKanataStageClear, "Clear a Stage with Amane Kanata" },
	{ locationIndexEnum_AmaneKanataGachikoi, "Reach Gachikoi with Amane Kanata" },
	{ locationIndexEnum_TsunomakiWatameStageClear, "Clear a Stage with Tsunomaki Watame" },
	{ locationIndexEnum_TsunomakiWatameGachikoi, "Reach Gachikoi with Tsunomaki Watame" },
	{ locationIndexEnum_TokoyamiTowaStageClear, "Clear a Stage with Tokoyami Towa" },
	{ locationIndexEnum_TokoyamiTowaGachikoi, "Reach Gachikoi with Tokoyami Towa" },
	{ locationIndexEnum_HimemoriLunaStageClear, "Clear a Stage with Himemori Luna" },
	{ locationIndexEnum_HimemoriLunaGachikoi, "Reach Gachikoi with Himemori Luna" },
	{ locationIndexEnum_FirstGame, "Complete your first game" },
	{ locationIndexEnum_DefeatFubura, "Defeat Fubura" },
	{ locationIndexEnum_DefeatStage1Boss, "Defeat the Boss of Stage 1" },
	{ locationIndexEnum_DefeatStage2Boss, "Defeat the Boss of Stage 2" },
	{ locationIndexEnum_DefeatStage3Boss, "Defeat the Boss of Stage 3" },
	{ locationIndexEnum_DefeatStage4Boss, "Defeat the Boss of Stage 4" },
	{ locationIndexEnum_DefeatStage5Boss, "Defeat the Boss of Stage 5" },
	{ locationIndexEnum_DefeatStage1HardBoss, "Defeat the Boss of Stage 1 (Hard)" },
	{ locationIndexEnum_DefeatStage2HardBoss, "Defeat the Boss of Stage 2 (Hard)" },
	{ locationIndexEnum_DefeatStage3HardBoss, "Defeat the Boss of Stage 3 (Hard)" },
	{ locationIndexEnum_DefeatStage4HardBoss, "Defeat the Boss of Stage 4 (Hard)" },
	{ locationIndexEnum_ClearTimeMode, "Clear a stage in Time Mode" },
	{ locationIndexEnum_UnlockAllCharacters, "Unlock all characters" },
	{ locationIndexEnum_UseSpecial, "Unlock and use a character's special" },
	{ locationIndexEnum_DestroyYagooStatue, "Destroy a Yagoo Statue" },
	{ locationIndexEnum_UseAnvil, "Use an anvil" },
	{ locationIndexEnum_CuttingBoard10Minutes, "Reach 10 minutes with Cutting Board or related weapons using certain characters" },
	{ locationIndexEnum_UsePlugTypeAsacoco, "Complete a stage using Plug-In Type Asacoco" },
	{ locationIndexEnum_5000Coins, "Have 5000 coins" },
	{ locationIndexEnum_1000000Coins, "Have 1,000,000 coins" },
	{ locationIndexEnum_UseSake, "Clear any stage while using Sake" },
	{ locationIndexEnum_Level50, "Reach level 50 in one game" },
	{ locationIndexEnum_Level100, "Reach level 100 in one game" },
	{ locationIndexEnum_Defeat5000, "Defeat at least 5000 targets in a stage" },
	{ locationIndexEnum_LoseWithHalu, "Be defeated while using Halu" },
	{ locationIndexEnum_Eat50Hamburgers, "Eat over 50 hamburgers in one game" },
	{ locationIndexEnum_Deal1000Damage, "Deal over 1000 damage in one attack" },
	{ locationIndexEnum_Deal10000Damage, "Deal over 10000 damage in one attack" },
	{ locationIndexEnum_NoMove, "Clear a game of Stage Mode without moving at all" },
	{ locationIndexEnum_10Minutes, "Lose after 10 minutes in a game" },
	{ locationIndexEnum_NoSpecial, "Clear a game of Stage Mode without using Special after unlocking it" },
	{ locationIndexEnum_UseSuperChattoTime, "Complete a stage while using Super Chatto Time" },
	{ locationIndexEnum_PetBubba, "Pet Bubba as Amelia Watson" },
	{ locationIndexEnum_Get4Collabs, "Get 4 Collab Weapons in 1 game" },
	{ locationIndexEnum_Take500Damage, "Take a total of over 500 damage in one game" },
	{ locationIndexEnum_EnhanceAWeapon, "Enhance a weapon once" },
	{ locationIndexEnum_DefeatYagoo, "Defeat a Yagoo" },
	{ locationIndexEnum_DefeatGoldYagoo, "Defeat a Golden Yagoo" },
	{ locationIndexEnum_DefeatSilverYagoo, "Defeat a Silver Yagoo" },
	{ locationIndexEnum_LoseToYagoo, "Be defeated by a Yagoo" },
	{ locationIndexEnum_SuperBox, "Open a Super Box" },
	{ locationIndexEnum_DropSuperItem, "Drop a super item" },
	{ locationIndexEnum_ClearHardcore, "Clear a stage in Hardcore Mode" },
	{ locationIndexEnum_10Enhance, "Get a weapon to +10 enhancements" },
	{ locationIndexEnum_MainWeaponOnly, "Clear with only your main weapon" },
	{ locationIndexEnum_Fail5Enhance, "Fail enhancements 5 times in 1 run" },
	{ locationIndexEnum_Fail1To2Enhance, "Fail a +1 > +2 enhancing" },
	{ locationIndexEnum_ClearHaluLevel5, "Clear with Halu level 5" },
	{ locationIndexEnum_30MinutesHaluLevel5, "Survive to 30 minutes with Halu level 5" },
	{ locationIndexEnum_DefeatBossUnder10Seconds, "Defeat a 10 or 20-minute boss in under 10 seconds" },
	{ locationIndexEnum_LeaveBossAlive5Minutes, "Leave a boss alive for 5 minutes or more" },
	{ locationIndexEnum_LevelUp5Times1Second, "Level up 5 times in a row in one second" },
	{ locationIndexEnum_CompleteArmory, "Complete the Armory" },
	{ locationIndexEnum_WatchCredits, "Watch the credits to the end" },
	{ locationIndexEnum_100Crit, "Get 100% crit chance in a single run" },
	{ locationIndexEnum_1MillionScore, "Achieve 1m+ score in a single run" },
	{ locationIndexEnum_WatchTV10Seconds, "Watch the TV for 10 seconds" },
	{ locationIndexEnum_NoDamage5Minutes, "Don't take any damage for 5 minutes" },
	{ locationIndexEnum_HoloHouse, "Go to Holo House" },
	{ locationIndexEnum_AnnoyMember, "Annoy another member" },
	{ locationIndexEnum_HarvestPlant, "Harvest a plant" },
	{ locationIndexEnum_CatchShinyFish, "Catch a Shiny fish" },
	{ locationIndexEnum_StealFish, "Steal a fish from another Holo member" },
	{ locationIndexEnum_CookDish, "Cook a dish" },
	{ locationIndexEnum_Fish10Combo, "Get 10 combos in the fishing minigame" },
	{ locationIndexEnum_Fish50Combo, "Get 50 combos in the fishing minigame" },
	{ locationIndexEnum_CatchEveryFish, "Catch at least one of every kind of fish" },
	{ locationIndexEnum_HarvestEveryCrop, "Harvest at least one of every kind of crop" },
	{ locationIndexEnum_MaxLevelWorker, "Level a worker to their maximum level" },
	{ locationIndexEnum_ManagerLevel4, "Get Manager Level 4" },
	{ locationIndexEnum_RetireWorker, "Retire a Worker" },
	{ locationIndexEnum_Collect10000CoinsWorkers, "Collect 100,000 HoloCoins from workers at once" },
	{ locationIndexEnum_Huh, "Huh?" },
	{ locationIndexEnum_NoItems, "Clear a stage with no items" },
	{ locationIndexEnum_GoldHammer, "Use the Golden Hammer" },
	{ locationIndexEnum_NoSkill, "Clear stage mode without having any Character Skills (Fandom off)" },
	{ locationIndexEnum_HasteUp10, "Choose the Haste Stat Up option 10 times when leveling up" },
	{ locationIndexEnum_IofiSpecial20Seconds, "Wait out the entire 20 seconds on Iofi's special without drawing anything" },
	{ locationIndexEnum_FirstOptionOnly, "Clear a stage only choosing the first option when leveling up without rerolls" },
	{ locationIndexEnum_HardNoProjectiles, "Clear a Hard Stage without taking any damage from projectiles" },
	{ locationIndexEnum_MainWeaponLevel1Only, "Clear a stage with Main Weapon at level 1 only" },
	{ locationIndexEnum_ClearHardNoHealItems, "Clear a (Hard) stage without taking any Healing Items" },
	{ locationIndexEnum_500HP, "Have over 500 HP in 1 run" },
	{ locationIndexEnum_UsadaCasino, "Enter the Usada Casino" },
	{ locationIndexEnum_WinWorkerRace, "Win a Worker Race" },
	{ locationIndexEnum_WinWorkerFight, "Win a Worker Fight" },
	{ locationIndexEnum_Get100000UsaChips, "Get 100,000 UsaChips" },
	{ locationIndexEnum_GetAPet, "Get a Pet in Holo House" },
	{ locationIndexEnum_LoseWith0UsaChips, "Lose in a Casino game with 0 UsaChips remaining" },
	{ locationIndexEnum_10FanLetters, "Find 10 Fan Letters" },
	{ locationIndexEnum_Stage4HardNoQuestionsWrong, "Get no questions wrong in Stage 4 (Hard)" },
	{ locationIndexEnum_WinJackpot, "Win a Jackpot in slots" },
	{ locationIndexEnum_Sell10Stamps, "Sell 10 Stamps in 1 run" },
	{ locationIndexEnum_500PickUpRange, "Reach 500% Pick Up Range" },
	{ locationIndexEnum_3DeathChickenFeather, "Clear a Stage Mode run after dying 3 times with Chickens Feather" },
	{ locationIndexEnum_ClearTowerOfSuffering, "Clear the Tower of Suffering" },
	{ locationIndexEnum_GetSomeHelp, "Complete all achievements. Then go outside" },
	{ locationIndexEnum_SpecialAttackShop, "Buy Special Attack Upgrade" },
	{ locationIndexEnum_GrowthShop1, "Buy Growth Upgrade 1 time" },
	{ locationIndexEnum_GrowthShop2, "Buy Growth Upgrade 2 times" },
	{ locationIndexEnum_GrowthShop3, "Buy Growth Upgrade 3 times" },
	{ locationIndexEnum_RerollShop1, "Buy Reroll Upgrade 1 time" },
	{ locationIndexEnum_RerollShop2, "Buy Reroll Upgrade 2 times" },
	{ locationIndexEnum_RerollShop3, "Buy Reroll Upgrade 3 times" },
	{ locationIndexEnum_RerollShop4, "Buy Reroll Upgrade 4 times" },
	{ locationIndexEnum_RerollShop5, "Buy Reroll Upgrade 5 times" },
	{ locationIndexEnum_RerollShop6, "Buy Reroll Upgrade 6 times" },
	{ locationIndexEnum_RerollShop7, "Buy Reroll Upgrade 7 times" },
	{ locationIndexEnum_RerollShop8, "Buy Reroll Upgrade 8 times" },
	{ locationIndexEnum_RerollShop9, "Buy Reroll Upgrade 9 times" },
	{ locationIndexEnum_RerollShop10, "Buy Reroll Upgrade 10 times" },
	{ locationIndexEnum_EliminateShop1, "Buy Eliminate Upgrade 1 time" },
	{ locationIndexEnum_EliminateShop2, "Buy Eliminate Upgrade 2 times" },
	{ locationIndexEnum_EliminateShop3, "Buy Eliminate Upgrade 3 times" },
	{ locationIndexEnum_EliminateShop4, "Buy Eliminate Upgrade 4 times" },
	{ locationIndexEnum_EliminateShop5, "Buy Eliminate Upgrade 5 times" },
	{ locationIndexEnum_EliminateShop6, "Buy Eliminate Upgrade 6 times" },
	{ locationIndexEnum_EliminateShop7, "Buy Eliminate Upgrade 7 times" },
	{ locationIndexEnum_EliminateShop8, "Buy Eliminate Upgrade 8 times" },
	{ locationIndexEnum_EliminateShop9, "Buy Eliminate Upgrade 9 times" },
	{ locationIndexEnum_EliminateShop10, "Buy Eliminate Upgrade 10 times" },
	{ locationIndexEnum_HoldShop1, "Buy Hold Upgrade 1 time" },
	{ locationIndexEnum_HoldShop2, "Buy Hold Upgrade 2 times" },
	{ locationIndexEnum_HoldShop3, "Buy Hold Upgrade 3 times" },
	{ locationIndexEnum_HoldShop4, "Buy Hold Upgrade 4 times" },
	{ locationIndexEnum_HoldShop5, "Buy Hold Upgrade 5 times" },
	{ locationIndexEnum_CustomizeShop, "Buy Customize Upgrade" },
	{ locationIndexEnum_SupportsShop, "Buy Support Upgrade" },
	{ locationIndexEnum_MaterialFindShop, "Buy Material Upgrade" },
	{ locationIndexEnum_StampsShop, "Buy Stamp Upgrade" },
	{ locationIndexEnum_EnchantShop, "Buy Enchant Upgrade" },
	{ locationIndexEnum_FandomShop, "Buy Fandom Upgrade" },
	{ locationIndexEnum_FanLetterShop, "Buy Fan Letter Upgrade" },
	{ locationIndexEnum_MaxHPShop1, "Buy Max HP Upgrade 1 time" },
	{ locationIndexEnum_MaxHPShop2, "Buy Max HP Upgrade 2 times" },
	{ locationIndexEnum_MaxHPShop3, "Buy Max HP Upgrade 3 times" },
	{ locationIndexEnum_MaxHPShop4, "Buy Max HP Upgrade 4 times" },
	{ locationIndexEnum_MaxHPShop5, "Buy Max HP Upgrade 5 times" },
	{ locationIndexEnum_MaxHPShop6, "Buy Max HP Upgrade 6 times" },
	{ locationIndexEnum_MaxHPShop7, "Buy Max HP Upgrade 7 times" },
	{ locationIndexEnum_MaxHPShop8, "Buy Max HP Upgrade 8 times" },
	{ locationIndexEnum_MaxHPShop9, "Buy Max HP Upgrade 9 times" },
	{ locationIndexEnum_MaxHPShop10, "Buy Max HP Upgrade 10 times" },
	{ locationIndexEnum_ATKShop1, "Buy ATK Upgrade 1 time" },
	{ locationIndexEnum_ATKShop2, "Buy ATK Upgrade 2 times" },
	{ locationIndexEnum_ATKShop3, "Buy ATK Upgrade 3 times" },
	{ locationIndexEnum_ATKShop4, "Buy ATK Upgrade 4 times" },
	{ locationIndexEnum_ATKShop5, "Buy ATK Upgrade 5 times" },
	{ locationIndexEnum_ATKShop6, "Buy ATK Upgrade 6 times" },
	{ locationIndexEnum_ATKShop7, "Buy ATK Upgrade 7 times" },
	{ locationIndexEnum_ATKShop8, "Buy ATK Upgrade 8 times" },
	{ locationIndexEnum_ATKShop9, "Buy ATK Upgrade 9 times" },
	{ locationIndexEnum_ATKShop10, "Buy ATK Upgrade 10 times" },
	{ locationIndexEnum_SPDShop1, "Buy SPD Upgrade 1 time" },
	{ locationIndexEnum_SPDShop2, "Buy SPD Upgrade 2 times" },
	{ locationIndexEnum_SPDShop3, "Buy SPD Upgrade 3 times" },
	{ locationIndexEnum_SPDShop4, "Buy SPD Upgrade 4 times" },
	{ locationIndexEnum_SPDShop5, "Buy SPD Upgrade 5 times" },
	{ locationIndexEnum_SPDShop6, "Buy SPD Upgrade 6 times" },
	{ locationIndexEnum_SPDShop7, "Buy SPD Upgrade 7 times" },
	{ locationIndexEnum_SPDShop8, "Buy SPD Upgrade 8 times" },
	{ locationIndexEnum_SPDShop9, "Buy SPD Upgrade 9 times" },
	{ locationIndexEnum_SPDShop10, "Buy SPD Upgrade 10 times" },
	{ locationIndexEnum_CritShop1, "Buy Crit Upgrade 1 time" },
	{ locationIndexEnum_CritShop2, "Buy Crit Upgrade 2 times" },
	{ locationIndexEnum_CritShop3, "Buy Crit Upgrade 3 times" },
	{ locationIndexEnum_CritShop4, "Buy Crit Upgrade 4 times" },
	{ locationIndexEnum_CritShop5, "Buy Crit Upgrade 5 times" },
	{ locationIndexEnum_PickUpRangeShop1, "Buy Pick Up Range Upgrade 1 time" },
	{ locationIndexEnum_PickUpRangeShop2, "Buy Pick Up Range Upgrade 2 times" },
	{ locationIndexEnum_PickUpRangeShop3, "Buy Pick Up Range Upgrade 3 times" },
	{ locationIndexEnum_PickUpRangeShop4, "Buy Pick Up Range Upgrade 4 times" },
	{ locationIndexEnum_PickUpRangeShop5, "Buy Pick Up Range Upgrade 5 times" },
	{ locationIndexEnum_PickUpRangeShop6, "Buy Pick Up Range Upgrade 6 times" },
	{ locationIndexEnum_PickUpRangeShop7, "Buy Pick Up Range Upgrade 7 times" },
	{ locationIndexEnum_PickUpRangeShop8, "Buy Pick Up Range Upgrade 8 times" },
	{ locationIndexEnum_PickUpRangeShop9, "Buy Pick Up Range Upgrade 9 times" },
	{ locationIndexEnum_PickUpRangeShop10, "Buy Pick Up Range Upgrade 10 times" },
	{ locationIndexEnum_HasteShop1, "Buy Haste Upgrade 1 time" },
	{ locationIndexEnum_HasteShop2, "Buy Haste Upgrade 2 times" },
	{ locationIndexEnum_HasteShop3, "Buy Haste Upgrade 3 times" },
	{ locationIndexEnum_HasteShop4, "Buy Haste Upgrade 4 times" },
	{ locationIndexEnum_HasteShop5, "Buy Haste Upgrade 5 times" },
	{ locationIndexEnum_RegenShop1, "Buy Regen Upgrade 1 time" },
	{ locationIndexEnum_RegenShop2, "Buy Regen Upgrade 2 times" },
	{ locationIndexEnum_RegenShop3, "Buy Regen Upgrade 3 times" },
	{ locationIndexEnum_RegenShop4, "Buy Regen Upgrade 4 times" },
	{ locationIndexEnum_RegenShop5, "Buy Regen Upgrade 5 times" },
	{ locationIndexEnum_DefenseShop1, "Buy Defense Upgrade 1 time" },
	{ locationIndexEnum_DefenseShop2, "Buy Defense Upgrade 2 times" },
	{ locationIndexEnum_DefenseShop3, "Buy Defense Upgrade 3 times" },
	{ locationIndexEnum_DefenseShop4, "Buy Defense Upgrade 4 times" },
	{ locationIndexEnum_DefenseShop5, "Buy Defense Upgrade 5 times" },
	{ locationIndexEnum_SpecialCDRShop1, "Buy Special Cooldown Reduction Upgrade 1 time" },
	{ locationIndexEnum_SpecialCDRShop2, "Buy Special Cooldown Reduction Upgrade 2 times" },
	{ locationIndexEnum_SpecialCDRShop3, "Buy Special Cooldown Reduction Upgrade 3 times" },
	{ locationIndexEnum_SpecialCDRShop4, "Buy Special Cooldown Reduction Upgrade 4 times" },
	{ locationIndexEnum_SpecialCDRShop5, "Buy Special Cooldown Reduction Upgrade 5 times" },
	{ locationIndexEnum_SkillUpShop1, "Buy Skill Up Upgrade 1 time" },
	{ locationIndexEnum_SkillUpShop2, "Buy Skill Up Upgrade 2 times" },
	{ locationIndexEnum_SkillUpShop3, "Buy Skill Up Upgrade 3 times" },
	{ locationIndexEnum_SkillUpShop4, "Buy Skill Up Upgrade 4 times" },
	{ locationIndexEnum_SkillUpShop5, "Buy Skill Up Upgrade 5 times" },
	{ locationIndexEnum_SkillUpShop6, "Buy Skill Up Upgrade 6 times" },
	{ locationIndexEnum_SkillUpShop7, "Buy Skill Up Upgrade 7 times" },
	{ locationIndexEnum_SkillUpShop8, "Buy Skill Up Upgrade 8 times" },
	{ locationIndexEnum_SkillUpShop9, "Buy Skill Up Upgrade 9 times" },
	{ locationIndexEnum_SkillUpShop10, "Buy Skill Up Upgrade 10 times" },
	{ locationIndexEnum_EXPGainShop1, "Buy EXP Gain Upgrade 1 time" },
	{ locationIndexEnum_EXPGainShop2, "Buy EXP Gain Upgrade 2 times" },
	{ locationIndexEnum_EXPGainShop3, "Buy EXP Gain Upgrade 3 times" },
	{ locationIndexEnum_EXPGainShop4, "Buy EXP Gain Upgrade 4 times" },
	{ locationIndexEnum_EXPGainShop5, "Buy EXP Gain Upgrade 5 times" },
	{ locationIndexEnum_FoodShop1, "Buy Food Upgrade 1 time" },
	{ locationIndexEnum_FoodShop2, "Buy Food Upgrade 2 times" },
	{ locationIndexEnum_FoodShop3, "Buy Food Upgrade 3 times" },
	{ locationIndexEnum_FoodShop4, "Buy Food Upgrade 4 times" },
	{ locationIndexEnum_FoodShop5, "Buy Food Upgrade 5 times" },
	{ locationIndexEnum_MoneyGainShop1, "Buy Money Gain Upgrade 1 time" },
	{ locationIndexEnum_MoneyGainShop2, "Buy Money Gain Upgrade 2 times" },
	{ locationIndexEnum_MoneyGainShop3, "Buy Money Gain Upgrade 3 times" },
	{ locationIndexEnum_MoneyGainShop4, "Buy Money Gain Upgrade 4 times" },
	{ locationIndexEnum_MoneyGainShop5, "Buy Money Gain Upgrade 5 times" },
	{ locationIndexEnum_MoneyGainShop6, "Buy Money Gain Upgrade 6 times" },
	{ locationIndexEnum_MoneyGainShop7, "Buy Money Gain Upgrade 7 times" },
	{ locationIndexEnum_MoneyGainShop8, "Buy Money Gain Upgrade 8 times" },
	{ locationIndexEnum_MoneyGainShop9, "Buy Money Gain Upgrade 9 times" },
	{ locationIndexEnum_MoneyGainShop10, "Buy Money Gain Upgrade 10 times" },
	{ locationIndexEnum_EnhancementShop1, "Buy Enhancement Upgrade 1 time" },
	{ locationIndexEnum_EnhancementShop2, "Buy Enhancement Upgrade 2 times" },
	{ locationIndexEnum_EnhancementShop3, "Buy Enhancement Upgrade 3 times" },
	{ locationIndexEnum_EnhancementShop4, "Buy Enhancement Upgrade 4 times" },
	{ locationIndexEnum_EnhancementShop5, "Buy Enhancement Upgrade 5 times" },
	{ locationIndexEnum_MarketingShop1, "Buy Marketing Upgrade 1 time" },
	{ locationIndexEnum_MarketingShop2, "Buy Marketing Upgrade 2 times" },
	{ locationIndexEnum_MarketingShop3, "Buy Marketing Upgrade 3 times" },
	{ locationIndexEnum_MarketingShop4, "Buy Marketing Upgrade 4 times" },
	{ locationIndexEnum_MarketingShop5, "Buy Marketing Upgrade 5 times" },
};

std::unordered_map<itemIndexEnum, locationIndexEnum> shopItemToLocationMap
{
	{ itemIndexEnum_SpecialAttackShopUpgrade, locationIndexEnum_SpecialAttackShop },
	{ itemIndexEnum_GrowthProgressiveShopUpgrade, locationIndexEnum_GrowthShop1 },
	{ itemIndexEnum_RerollProgressiveShopUpgrade, locationIndexEnum_RerollShop1 },
	{ itemIndexEnum_EliminateProgressiveShopUpgrade, locationIndexEnum_EliminateShop1 },
	{ itemIndexEnum_HoldProgressiveShopUpgrade, locationIndexEnum_HoldShop1 },
	{ itemIndexEnum_CustomizeShopUpgrade, locationIndexEnum_CustomizeShop },
	{ itemIndexEnum_SupportsShopUpgrade, locationIndexEnum_SupportsShop },
	{ itemIndexEnum_MaterialShopUpgrade, locationIndexEnum_MaterialFindShop },
	{ itemIndexEnum_StampsShopUpgrade, locationIndexEnum_StampsShop },
	{ itemIndexEnum_EnchantmentsShopUpgrade, locationIndexEnum_EnchantShop },
	{ itemIndexEnum_FandomShopUpgrade, locationIndexEnum_FandomShop },
	{ itemIndexEnum_FanLettersShopUpgrade, locationIndexEnum_FanLetterShop },
	{ itemIndexEnum_MaxHPProgressiveShopUpgrade, locationIndexEnum_MaxHPShop1 },
	{ itemIndexEnum_ATKProgressiveShopUpgrade, locationIndexEnum_ATKShop1 },
	{ itemIndexEnum_SPDProgressiveShopUpgrade, locationIndexEnum_SPDShop1 },
	{ itemIndexEnum_CritProgressiveShopUpgrade, locationIndexEnum_CritShop1 },
	{ itemIndexEnum_PickUpProgressiveShopUpgrade, locationIndexEnum_PickUpRangeShop1 },
	{ itemIndexEnum_HasteProgressiveShopUpgrade, locationIndexEnum_HasteShop1 },
	{ itemIndexEnum_RegenProgressiveShopUpgrade, locationIndexEnum_RegenShop1 },
	{ itemIndexEnum_DefenseProgressiveShopUpgrade, locationIndexEnum_DefenseShop1 },
	{ itemIndexEnum_SpecialCooldownProgressiveShopUpgrade, locationIndexEnum_SpecialCDRShop1 },
	{ itemIndexEnum_SkillUpProgressiveShopUpgrade, locationIndexEnum_SkillUpShop1 },
	{ itemIndexEnum_EXPGainProgressiveShopUpgrade, locationIndexEnum_EXPGainShop1 },
	{ itemIndexEnum_FoodDropProgressiveShopUpgrade, locationIndexEnum_FoodShop1 },
	{ itemIndexEnum_MoneyGainProgressiveShopUpgrade, locationIndexEnum_MoneyGainShop1 },
	{ itemIndexEnum_EnhancementProgressiveShopUpgrade, locationIndexEnum_EnhancementShop1 },
	{ itemIndexEnum_MarketingProgressiveShopUpgrade, locationIndexEnum_MarketingShop1 },
};

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
		locationIndexEnum locationNumber = static_cast<locationIndexEnum>(getInstanceVariable(curAchievement, GML_achievementNumber).ToInt32() + 1);

		loggingCallback(std::format("Obtained achievement: {}", locationToNameMap[locationNumber]));
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
		RValue saveName = "ArchipelagoSave.dat";
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
		RValue** args = new RValue*[2];
		RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
		RValue saveName = "ArchipelagoSave.dat";
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