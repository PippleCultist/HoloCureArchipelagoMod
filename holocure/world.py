from collections.abc import Mapping
from typing import Any

from rule_builder.rules import HasAll
# Imports of base Archipelago modules must be absolute.
from worlds.AutoWorld import World

# Imports of your world's files must be relative.
from . import items, locations, regions, rules, web_world
from . import options as holocure_options  # rename due to a name conflict with World.options
from .locations import location_data
from settings import get_settings

import typing
import os
import settings
import logging

from typing import ClassVar

# APQuest will go through all the parts of the world api one step at a time,
# with many examples and comments across multiple files.
# If you'd rather read one continuous document, or just like reading multiple sources,
# we also have this document specifying the entire world api:
# https://github.com/ArchipelagoMW/Archipelago/blob/main/docs/world%20api.md

class HoloCureSettings(settings.Group):
	class EnableLocationHints(settings.Bool):
		"""Enable to allow location hints to be freely viewable by the player"""

	enable_location_hints: typing.Union[EnableLocationHints, bool] = False

# The world class is the heart and soul of an apworld implementation.
# It holds all the data and functions required to build the world and submit it to the multiworld generator.
# You could have all your world code in just this one class, but for readability and better structure,
# it is common to split up world functionality into multiple files.
# This implementation in particular has the following additional files, each covering one topic:
# regions.py, locations.py, rules.py, items.py, options.py and web_world.py.
# It is recommended that you read these in that specific order, then come back to the world class.
class HoloCureWorld(World):
	"""
	HoloCure is a game inspired by Vampire Survivors with the Hololive Production Streamers as playable characters.
	"""

	# The docstring should contain a description of the game, to be displayed on the WebHost.

	# You must override the "game" field to say the name of the game.
	game = "HoloCure"
	settings_key = "holocure_options"
	settings: ClassVar[HoloCureSettings]
	ut_can_gen_without_yaml = True

	# The WebWorld is a definition class that governs how this world will be displayed on the website.
	web = web_world.HoloCureWebWorld()

	# This is how we associate the options defined in our options.py with our world.
	# (Note: options.py has been imported as "apquest_options" at the top of this file to avoid a name conflict)
	options_dataclass = holocure_options.HoloCureOptions
	options: holocure_options.HoloCureOptions  # Common mistake: This has to be a colon (:), not an equals sign (=).

	# Our world class must have a static location_name_to_id and item_name_to_id defined.
	# We define these in regions.py and items.py respectively, so we just set them here.
	LOCATION_NAME_TO_ID = {}

	for cur_location_data in location_data:
		if cur_location_data.count == 1:
			LOCATION_NAME_TO_ID[cur_location_data.location_name] = cur_location_data.location_id
		else:
			for cur_count in range(cur_location_data.count):
				LOCATION_NAME_TO_ID[cur_location_data.location_name + " " + str(cur_count + 1)] = cur_location_data.location_id + cur_count

	location_name_to_id = LOCATION_NAME_TO_ID
	item_name_to_id = items.ITEM_NAME_TO_ID

	# There is always one region that the generator starts from & assumes you can always go back to.
	# This defaults to "Menu", but you can change it by overriding origin_region_name.
	origin_region_name = "Menu"

	@staticmethod
	def interpret_slot_data(slot_data: dict[str, Any]) -> dict[str, Any]:
		return slot_data

	def generate_early(self) -> None:
		from .options import EndGoal

		self.location_data_is_enabled = {}

		self.valid_locations = []

		re_gen_passthrough = getattr(self.multiworld, "re_gen_passthrough", {})
		if re_gen_passthrough and self.game in re_gen_passthrough:
			# Get the passed through slot data from the real generation
			slot_data: dict[str, Any] = re_gen_passthrough[self.game]

			self.achievement_locations = slot_data["achievement_locations"]
			self.options.end_goal.value = slot_data["end_goal"]
			self.options.grindy_checks.value = slot_data["grindy_checks"]
			self.options.enable_stage.value = slot_data["enable_stage"]
			self.options.enable_holo_house_randomization.value = slot_data["enable_holo_house_randomization"]
			self.options.enable_unique_enemy_checks.value = slot_data["enable_unique_enemy_checks"]
			self.options.hololive_member_include_list.value = slot_data["hololive_member_include_list"]
			self.options.hololive_member_goal.value = slot_data["hololive_member_goal"]
			self.options.achievement_goal.value = slot_data["achievement_goal"]


		logger = logging.getLogger()
		if not self.options.enable_holo_house_randomization and not self.options.enable_stage:
			logger.warning("HoloHouse and Stage are both disabled which causes an impossible apworld. Enabling Stage to fix this")
			self.options.enable_stage.value = True

		if (self.options.end_goal == EndGoal.option_stage or self.options.end_goal == EndGoal.option_stage_hard) and not self.options.enable_stage:
			logger.warning("Stage is disabled with clearing Stage as the goal which causes an impossible apworld. Enabling Stage to fix this")
			self.options.enable_stage.value = True

		if len(self.options.hololive_member_exclude_list.value) == 47:
			logger.warning("Exclude list contains every hololive member which causes an impossible apworld. Disabling exclude list")
			self.options.hololive_member_exclude_list.value = []

		if self.options.end_goal == EndGoal.option_stage_member:
			if self.options.item_pool_hololive_member_count < self.options.hololive_member_goal:
				logger.warning("Item pool contains fewer hololive members than the goal which causes an impossible apworld. Lowering goal")
				self.options.hololive_member_goal.value = self.options.item_pool_hololive_member_count.value
			if 47 - len(self.options.hololive_member_exclude_list.value) < self.options.hololive_member_goal:
				logger.warning("Exclude list causes fewer hololive members than the goal which causes an impossible apworld. Lowering goal")
				self.options.hololive_member_goal.value = 47 - len(self.options.hololive_member_exclude_list.value)

		if self.options.end_goal == EndGoal.option_achievement and self.options.achievement_count < self.options.achievement_goal:
			logger.warning("There are fewer achievements than the goal which causes an impossible apworld. Lowering goal")
			self.options.achievement_goal.value = self.options.achievement_count.value

		if not getattr(self.multiworld, "generation_is_fake", False):
			self.achievement_locations = []
			char_list = ["Amelia Watson", "Gawr Gura", "Ninomae Inanis", "Takanashi Kiara", "Mori Calliope", "Hakos Baelz",
	"Ouro Kronii", "Ceres Fauna", "Nanashi Mumei", "Tsukumo Sana", "IRyS", "Shirakami Fubuki", "Ookami Mio",
	"Nekomata Okayu", "Inugami Korone", "Tokino Sora", "AZki", "Roboco-san", "Hoshimachi Suisei", "Sakura Miko",
	"Akai Haato", "Yozora Mel", "Natsuiro Matsuri", "Aki Rosenthal", "Yuzuki Choco", "Oozora Subaru", "Murasaki Shion",
	"Nakiri Ayame", "Minato Aqua", "Moona Hoshinova", "Airani Iofifteen", "Ayunda Risu", "Kureiji Ollie", "Pavolia Reine",
	"Anya Melfissa", "Kobo Kanaeru", "Kaela Kovalskia", "Vestia Zeta", "Usada Pekora", "Shirogane Noel", "Shiranui Flare",
	"Houshou Marine", "Kiryu Coco", "Amane Kanata", "Tsunomaki Watame", "Tokoyami Towa", "Himemori Luna"]
			[char_list.remove(curChar) for curChar in self.options.hololive_member_include_list.value]
			[char_list.remove(curChar) for curChar in self.options.hololive_member_exclude_list.value if curChar not in self.options.hololive_member_include_list.value]
			random_char_list = self.random.sample(char_list, min(len(char_list), max(0, self.options.item_pool_hololive_member_count - len(self.options.hololive_member_include_list.value))))
			[self.options.hololive_member_include_list.value.add(curChar) for curChar in random_char_list]

	# Our world class must have certain functions ("steps") that get called during generation.
	# The main ones are: create_regions, set_rules, create_items.
	# For better structure and readability, we put each of these in their own file.
	def create_regions(self) -> None:
		regions.create_and_connect_regions(self)
		locations.create_all_locations(self)

	def set_rules(self) -> None:
		rules.set_all_rules(self)

	def create_items(self) -> None:
		items.create_all_items(self)

	# Our world class must also have a create_item function that can create any one of our items by name at any time.
	# We also put this in a different file, the same one that create_items is in.
	def create_item(self, name: str) -> items.HoloCureItem:
		return items.create_item_with_correct_classification(self, name)

	# For features such as item links and panic-method start inventory, AP may ask your world to create extra filler.
	# The way it does this is by calling get_filler_item_name.
	# For this purpose, your world *must* have at least one infinitely repeatable item (usually filler).
	# You must override this function and return this infinitely repeatable item's name.
	# In our case, we defined a function called get_random_filler_item_name for this purpose in our items.py.
	def get_filler_item_name(self) -> str:
		return items.get_random_filler_item_name(self)

	# There may be data that the game client will need to modify the behavior of the game.
	# This is what slot_data exists for. Upon every client connection, the slot's slot_data is sent to the client.
	# slot_data is just a dictionary using basic types, that will be converted to json when sent to the client.
	def fill_slot_data(self) -> Mapping[str, Any]:
		# If you need access to the player's chosen options on the client side, there is a helper for that.
		slot_data_dict = self.options.as_dict(
			"end_goal", "grindy_checks", "enable_stage", "enable_holo_house_randomization", "enable_unique_enemy_checks", "hololive_member_include_list", "hololive_member_goal", "achievement_goal"
		)
		settings: HoloCureSettings = get_settings().holocure_options
		slot_data_dict["enable_location_hints"] = settings["enable_location_hints"]
		slot_data_dict["achievement_locations"] = self.achievement_locations
		return slot_data_dict
