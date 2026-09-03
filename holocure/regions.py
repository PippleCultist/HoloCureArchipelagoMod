from __future__ import annotations

from typing import TYPE_CHECKING

from BaseClasses import Entrance, Region

if TYPE_CHECKING:
	from .world import HoloCureWorld

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
	# Creating a region is as simple as calling the constructor of the Region class.
	menu = Region("Menu", world.player, world.multiworld)
	holo_house = Region("HoloHouse", world.player, world.multiworld)
	grindy = Region("Grindy", world.player, world.multiworld)
	shop = Region("Shop", world.player, world.multiworld)
	stage1 = Region("Stage 1", world.player, world.multiworld)
	stage2 = Region("Stage 2", world.player, world.multiworld)
	stage3 = Region("Stage 3", world.player, world.multiworld)
	stage4 = Region("Stage 4", world.player, world.multiworld)
	stage5 = Region("Stage 5", world.player, world.multiworld)
	stage1_hard = Region("Stage 1 (Hard)", world.player, world.multiworld)
	stage2_hard = Region("Stage 2 (Hard)", world.player, world.multiworld)
	stage3_hard = Region("Stage 3 (Hard)", world.player, world.multiworld)
	stage4_hard = Region("Stage 4 (Hard)", world.player, world.multiworld)
	timemode = Region("Time Mode", world.player, world.multiworld)

	# Let's put all these regions in a list.
	regions = [menu, holo_house, grindy, shop, stage1, stage2, stage3, stage4, stage5, stage1_hard, stage2_hard, stage3_hard, stage4_hard, timemode]

	# We now need to add these regions to multiworld.regions so that AP knows about their existence.
	world.multiworld.regions += regions


def connect_regions(world: HoloCureWorld) -> None:
	# We have regions now, but still need to connect them to each other.
	# But wait, we no longer have access to the region variables we created in create_all_regions()!
	# Luckily, once you've submitted your regions to multiworld.regions,
	# you can get them at any time using world.get_region(...).
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

	# The region.connect helper even allows adding a rule immediately.
	# We'll talk more about rule creation in the set_all_rules() function in rules.py.
	menu.connect(holo_house, "Unlock Holo House", lambda state: state.has("HoloHouse", world.player))

	menu.connect(shop, "Shop")
	menu.connect(stage1, "Stage 1")
	menu.connect(stage2, "Stage 2", lambda state: state.has("Progressive Stage", world.player, count = 1))
	menu.connect(stage3, "Stage 3", lambda state: state.has("Progressive Stage", world.player, count = 2))
	menu.connect(stage4, "Stage 4", lambda state: state.has("Progressive Stage", world.player, count = 3))
	menu.connect(stage5, "Stage 5", lambda state: state.has("Progressive Stage", world.player, count = 4))
	menu.connect(stage1_hard, "Stage 1 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 1))
	menu.connect(stage2_hard, "Stage 2 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 2))
	menu.connect(stage3_hard, "Stage 3 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 3))
	menu.connect(stage4_hard, "Stage 4 (Hard)", lambda state: state.has("Progressive Stage (Hard)", world.player, count = 4))
	menu.connect(timemode, "Time Mode", lambda state: state.has("Time Stage 1", world.player))

	if world.options.grindy_checks:
		menu.connect(grindy, "Grindy")
