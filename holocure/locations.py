from __future__ import annotations
from rule_builder.rules import Has, HasAll, HasAny, And, Rule

from typing import TYPE_CHECKING

from BaseClasses import ItemClassification, Location

from . import items

if TYPE_CHECKING:
	from .world import HoloCureWorld

class LocationData:

	def __init__(self, location_id: int, location_name: str, region_name: str, required_items: Rule | None = None, count: int = 1):
		self.location_id = location_id
		self.location_name = location_name
		self.region_name = region_name
		self.required_items = required_items
		self.count = count

location_data = [
	LocationData(1, "Clear a Stage with Amelia Watson", "Menu", Has("Amelia Watson")),
	LocationData(2, "Reach Gachikoi with Amelia Watson", "Grindy", Has("Amelia Watson") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(3, "Clear a Stage with Gawr Gura", "Menu", Has("Gawr Gura")),
	LocationData(4, "Reach Gachikoi with Gawr Gura", "Grindy", Has("Gawr Gura") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(5, "Reach 10 minutes with Ninomae Inanis", "Menu", Has("Ninomae Inanis")),
	LocationData(6, "Clear a Stage with Ninomae Inanis", "Menu", Has("Ninomae Inanis")),
	LocationData(7, "Reach Gachikoi with Ninomae Inanis", "Grindy", Has("Ninomae Inanis") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(8, "Reach 10 minutes with Takanashi Kiara", "Menu", Has("Takanashi Kiara")),
	LocationData(9, "Clear a Stage with Takanashi Kiara", "Menu", Has("Takanashi Kiara")),
	LocationData(10, "Reach Gachikoi with Takanashi Kiara", "Grindy", Has("Takanashi Kiara") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(11, "Reach 10 minutes with Mori Calliope", "Menu", Has("Mori Calliope")),
	LocationData(12, "Clear a Stage with Mori Calliope", "Menu", Has("Mori Calliope")),
	LocationData(13, "Reach Gachikoi with Mori Calliope", "Grindy", Has("Mori Calliope") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(14, "Reach 10 minutes with Hakos Baelz", "Menu", Has("Hakos Baelz")),
	LocationData(15, "Clear a Stage with Hakos Baelz", "Menu", Has("Hakos Baelz")),
	LocationData(16, "Reach Gachikoi with Hakos Baelz", "Grindy", Has("Hakos Baelz") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(17, "Clear a Stage with Ouro Kronii", "Menu", Has("Ouro Kronii")),
	LocationData(18, "Reach Gachikoi with Ouro Kronii", "Grindy", Has("Ouro Kronii") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(19, "Clear a Stage with Ceres Fauna", "Menu", Has("Ceres Fauna")),
	LocationData(20, "Reach Gachikoi with Ceres Fauna", "Grindy", Has("Ceres Fauna") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(21, "Clear a Stage with Nanashi Mumei", "Menu", Has("Nanashi Mumei")),
	LocationData(22, "Reach Gachikoi with Nanashi Mumei", "Grindy", Has("Nanashi Mumei") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(23, "Reach 10 minutes with Tsukumo Sana", "Menu", Has("Tsukumo Sana")),
	LocationData(24, "Clear a Stage with Tsukumo Sana", "Menu", Has("Tsukumo Sana")),
	LocationData(25, "Reach Gachikoi with Tsukumo Sana", "Grindy", Has("Tsukumo Sana") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(26, "Reach 10 minutes with IRyS", "Menu", Has("IRyS")),
	LocationData(27, "Clear a Stage with IRyS", "Menu", Has("IRyS")),
	LocationData(28, "Reach Gachikoi with IRyS", "Grindy", Has("IRyS") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(29, "Clear a Stage with Shirakami Fubuki", "Menu", Has("Shirakami Fubuki")),
	LocationData(30, "Reach Gachikoi with Shirakami Fubuki", "Grindy", Has("Shirakami Fubuki") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(31, "Clear a Stage with Ookami Mio", "Menu", Has("Ookami Mio")),
	LocationData(32, "Reach Gachikoi with Ookami Mio", "Grindy", Has("Ookami Mio") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(33, "Clear a Stage with Nekomata Okayu", "Menu", Has("Nekomata Okayu")),
	LocationData(34, "Reach Gachikoi with Nekomata Okayu", "Grindy", Has("Nekomata Okayu") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(35, "Reach 10 minutes with Inugami Korone", "Menu", Has("Inugami Korone")),
	LocationData(36, "Clear a Stage with Inugami Korone", "Menu", Has("Inugami Korone")),
	LocationData(37, "Reach Gachikoi with Inugami Korone", "Grindy", Has("Inugami Korone") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(38, "Clear a Stage with Tokino Sora", "Menu", Has("Tokino Sora")),
	LocationData(39, "Reach Gachikoi with Tokino Sora", "Grindy", Has("Tokino Sora") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(40, "Clear a Stage with AZki", "Menu", Has("AZki")),
	LocationData(41, "Reach Gachikoi with AZki", "Grindy", Has("AZki") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(42, "Clear a Stage with Roboco-san", "Menu", Has("Roboco-san")),
	LocationData(43, "Reach Gachikoi with Roboco-san", "Grindy", Has("Roboco-san") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(44, "Clear a Stage with Hoshimachi Suisei", "Menu", Has("Hoshimachi Suisei")),
	LocationData(45, "Reach Gachikoi with Hoshimachi Suisei", "Grindy", Has("Hoshimachi Suisei") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(46, "Clear a Stage with Sakura Miko", "Menu", Has("Sakura Miko")),
	LocationData(47, "Reach Gachikoi with Sakura Miko", "Grindy", Has("Sakura Miko") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(48, "Clear a Stage with Akai Haato", "Menu", Has("Akai Haato")),
	LocationData(49, "Reach Gachikoi with Akai Haato", "Grindy", Has("Akai Haato") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(50, "Clear a Stage with Yozora Mel", "Menu", Has("Yozora Mel")),
	LocationData(51, "Reach Gachikoi with Yozora Mel", "Grindy", Has("Yozora Mel") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(52, "Clear a Stage with Natsuiro Matsuri", "Menu", Has("Natsuiro Matsuri")),
	LocationData(53, "Reach Gachikoi with Natsuiro Matsuri", "Grindy", Has("Natsuiro Matsuri") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(54, "Clear a Stage with Aki Rosenthal", "Menu", Has("Aki Rosenthal")),
	LocationData(55, "Reach Gachikoi with Aki Rosenthal", "Grindy", Has("Aki Rosenthal") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(56, "Clear a Stage with Yuzuki Choco", "Menu", Has("Yuzuki Choco")),
	LocationData(57, "Reach Gachikoi with Yuzuki Choco", "Grindy", Has("Yuzuki Choco") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(58, "Clear a Stage with Oozora Subaru", "Menu", Has("Oozora Subaru")),
	LocationData(59, "Reach Gachikoi with Oozora Subaru", "Grindy", Has("Oozora Subaru") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(60, "Reach 10 minutes with Murasaki Shion", "Menu", Has("Murasaki Shion")),
	LocationData(61, "Clear a Stage with Murasaki Shion", "Menu", Has("Murasaki Shion")),
	LocationData(62, "Reach Gachikoi with Murasaki Shion", "Grindy", Has("Murasaki Shion") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(63, "Clear a Stage with Nakiri Ayame", "Menu", Has("Nakiri Ayame")),
	LocationData(64, "Reach Gachikoi with Nakiri Ayame", "Grindy", Has("Nakiri Ayame") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(65, "Clear a Stage with Minato Aqua", "Menu", Has("Minato Aqua")),
	LocationData(66, "Reach Gachikoi with Minato Aqua", "Grindy", Has("Minato Aqua") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(67, "Clear a Stage with Moona Hoshinova", "Menu", Has("Moona Hoshinova")),
	LocationData(68, "Reach Gachikoi with Moona Hoshinova", "Grindy", Has("Moona Hoshinova") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(69, "Clear a Stage with Airani Iofifteen", "Menu", Has("Airani Iofifteen")),
	LocationData(70, "Reach Gachikoi with Airani Iofifteen", "Grindy", Has("Airani Iofifteen") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(71, "Clear a Stage with Ayunda Risu", "Menu", Has("Ayunda Risu")),
	LocationData(72, "Reach Gachikoi with Ayunda Risu", "Grindy", Has("Ayunda Risu") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(73, "Clear a Stage with Kureiji Ollie", "Menu", Has("Kureiji Ollie")),
	LocationData(74, "Reach 10 minutes with Kureiji Ollie", "Menu", Has("Kureiji Ollie")),
	LocationData(75, "Reach Gachikoi with Kureiji Ollie", "Grindy", Has("Kureiji Ollie") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(76, "Clear a Stage with Pavolia Reine", "Menu", Has("Pavolia Reine")),
	LocationData(77, "Reach Gachikoi with Pavolia Reine", "Grindy", Has("Pavolia Reine") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(78, "Clear a Stage with Anya Melfissa", "Menu", Has("Anya Melfissa")),
	LocationData(79, "Reach Gachikoi with Anya Melfissa", "Grindy", Has("Anya Melfissa") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(80, "Clear a Stage with Kobo Kanaeru", "Menu", Has("Kobo Kanaeru")),
	LocationData(81, "Reach Gachikoi with Kobo Kanaeru", "Grindy", Has("Kobo Kanaeru") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(82, "Clear a Stage with Kaela Kovalskia", "Menu", Has("Kaela Kovalskia")),
	LocationData(83, "Reach Gachikoi with Kaela Kovalskia", "Grindy", Has("Kaela Kovalskia") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(84, "Reach 10 minutes with Vestia Zeta", "Menu", Has("Vestia Zeta")),
	LocationData(85, "Clear a Stage with Vestia Zeta", "Menu", Has("Vestia Zeta")),
	LocationData(86, "Reach Gachikoi with Vestia Zeta", "Grindy", Has("Vestia Zeta") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(87, "Clear a Stage with Usada Pekora", "Menu", Has("Usada Pekora")),
	LocationData(88, "Reach Gachikoi with Usada Pekora", "Grindy", Has("Usada Pekora") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(89, "Clear a Stage with Shirogane Noel", "Menu", Has("Shirogane Noel")),
	LocationData(90, "Reach Gachikoi with Shirogane Noel", "Grindy", Has("Shirogane Noel") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(91, "Clear a Stage with Shiranui Flare", "Menu", Has("Shiranui Flare")),
	LocationData(92, "Reach Gachikoi with Shiranui Flare", "Grindy", Has("Shiranui Flare") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(93, "Clear a Stage with Houshou Marine", "Menu", Has("Houshou Marine")),
	LocationData(94, "Reach Gachikoi with Houshou Marine", "Grindy", Has("Houshou Marine") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(95, "Clear a Stage with Kiryu Coco", "Menu", Has("Kiryu Coco")),
	LocationData(96, "Reach Gachikoi with Kiryu Coco", "Grindy", Has("Kiryu Coco") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(97, "Clear a Stage with Amane Kanata", "Menu", Has("Amane Kanata")),
	LocationData(98, "Reach Gachikoi with Amane Kanata", "Grindy", Has("Amane Kanata") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(99, "Clear a Stage with Tsunomaki Watame", "Menu", Has("Tsunomaki Watame")),
	LocationData(100, "Reach Gachikoi with Tsunomaki Watame", "Grindy", Has("Tsunomaki Watame") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(101, "Clear a Stage with Tokoyami Towa", "Menu", Has("Tokoyami Towa")),
	LocationData(102, "Reach Gachikoi with Tokoyami Towa", "Grindy", Has("Tokoyami Towa") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(103, "Clear a Stage with Himemori Luna", "Menu", Has("Himemori Luna")),
	LocationData(104, "Reach Gachikoi with Himemori Luna", "Grindy", Has("Himemori Luna") & Has("Progressive Stage", 3) & Has("Progressive Stage (Hard)", 2)),
	LocationData(105, "Complete your first game", "Menu"),
	LocationData(106, "Defeat Fubura", "Stage 1"),
	LocationData(107, "Defeat the Boss of Stage 1", "Stage 1"),
	LocationData(108, "Defeat the Boss of Stage 2", "Stage 2", Has("ATK Progressive Shop Upgrade", 2) & Has("SPD Progressive Shop Upgrade", 2)),
	LocationData(109, "Defeat the Boss of Stage 3", "Stage 3", Has("ATK Progressive Shop Upgrade", 3) & Has("SPD Progressive Shop Upgrade", 3)),
	LocationData(110, "Defeat the Boss of Stage 4", "Stage 4", Has("ATK Progressive Shop Upgrade", 4) & Has("SPD Progressive Shop Upgrade", 4)),
	LocationData(111, "Defeat the Boss of Stage 5", "Stage 5", Has("ATK Progressive Shop Upgrade", 5) & Has("SPD Progressive Shop Upgrade", 5)),
	LocationData(112, "Defeat the Boss of Stage 1 (Hard)", "Stage 1 (Hard)", Has("ATK Progressive Shop Upgrade", 5) & Has("SPD Progressive Shop Upgrade", 5)),
	LocationData(113, "Defeat the Boss of Stage 2 (Hard)", "Stage 2 (Hard)", Has("ATK Progressive Shop Upgrade", 6) & Has("SPD Progressive Shop Upgrade", 6)),
	LocationData(114, "Defeat the Boss of Stage 3 (Hard)", "Stage 3 (Hard)", Has("ATK Progressive Shop Upgrade", 7) & Has("SPD Progressive Shop Upgrade", 7)),
	LocationData(115, "Defeat the Boss of Stage 4 (Hard)", "Stage 4 (Hard)", Has("ATK Progressive Shop Upgrade", 8) & Has("SPD Progressive Shop Upgrade", 8)),
	LocationData(116, "Clear a stage in Time Mode", "Time Mode"),
	LocationData(117, "Unlock all characters", "Menu", HasAll("Amelia Watson", "Gawr Gura", "Ninomae Inanis", "Takanashi Kiara", "Mori Calliope", "Hakos Baelz", "Ouro Kronii", "Ceres Fauna", "Nanashi Mumei", "Tsukumo Sana", "IRyS", "Shirakami Fubuki", "Ookami Mio", "Nekomata Okayu", "Inugami Korone", "Tokino Sora", "AZki", "Roboco-san", "Hoshimachi Suisei", "Sakura Miko", "Akai Haato", "Yozora Mel", "Natsuiro Matsuri", "Aki Rosenthal", "Yuzuki Choco", "Oozora Subaru", "Murasaki Shion", "Nakiri Ayame", "Minato Aqua", "Moona Hoshinova", "Airani Iofifteen", "Ayunda Risu", "Kureiji Ollie", "Pavolia Reine", "Anya Melfissa", "Kobo Kanaeru", "Kaela Kovalskia", "Vestia Zeta", "Usada Pekora", "Shirogane Noel", "Shiranui Flare", "Houshou Marine", "Kiryu Coco", "Amane Kanata", "Tsunomaki Watame", "Tokoyami Towa", "Himemori Luna")),
	LocationData(118, "Unlock and use a character's special", "Menu", Has("Special Attack Shop Upgrade")),
	LocationData(119, "Destroy a Yagoo Statue", "Menu"),
	LocationData(120, "Use an anvil", "Menu"),
	LocationData(121, "Reach 10 minutes with Cutting Board or related weapons using certain characters", "Menu", And(Has("Cutting Board"), HasAny("Amane Kanata", "Gawr Gura", "Hoshimachi Suisei", "Kobo Kanaeru", "Kureiji Ollie", "Murasaki Shion", "Natsuiro Matsuri", "Ninomae Inanis"))),
	LocationData(122, "Complete a stage using Plug-In Type Asacoco", "Menu", Has("Plug Type Asacoco")),
	LocationData(123, "Have 5000 coins", "Menu"),
	LocationData(124, "Have 1,000,000 coins", "Menu", And(Has("Super Chatto Time!"), Has("Money Gain Up Progressive Shop Upgrade", 8), Has("Progressive Stage (Hard)", 4))),
	LocationData(125, "Clear any stage while using Sake", "Menu", Has("Sake")),
	LocationData(126, "Reach level 50 in one game", "Menu"),
	LocationData(127, "Reach level 100 in one game", "Menu", And(Has("Study Glasses"), Has("EXP Gain Up Progressive Shop Upgrade", 5))),
	LocationData(128, "Defeat at least 5000 targets in a stage", "Menu", And(Has("Marketing Up Progressive Shop Upgrade", 5), Has("Halu"))),
	LocationData(129, "Be defeated while using Halu", "Menu", Has("Halu")),
	LocationData(130, "Eat over 50 hamburgers in one game", "Menu", Has("Uber Sheep")),
	LocationData(131, "Deal over 1000 damage in one attack", "Menu"),
	LocationData(132, "Deal over 10000 damage in one attack", "Menu", And(Has("ATK Progressive Shop Upgrade", 8), Has("Gorilla's Paw"))),
	LocationData(133, "Clear a game of Stage Mode without moving at all", "Menu", And(Has("Breastplate"), Has("Membership"))),
	LocationData(134, "Lose after 10 minutes in a game", "Menu"),
	LocationData(135, "Clear a game of Stage Mode without using Special after unlocking it", "Menu", Has("Special Attack Shop Upgrade")),
	LocationData(136, "Complete a stage while using Super Chatto Time", "Menu", Has("Super Chatto Time!")),
	LocationData(137, "Pet Bubba as Amelia Watson", "Menu", Has("Amelia Watson")),
	LocationData(138, "Get 4 Collab Weapons in 1 game", "Menu", And(Has("EXP Gain Up Progressive Shop Upgrade", 5), Has("Enhancement Rate Up Progressive Shop Upgrade", 5), Has("Blacksmith's Gear"), Has("Credit Card"))),
	LocationData(139, "Take a total of over 500 damage in one game", "Menu", And(Has("Breastplate"), Has("Membership"))),
	LocationData(140, "Enhance a weapon once", "Menu"),
	LocationData(141, "Defeat a Yagoo", "Menu"),
	LocationData(142, "Defeat a Golden Yagoo", "Menu"),
	LocationData(143, "Defeat a Silver Yagoo", "Menu"),
	LocationData(144, "Be defeated by a Yagoo", "Menu"),
	LocationData(145, "Open a Super Box", "Menu"),
	LocationData(146, "Drop a super item", "Menu"),
	LocationData(147, "Clear a stage in Hardcore Mode", "Menu", Has("Body Pillow")),
	LocationData(148, "Get a weapon to +10 enhancements", "Menu", And(Has("Enhancement Rate Up Progressive Shop Upgrade", 5), Has("Blacksmith's Gear"), Has("Credit Card"))),
	LocationData(149, "Clear with only your main weapon", "Menu", And(Has("ATK Progressive Shop Upgrade", 5), Has("SPD Progressive Shop Upgrade", 5), Has("Haste Up Progressive Shop Upgrade", 3))),
	LocationData(150, "Fail enhancements 5 times in 1 run", "Menu", HasAny("Blacksmith's Gear", "Credit Card")),
	LocationData(151, "Fail a +1 > +2 enhancing", "Menu"),
	LocationData(152, "Clear with Halu level 5", "Menu", Has("Halu")),
	LocationData(153, "Survive to 30 minutes with Halu level 5", "Menu", Has("Halu")),
	LocationData(154, "Defeat a 10 or 20-minute boss in under 10 seconds", "Menu", And(Has("ATK Progressive Shop Upgrade", 8), Has("Gorilla's Paw"), Has("EXP Gain Up Progressive Shop Upgrade", 3), Has("Marketing Up Progressive Shop Upgrade", 3))),
	LocationData(155, "Leave a boss alive for 5 minutes or more", "Menu"),
	LocationData(156, "Level up 5 times in a row in one second", "Menu", Has("Study Glasses")),
	LocationData(157, "Complete the Armory", "Menu", HasAll("Wamy Water", "Psycho Axe", "X-Potato", "Bounce Ball", "Sausage", "Glowstick", "Spider Cooking", "Plug Type Asacoco", "BL Book", "Elite Lava Bucket", "Holo Bomb", "Cutting Board", "Fan Beam", "Idol Song", "CEO's Tears", "EN's Curse", "Owl Dagger", "Energy Drink", "Plushie", "Limiter", "Beetle", "Kusogaki Shackles", "Ninja Headband", "Chicken's Feather", "Raven Feather", "Body Pillow", "Full Meal", "Piki Piki Piman", "Nurse's Horn", "Headphones", "Uber Sheep", "Knightly Milk", "Sake", "Face Mask", "Credit Card", "Gorilla's Paw", "Super Chatto Time!", "Halu", "Injection Type Asacoco", "Idol Costume", "GWS Pill", "Just Bandage", "Breastplate", "Study Glasses", "Blacksmith's Gear", "Hope Soda", "Stolen Piggy Bank", "Candy Kingdom Sweets", "Researcher's Coat", "Membership", "Devil Hat", "Focus Shades", "Corporation Pin", "Promise Tiara")),
	LocationData(158, "Watch the credits to the end", "Menu"),
	LocationData(159, "Get 100% crit chance in a single run", "Menu", And(Has("Study Glasses"), Has("Crit Progressive Shop Upgrade", 3))),
	LocationData(160, "Achieve 1m+ score in a single run", "Menu", And(Has("ATK Progressive Shop Upgrade", 5), Has("SPD Progressive Shop Upgrade", 5), Has("Haste Up Progressive Shop Upgrade", 3))),
	LocationData(161, "Watch the TV for 10 seconds", "Stage 2"),
	LocationData(162, "Don't take any damage for 5 minutes", "Menu", Has("SPD Progressive Shop Upgrade", 5)),
	LocationData(163, "Go to Holo House", "HoloHouse"),
	LocationData(164, "Annoy another member", "HoloHouse"),
	LocationData(165, "Harvest a plant", "HoloHouse"),
	LocationData(166, "Catch a Shiny fish", "HoloHouse"),
	LocationData(167, "Steal a fish from another Holo member", "HoloHouse"),
	LocationData(168, "Cook a dish", "HoloHouse"),
	LocationData(169, "Get 10 combos in the fishing minigame", "HoloHouse"),
	LocationData(170, "Get 50 combos in the fishing minigame", "HoloHouse"),
	LocationData(171, "Catch at least one of every kind of fish", "HoloHouse"),
	LocationData(172, "Harvest at least one of every kind of crop", "HoloHouse"),
	LocationData(173, "Level a worker to their maximum level", "HoloHouse"),
	LocationData(174, "Get Manager Level 4", "HoloHouse"),
	LocationData(175, "Retire a Worker", "HoloHouse"),
	LocationData(176, "Collect 100,000 HoloCoins from workers at once", "HoloHouse"),
	LocationData(177, "Huh?", "HoloHouse"),
	LocationData(178, "Clear a stage with no items", "Menu", And(Has("ATK Progressive Shop Upgrade", 5), Has("SPD Progressive Shop Upgrade", 5), Has("Haste Up Progressive Shop Upgrade", 5))),
	LocationData(179, "Use the Golden Hammer", "Menu"),
	LocationData(180, "Clear stage mode without having any Character Skills (Fandom off)", "Menu", And(Has("ATK Progressive Shop Upgrade", 3), Has("SPD Progressive Shop Upgrade", 3), Has("Haste Up Progressive Shop Upgrade", 2))),
	LocationData(181, "Choose the Haste Stat Up option 10 times when leveling up", "Menu", Has("Study Glasses")),
	LocationData(182, "Wait out the entire 20 seconds on Iofi's special without drawing anything", "Menu", Has("Airani Iofifteen")),
	LocationData(183, "Clear a stage only choosing the first option when leveling up without rerolls", "Menu"),
	LocationData(184, "Clear a Hard Stage without taking any damage from projectiles", "Menu", Has("Progressive Stage (Hard)")),
	LocationData(185, "Clear a stage with Main Weapon at level 1 only", "Menu", And(Has("ATK Progressive Shop Upgrade", 5), Has("SPD Progressive Shop Upgrade", 5), Has("Haste Up Progressive Shop Upgrade", 3))),
	LocationData(186, "Clear a (Hard) stage without taking any Healing Items", "Menu", Has("Progressive Stage (Hard)")),
	LocationData(187, "Have over 500 HP in 1 run", "Menu", And(Has("Max HP Progressive Shop Upgrade", 10), Has("Study Glasses"))),
	LocationData(188, "Enter the Usada Casino", "HoloHouse"),
	LocationData(189, "Win a Worker Race", "HoloHouse"),
	LocationData(190, "Win a Worker Fight", "HoloHouse"),
	LocationData(191, "Get 100,000 UsaChips", "HoloHouse"),
	LocationData(192, "Get a Pet in Holo House", "HoloHouse"),
	LocationData(193, "Lose in a Casino game with 0 UsaChips remaining", "HoloHouse"),
	LocationData(194, "Find 10 Fan Letters", "Menu", Has("Fan Letters Shop Upgrade")),
	LocationData(195, "Get no questions wrong in Stage 4 (Hard)", "Stage 4 (Hard)"),
	LocationData(196, "Win a Jackpot in slots", "HoloHouse"),
	LocationData(197, "Sell 10 Stamps in 1 run", "Menu", Has("Stamps Shop Upgrade")),
	LocationData(198, "Reach 500% Pick Up Range", "Menu", Has("Pick Up Range Progressive Shop Upgrade", 5)),
	LocationData(199, "Clear a Stage Mode run after dying 3 times with Chickens Feather", "Menu", Has("Chicken's Feather")),
	LocationData(200, "Clear the Tower of Suffering", "Grindy", Has("HoloHouse")),
	LocationData(201, "Complete all achievements. Then go outside", "Grindy", Has("Progressive Stage", 4) & Has("Progressive Stage (Hard)", 4)),
	LocationData(202, "Special Attack Shop Upgrade", "Shop"),
	LocationData(203, "Growth Shop Upgrade 1", "Shop"),
	LocationData(204, "Growth Shop Upgrade 2", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 3)) & Has("Money Gain Up Progressive Shop Upgrade", 5) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(205, "Growth Shop Upgrade 3", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(206, "Reroll Shop Upgrade 1", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(207, "Reroll Shop Upgrade 2", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(208, "Reroll Shop Upgrade 3", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(209, "Reroll Shop Upgrade 4", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 3)) & Has("Money Gain Up Progressive Shop Upgrade", 5) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(210, "Reroll Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(211, "Reroll Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 8) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(212, "Reroll Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 9) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(213, "Reroll Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(214, "Reroll Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(215, "Reroll Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(216, "Eliminate Shop Upgrade 1", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(217, "Eliminate Shop Upgrade 2", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(218, "Eliminate Shop Upgrade 3", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(219, "Eliminate Shop Upgrade 4", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 3)) & Has("Money Gain Up Progressive Shop Upgrade", 5) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(220, "Eliminate Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(221, "Eliminate Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 8) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(222, "Eliminate Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 9) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(223, "Eliminate Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(224, "Eliminate Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(225, "Eliminate Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(226, "Hold Shop Upgrade 1", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(227, "Hold Shop Upgrade 2", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 3)) & Has("Money Gain Up Progressive Shop Upgrade", 5) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(228, "Hold Shop Upgrade 3", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 8) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(229, "Hold Shop Upgrade 4", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(230, "Hold Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(231, "Customize Shop Upgrade", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(232, "Supports Shop Upgrade", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(233, "Material Find Shop Upgrade", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(234, "Stamps Shop Upgrade", "Shop"),
	LocationData(235, "Enchantments Shop Upgrade", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(236, "Fandom Shop Upgrade", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(237, "Fan Letters Shop Upgrade", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(238, "Max HP Shop Upgrade 1", "Shop"),
	LocationData(239, "Max HP Shop Upgrade 2", "Shop"),
	LocationData(240, "Max HP Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(241, "Max HP Shop Upgrade 4", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(242, "Max HP Shop Upgrade 5", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(243, "Max HP Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(244, "Max HP Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 9) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(245, "Max HP Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(246, "Max HP Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(247, "Max HP Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(248, "ATK Up Shop Upgrade 1", "Shop"),
	LocationData(249, "ATK Up Shop Upgrade 2", "Shop"),
	LocationData(250, "ATK Up Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(251, "ATK Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Stamps Shop Upgrade")),
	LocationData(252, "ATK Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 2)) & Has("Money Gain Up Progressive Shop Upgrade", 4) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(253, "ATK Up Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 9) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(254, "ATK Up Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(255, "ATK Up Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(256, "ATK Up Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(257, "ATK Up Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(258, "SPD Up Shop Upgrade 1", "Shop"),
	LocationData(259, "SPD Up Shop Upgrade 2", "Shop"),
	LocationData(260, "SPD Up Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(261, "SPD Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(262, "SPD Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(263, "SPD Up Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(264, "SPD Up Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 9) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(265, "SPD Up Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(266, "SPD Up Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(267, "SPD Up Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(268, "Crit Up Shop Upgrade 1", "Shop"),
	LocationData(269, "Crit Up Shop Upgrade 2", "Shop"),
	LocationData(270, "Crit Up Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(271, "Crit Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Stamps Shop Upgrade")),
	LocationData(272, "Crit Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 2)) & Has("Money Gain Up Progressive Shop Upgrade", 4) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(273, "Pick Up Range Shop Upgrade 1", "Shop"),
	LocationData(274, "Pick Up Range Shop Upgrade 2", "Shop"),
	LocationData(275, "Pick Up Range Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(276, "Pick Up Range Shop Upgrade 4", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(277, "Pick Up Range Shop Upgrade 5", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(278, "Pick Up Range Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(279, "Pick Up Range Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 9) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(280, "Pick Up Range Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(281, "Pick Up Range Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(282, "Pick Up Range Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(283, "Haste Shop Upgrade 1", "Shop"),
	LocationData(284, "Haste Shop Upgrade 2", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(285, "Haste Shop Upgrade 3", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(286, "Haste Shop Upgrade 4", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(287, "Haste Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(288, "Regeneration Shop Upgrade 1", "Shop"),
	LocationData(289, "Regeneration Shop Upgrade 2", "Shop"),
	LocationData(290, "Regeneration Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(291, "Regeneration Shop Upgrade 4", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(292, "Regeneration Shop Upgrade 5", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(293, "Defense Up Shop Upgrade 1", "Shop"),
	LocationData(294, "Defense Up Shop Upgrade 2", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(295, "Defense Up Shop Upgrade 3", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(296, "Defense Up Shop Upgrade 4", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(297, "Defense Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 7) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(298, "Special Cooldown Reduction Shop Upgrade 1", "Shop"),
	LocationData(299, "Special Cooldown Reduction Shop Upgrade 2", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(300, "Special Cooldown Reduction Shop Upgrade 3", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(301, "Special Cooldown Reduction Shop Upgrade 4", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(302, "Special Cooldown Reduction Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 7) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(303, "Skill Up Shop Upgrade 1", "Shop"),
	LocationData(304, "Skill Up Shop Upgrade 2", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(305, "Skill Up Shop Upgrade 3", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(306, "Skill Up Shop Upgrade 4", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(307, "Skill Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 7) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(308, "Skill Up Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(309, "Skill Up Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(310, "Skill Up Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(311, "Skill Up Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(312, "Skill Up Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(313, "EXP Gain Up Shop Upgrade 1", "Shop"),
	LocationData(314, "EXP Gain Up Shop Upgrade 2", "Shop"),
	LocationData(315, "EXP Gain Up Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(316, "EXP Gain Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Stamps Shop Upgrade")),
	LocationData(317, "EXP Gain Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 2)) & Has("Money Gain Up Progressive Shop Upgrade", 4) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(318, "Food Drop Up Shop Upgrade 1", "Shop"),
	LocationData(319, "Food Drop Up Shop Upgrade 2", "Shop"),
	LocationData(320, "Food Drop Up Shop Upgrade 3", "Shop"),
	LocationData(321, "Food Drop Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(322, "Food Drop Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 2)) & Has("Money Gain Up Progressive Shop Upgrade", 4) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(323, "Money Gain Up Shop Upgrade 1", "Shop"),
	LocationData(324, "Money Gain Up Shop Upgrade 2", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(325, "Money Gain Up Shop Upgrade 3", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(326, "Money Gain Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(327, "Money Gain Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 6) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(328, "Money Gain Up Shop Upgrade 6", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(329, "Money Gain Up Shop Upgrade 7", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(330, "Money Gain Up Shop Upgrade 8", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(331, "Money Gain Up Shop Upgrade 9", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(332, "Money Gain Up Shop Upgrade 10", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 4)) & Has("Money Gain Up Progressive Shop Upgrade", 10) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(333, "Enhancement Rate Up Shop Upgrade 1", "Shop"),
	LocationData(334, "Enhancement Rate Up Shop Upgrade 2", "Shop"),
	LocationData(335, "Enhancement Rate Up Shop Upgrade 3", "Shop", Has("Stamps Shop Upgrade")),
	LocationData(336, "Enhancement Rate Up Shop Upgrade 4", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Stamps Shop Upgrade")),
	LocationData(337, "Enhancement Rate Up Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 2)) & Has("Money Gain Up Progressive Shop Upgrade", 4) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(338, "Marketing Shop Upgrade 1", "Shop", Has("Progressive Stage", 2) & Has("Money Gain Up Progressive Shop Upgrade", 1) & Has("Stamps Shop Upgrade")),
	LocationData(339, "Marketing Shop Upgrade 2", "Shop", Has("Progressive Stage", 3) & Has("Money Gain Up Progressive Shop Upgrade", 2) & Has("Stamps Shop Upgrade")),
	LocationData(340, "Marketing Shop Upgrade 3", "Shop", (Has("Progressive Stage", 4) | Has("Progressive Stage (Hard)", 1)) & Has("Money Gain Up Progressive Shop Upgrade", 3) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(341, "Marketing Shop Upgrade 4", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 2)) & Has("Money Gain Up Progressive Shop Upgrade", 4) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
	LocationData(342, "Marketing Shop Upgrade 5", "Shop", (Has("Progressive Stage", 5) | Has("Progressive Stage (Hard)", 3)) & Has("Money Gain Up Progressive Shop Upgrade", 5) & Has("Super Chatto Time!") & Has("Stamps Shop Upgrade")),
]


# Each Location instance must correctly report the "game" it belongs to.
# To make this simple, it is common practice to subclass the basic Location class and override the "game" field.
class HoloCureLocation(Location):
	game = "HoloCure"


def create_all_locations(world: HoloCureWorld) -> None:
	create_regular_locations(world)
	create_events(world)


def create_regular_locations(world: HoloCureWorld) -> None:
	# Finally, we need to put the Locations ("checks") into their regions.
	# Once again, before we do anything, we can grab our regions we created by using world.get_region()
	menu = world.get_region("Menu")
	holo_house = world.get_region("HoloHouse")
	grindy = world.get_region("Grindy")
	shop = world.get_region("Shop")
	stage1 = world.get_region("Stage 1")
	stage2 = world.get_region("Stage 2")
	stage3 = world.get_region("Stage 3")
	stage4 = world.get_region("Stage 4")
	stage5 = world.get_region("Stage 5")
	stage1_hard = world.get_region("Stage 1 (Hard)")
	stage2_hard = world.get_region("Stage 2 (Hard)")
	stage3_hard = world.get_region("Stage 3 (Hard)")
	stage4_hard = world.get_region("Stage 4 (Hard)")
	timemode = world.get_region("Time Mode")

	menu_locations = {}
	holo_house_locations = {}
	grindy_locations = {}
	shop_locations = {}
	stage1_locations = {}
	stage2_locations = {}
	stage3_locations = {}
	stage4_locations = {}
	stage5_locations = {}
	stage1_hard_locations = {}
	stage2_hard_locations = {}
	stage3_hard_locations = {}
	stage4_hard_locations = {}
	timemode_locations = {}

	for cur_location_data in location_data:
		for cur_count in range(cur_location_data.count):
			if cur_location_data.count == 1:
				cur_location_name = cur_location_data.location_name
			else:
				cur_location_name = cur_location_data.location_name + " " + str(cur_count + 1)
			if cur_location_data.region_name == "Menu":
				menu_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "HoloHouse":
				holo_house_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Grindy":
				grindy_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Shop":
				shop_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 1":
				stage1_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 2":
				stage2_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 3":
				stage3_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 4":
				stage4_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 5":
				stage5_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 1 (Hard)":
				stage1_hard_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 2 (Hard)":
				stage2_hard_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 3 (Hard)":
				stage3_hard_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Stage 4 (Hard)":
				stage4_hard_locations[cur_location_name] = cur_location_data.location_id + cur_count
			elif cur_location_data.region_name == "Time Mode":
				timemode_locations[cur_location_name] = cur_location_data.location_id + cur_count

	if world.options.grindy_checks:
		grindy.add_locations(grindy_locations, HoloCureLocation)
	menu.add_locations(menu_locations, HoloCureLocation)
	holo_house.add_locations(holo_house_locations, HoloCureLocation)
	shop.add_locations(shop_locations, HoloCureLocation)
	stage1.add_locations(stage1_locations, HoloCureLocation)
	stage2.add_locations(stage2_locations, HoloCureLocation)
	stage3.add_locations(stage3_locations, HoloCureLocation)
	stage4.add_locations(stage4_locations, HoloCureLocation)
	stage5.add_locations(stage5_locations, HoloCureLocation)
	stage1_hard.add_locations(stage1_hard_locations, HoloCureLocation)
	stage2_hard.add_locations(stage2_hard_locations, HoloCureLocation)
	stage3_hard.add_locations(stage3_hard_locations, HoloCureLocation)
	stage4_hard.add_locations(stage4_hard_locations, HoloCureLocation)
	timemode.add_locations(timemode_locations, HoloCureLocation)


def create_events(world: HoloCureWorld) -> None:
	return
	# Sometimes, the player may perform in-game actions that allow them to progress which are not related to Items.
	# In our case, the player must press a button in the top left room to open the final boss door.
	# AP has something for this purpose: "Event locations" and "Event items".
	# An event location is no different than a regular location, except it has the address "None".
	# It is treated during generation like any other location, but then it is discarded.
	# This location cannot be "sent" and its item cannot be "received", but the item can be used in logic rules.
	# Since we are creating more locations and adding them to regions, we need to grab those regions again first.
	#      top_left_room = world.get_region("Top Left Room")
	#    final_boss_room = world.get_region("Final Boss Room")

	# One way to create an event is simply to use one of the normal methods of creating a location.
#    button_in_top_left_room = APQuestLocation(world.player, "Top Left Room Button", None, top_left_room)
#    top_left_room.locations.append(button_in_top_left_room)

	# We then need to put an event item onto the location.
	# An event item is an item whose code is "None" (same as the event location's address),
	# and whose classification is "progression". Item creation will be discussed more in items.py.
	# Note: Usually, items are created in world.create_items(), which for us happens in items.py.
	# However, when the location of an item is known ahead of time (as is the case with an event location/item pair),
	# it is common practice to create the item when creating the location.
	# Since locations also have to be finalized after world.create_regions(), which runs before world.create_items(),
	# we'll create both the event location and the event item in our locations.py code.
#    button_item = items.APQuestItem("Top Left Room Button Pressed", ItemClassification.progression, None, world.player)
#    button_in_top_left_room.place_locked_item(button_item)

	# A way simpler way to do create an event location/item pair is by using the region.create_event helper.
	# Luckily, we have another event we want to create: The Victory event.
	# We will use this event to track whether the player can win the game.
	# The Victory event is a completely optional abstraction - This will be discussed more in set_rules().
#    final_boss_room.add_event(
#        "Final Boss Defeated", "Victory", location_type=APQuestLocation, item_type=items.APQuestItem
#    )

	# If you create all your regions and locations line-by-line like this,
	# the length of your create_regions might get out of hand.
	# Many worlds use more data-driven approaches using dataclasses or NamedTuples.
	# However, it is worth understanding how the actual creation of regions and locations works,
	# That way, we're not just mindlessly copy-pasting! :)
