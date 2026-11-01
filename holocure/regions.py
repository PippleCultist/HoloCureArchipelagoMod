from __future__ import annotations

from typing import TYPE_CHECKING

from BaseClasses import Entrance, Region

if TYPE_CHECKING:
	from .world import HoloCureWorld

from .options import EndGoal

# A region is a container for locations ("checks"), which connects to other regions via "Entrance" objects.
# Many games will model their Regions after physical in-game places, but you can also have more abstract regions.
# For a location to be in logic, its containing region must be reachable.
# The Entrances connecting regions can have rules - more on that in rules.py.
# This makes regions especially useful for traversal logic ("Can the player reach this part of the map?")

# Every location must be inside a region, and you must have at least one region.
# This is why we create regions first, and then later we create the locations (in locations.py).


def create_and_connect_regions(world: HoloCureWorld) -> None:
	create_all_regions(world)
	connect_regions(world)


def create_all_regions(world: HoloCureWorld) -> None:
	from .rules import is_stage_enabled, is_holo_house_enabled
	# Creating a region is as simple as calling the constructor of the Region class.
	menu = Region("Menu", world.player, world.multiworld)
	shop = Region("Shop", world.player, world.multiworld)
	regions = [menu, shop]

	if is_holo_house_enabled(world):
		regions.append(Region("HoloHouse", world.player, world.multiworld))

	if is_stage_enabled(world):
		if world.options.enable_unique_enemy_checks:
			regions.append(Region("StageEnemyCheck", world.player, world.multiworld))
		regions.append(Region("Stage", world.player, world.multiworld))
		regions.append(Region("Stage 1", world.player, world.multiworld))
		regions.append(Region("Stage 2", world.player, world.multiworld))
		regions.append(Region("Stage 3", world.player, world.multiworld))
		regions.append(Region("Stage 4", world.player, world.multiworld))
		regions.append(Region("Stage 5", world.player, world.multiworld))
		regions.append(Region("Stage 1 (Hard)", world.player, world.multiworld))
		regions.append(Region("Stage 2 (Hard)", world.player, world.multiworld))
		regions.append(Region("Stage 3 (Hard)", world.player, world.multiworld))
		regions.append(Region("Stage 4 (Hard)", world.player, world.multiworld))
		regions.append(Region("Time Mode", world.player, world.multiworld))

	if world.options.grindy_checks:
		if is_stage_enabled(world):
			regions.append(Region("Grindy Stage", world.player, world.multiworld))
		if is_holo_house_enabled(world):
			regions.append(Region("Grindy HoloHouse", world.player, world.multiworld))

	# We now need to add these regions to multiworld.regions so that AP knows about their existence.
	world.multiworld.regions += regions


def connect_regions(world: HoloCureWorld) -> None:
	from .rules import is_stage_enabled, is_holo_house_enabled
	# We have regions now, but still need to connect them to each other.
	# But wait, we no longer have access to the region variables we created in create_all_regions()!
	# Luckily, once you've submitted your regions to multiworld.regions,
	# you can get them at any time using world.get_region(...).
	menu = world.get_region("Menu")
	shop = world.get_region("Shop")

	# The region.connect helper even allows adding a rule immediately.
	# We'll talk more about rule creation in the set_all_rules() function in rules.py.
	if is_holo_house_enabled(world):
		holo_house = world.get_region("HoloHouse")
		menu.connect(holo_house, "Unlock Holo House", lambda state: state.has("HoloHouse", world.player))
		if world.options.grindy_checks:
			grindy_holo_house = world.get_region("Grindy HoloHouse")
			holo_house.connect(grindy_holo_house, "Grindy HoloHouse")

	menu.connect(shop, "Shop")

	if is_stage_enabled(world):
		if world.options.enable_unique_enemy_checks:
			stage_enemy_check = world.get_region("StageEnemyCheck")
			menu.connect(stage_enemy_check, "StageEnemyCheck")
		stage = world.get_region("Stage")
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
		menu.connect(stage, "Stage")
		menu.connect(stage1, "Stage 1", lambda state: state.has("Progressive Stage", world.player, count = 1))
		menu.connect(stage2, "Stage 2", lambda state: state.has("Progressive Stage", world.player, count = 2))
		menu.connect(stage3, "Stage 3", lambda state: state.has("Progressive Stage", world.player, count = 3))
		menu.connect(stage4, "Stage 4", lambda state: state.has("Progressive Stage", world.player, count = 4))
		menu.connect(stage5, "Stage 5", lambda state: state.has("Progressive Stage", world.player, count = 5))
		menu.connect(stage1_hard, "Stage 1 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 1))
		menu.connect(stage2_hard, "Stage 2 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 2))
		menu.connect(stage3_hard, "Stage 3 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 3))
		menu.connect(stage4_hard, "Stage 4 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 4))
		menu.connect(timemode, "Time Mode", lambda state: state.has("Time Stage 1", world.player))
		if world.options.grindy_checks:
			grindy_stage = world.get_region("Grindy Stage")
			stage.connect(grindy_stage, "Grindy Stage")