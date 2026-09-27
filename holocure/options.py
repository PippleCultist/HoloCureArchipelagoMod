from dataclasses import dataclass

from Options import Choice, OptionGroup, PerGameCommonOptions, Range, Toggle, DefaultOnToggle, OptionSet

# In this file, we define the options the player can pick.
# The most common types of options are Toggle, Range and Choice.

# Options will be in the game's template yaml.
# They will be represented by checkboxes, sliders etc. on the game's options page on the website.
# (Note: Options can also be made invisible from either of these places by overriding Option.visibility.
#  APQuest doesn't have an example of this, but this can be used for secret / hidden / advanced options.)

# For further reading on options, you can also read the Options API Document:
# https://github.com/ArchipelagoMW/Archipelago/blob/main/docs/options%20api.md


class EndGoal(Choice):
	"""The end goal required to beat the game.
	Stage: Beat all 5 normal stages

	Stage Hard: Beat all 4 hard stages

	Shop: Buy out every shop upgrade

	Stage Member: Beat stages with enough unique hololive members

	Achievement: Obtain enough achievements"""
	display_name = "End Goal"
	option_stage = 1
	option_stage_hard = 2
	option_shop = 3
	option_stage_member = 4
	option_achievement = 5
	default = 1

class HololiveMemberGoal(Range):
	"""
	The amount of unique hololive member clears needed for the goal
	"""
	display_name = "Hololive Member Goal"
	range_start = 1
	range_end = 47
	default = 15

class AchievementGoal(Range):
	"""
	The amount of unique hololive member clears needed for the goal
	"""
	display_name = "Achievement Goal"
	range_start = 1
	range_end = 201
	default = 70

# The first type of Option we'll discuss is the Toggle.
# A toggle is an option that can either be on or off. This will be represented by a checkbox on the website.
# The default for a toggle is "off".
# If you want a toggle to be on by default, you can use the "DefaultOnToggle" class instead of the "Toggle" class.
class GrindyChecks(Toggle):
	"""
	Controls if gachikoi, get some help, and tower of suffering are considered as checks
	"""

	# The docstring of an option is used as the description on the website and in the template yaml.

	# You'll also want to set a display name, which will determine what the option is called on the website.
	display_name = "Grindy Checks"

class EnableStage(DefaultOnToggle):
	"""
	Controls if stage mode is enabled or not
	"""

	display_name = "Enable Stage"

class EnableHoloHouseRandomization(DefaultOnToggle):
	"""
	Controls if HoloHouse randomization and new HoloHouse checks is enabled or not
	"""

	display_name = "Enable HoloHouse Randomization"

class EnableUniqueEnemyChecks(Toggle):
	"""
	Controls if enemy checks is enabled or not
	"""

	display_name = "Enable Unique Enemy Checks"

class HololiveMemberWhitelist(OptionSet):
	"""Only allow Hololive member as showing up as items
	
	Amelia Watson, Gawr Gura, Ninomae Inanis, Takanashi Kiara, Mori Calliope, Hakos Baelz, Ouro Kronii, Ceres Fauna, Nanashi Mumei
	Tsukumo Sana, IRyS, Shirakami Fubuki, Ookami Mio, Nekomata Okayu, Inugami Korone, Tokino Sora, AZki, Roboco-san, Hoshimachi Suisei
	Sakura Miko, Akai Haato, Yozora Mel, Natsuiro Matsuri, Aki Rosenthal, Yuzuki Choco, Oozora Subaru, Murasaki Shion, Nakiri Ayame
	Minato Aqua, Moona Hoshinova, Airani Iofifteen, Ayunda Risu, Kureiji Ollie, Pavolia Reine, Anya Melfissa, Kobo Kanaeru
	Kaela Kovalskia, Vestia Zeta, Usada Pekora, Shirogane Noel, Shiranui Flare, Houshou Marine, Kiryu Coco, Amane Kanata, Tsunomaki Watame
	Tokoyami Towa, Himemori Luna
	"""

	rich_text_doc = True
	display_name = "Hololive Member Whitelist"
	valid_keys = ["Amelia Watson", "Gawr Gura", "Ninomae Inanis", "Takanashi Kiara", "Mori Calliope", "Hakos Baelz",
	"Ouro Kronii", "Ceres Fauna", "Nanashi Mumei", "Tsukumo Sana", "IRyS", "Shirakami Fubuki", "Ookami Mio",
	"Nekomata Okayu", "Inugami Korone", "Tokino Sora", "AZki", "Roboco-san", "Hoshimachi Suisei", "Sakura Miko",
	"Akai Haato", "Yozora Mel", "Natsuiro Matsuri", "Aki Rosenthal", "Yuzuki Choco", "Oozora Subaru", "Murasaki Shion",
	"Nakiri Ayame", "Minato Aqua", "Moona Hoshinova", "Airani Iofifteen", "Ayunda Risu", "Kureiji Ollie", "Pavolia Reine",
	"Anya Melfissa", "Kobo Kanaeru", "Kaela Kovalskia", "Vestia Zeta", "Usada Pekora", "Shirogane Noel", "Shiranui Flare",
	"Houshou Marine", "Kiryu Coco", "Amane Kanata", "Tsunomaki Watame", "Tokoyami Towa", "Himemori Luna"]
	default = frozenset({"Amelia Watson", "Gawr Gura", "Ninomae Inanis", "Takanashi Kiara", "Mori Calliope", "Hakos Baelz",
	"Ouro Kronii", "Ceres Fauna", "Nanashi Mumei", "Tsukumo Sana", "IRyS", "Shirakami Fubuki", "Ookami Mio",
	"Nekomata Okayu", "Inugami Korone", "Tokino Sora", "AZki", "Roboco-san", "Hoshimachi Suisei", "Sakura Miko",
	"Akai Haato", "Yozora Mel", "Natsuiro Matsuri", "Aki Rosenthal", "Yuzuki Choco", "Oozora Subaru", "Murasaki Shion",
	"Nakiri Ayame", "Minato Aqua", "Moona Hoshinova", "Airani Iofifteen", "Ayunda Risu", "Kureiji Ollie", "Pavolia Reine",
	"Anya Melfissa", "Kobo Kanaeru", "Kaela Kovalskia", "Vestia Zeta", "Usada Pekora", "Shirogane Noel", "Shiranui Flare",
	"Houshou Marine", "Kiryu Coco", "Amane Kanata", "Tsunomaki Watame", "Tokoyami Towa", "Himemori Luna"})

# We must now define a dataclass inheriting from PerGameCommonOptions that we put all our options in.
# This is in the format "option_name_in_snake_case: OptionClassName".
@dataclass
class HoloCureOptions(PerGameCommonOptions):
	end_goal: EndGoal
	grindy_checks: GrindyChecks
	enable_stage: EnableStage
	enable_holo_house_randomization: EnableHoloHouseRandomization
	enable_unique_enemy_checks: EnableUniqueEnemyChecks
	hololive_member_whitelist: HololiveMemberWhitelist
	hololive_member_goal: HololiveMemberGoal
	achievement_goal: AchievementGoal


# If we want to group our options by similar type, we can do so as well. This looks nice on the website.
option_groups = [
	OptionGroup(
		"Gameplay Options",
		[EndGoal, GrindyChecks, EnableStage, EnableHoloHouseRandomization, EnableUniqueEnemyChecks, HololiveMemberWhitelist, HololiveMemberGoal, AchievementGoal],
	),
]

# Finally, we can define some option presets if we want the player to be able to quickly choose a specific "mode".
option_presets = {
	"default": {
		"end_goal": EndGoal.option_stage,
		"grindy_checks": False,
		"enable_stage": True,
		"enable_holo_house_randomization": False,
		"enable_unique_enemy_checks": False,
	},
	"holoHouse": {
		"end_goal": EndGoal.option_shop,
		"grindy_checks": False,
		"enable_stage": False,
		"enable_holo_house_randomization": True,
		"enable_unique_enemy_checks": False,
	},
	"grind": {
		"end_goal": EndGoal.option_stage_hard,
		"grindy_checks": True,
		"enable_stage": True,
		"enable_holo_house_randomization": True,
		"enable_unique_enemy_checks": True,
	},
}
