from __future__ import annotations

from typing import TYPE_CHECKING

from BaseClasses import Item, ItemClassification

if TYPE_CHECKING:
	from .world import HoloCureWorld

# Every item must have a unique integer ID associated with it.
# We will have a lookup from item name to ID here that, in world.py, we will import and bind to the world class.
# Even if an item doesn't exist on specific options, it must be present in this lookup.

ITEM_NAME_TO_ID = {
	"HoloHouse": 1,
	"HoloCoin": 2,
	"Progressive Stage": 3,
	"Progressive Stage (Hard)": 4,
	"Time Stage 1": 5,
	"Amelia Watson": 100,
	"Gawr Gura": 101,
	"Ninomae Inanis": 102,
	"Takanashi Kiara": 103,
	"Mori Calliope": 104,
	"Hakos Baelz": 105,
	"Ouro Kronii": 106,
	"Ceres Fauna": 107,
	"Nanashi Mumei": 108,
	"Tsukumo Sana": 109,
	"IRyS": 110,
	"Shirakami Fubuki": 111,
	"Ookami Mio": 112,
	"Nekomata Okayu": 113,
	"Inugami Korone": 114,
	"Tokino Sora": 115,
	"AZki": 116,
	"Roboco-san": 117,
	"Hoshimachi Suisei": 118,
	"Sakura Miko": 119,
	"Akai Haato": 120,
	"Yozora Mel": 121,
	"Natsuiro Matsuri": 122,
	"Aki Rosenthal": 123,
	"Oozora Subaru": 124,
	"Yuzuki Choco": 125,
	"Murasaki Shion": 126,
	"Nakiri Ayame": 127,
	"Minato Aqua": 128,
	"Moona Hoshinova": 129,
	"Ayunda Risu": 130,
	"Airani Iofifteen": 131,
	"Kureiji Ollie": 132,
	"Pavolia Reine": 133,
	"Anya Melfissa": 134,
	"Kobo Kanaeru": 135,
	"Kaela Kovalskia": 136,
	"Vestia Zeta": 137,
	"Usada Pekora": 138,
	"Houshou Marine": 139,
	"Shirogane Noel": 140,
	"Shiranui Flare": 141,
	"Kiryu Coco": 142,
	"Amane Kanata": 143,
	"Tokoyami Towa": 144,
	"Tsunomaki Watame": 145,
	"Himemori Luna": 146,
	"Wamy Water": 1000,
	"Psycho Axe": 1001,
	"X-Potato": 1002,
	"Bounce Ball": 1003,
	"Sausage": 1004,
	"Glowstick": 1005,
	"Spider Cooking": 1006,
	"Plug Type Asacoco": 1007,
	"BL Book": 1008,
	"Elite Lava Bucket": 1009,
	"Holo Bomb": 1010,
	"Cutting Board": 1011,
	"Fan Beam": 1012,
	"Idol Song": 1013,
	"CEO's Tears": 1014,
	"EN's Curse": 1015,
	"Owl Dagger": 1016,
	"Energy Drink": 2000,
	"Plushie": 2001,
	"Limiter": 2002,
	"Beetle": 2003,
	"Kusogaki Shackles": 2004,
	"Ninja Headband": 2005,
	"Chicken's Feather": 2006,
	"Raven Feather": 2007,
	"Body Pillow": 2008,
	"Full Meal": 2009,
	"Piki Piki Piman": 2010,
	"Nurse's Horn": 2011,
	"Headphones": 2012,
	"Uber Sheep": 2013,
	"Knightly Milk": 2014,
	"Sake": 2015,
	"Face Mask": 2016,
	"Credit Card": 2017,
	"Gorilla's Paw": 2018,
	"Super Chatto Time!": 2019,
	"Halu": 2020,
	"Injection Type Asacoco": 2021,
	"Idol Costume": 2022,
	"GWS Pill": 2023,
	"Just Bandage": 2024,
	"Breastplate": 2025,
	"Study Glasses": 2026,
	"Blacksmith's Gear": 2027,
	"Hope Soda": 2028,
	"Stolen Piggy Bank": 2029,
	"Candy Kingdom Sweets": 2030,
	"Researcher's Coat": 2031,
	"Membership": 2032,
	"Devil Hat": 2033,
	"Focus Shades": 2034,
	"Corporation Pin": 2035,
	"Promise Tiara": 2036,
	"Special Attack Shop Upgrade": 3000,
	"Growth Progressive Shop Upgrade": 3001,
	"Reroll Progressive Shop Upgrade": 3002,
	"Eliminate Progressive Shop Upgrade": 3003,
	"Hold Progressive Shop Upgrade": 3004,
	"Customize Shop Upgrade": 3005,
	"Supports Shop Upgrade": 3006,
	"Material Find Shop Upgrade": 3007,
	"Stamps Shop Upgrade": 3008,
	"Enchantments Shop Upgrade": 3009,
	"Fandom Shop Upgrade": 3010,
	"Fan Letters Shop Upgrade": 3011,
	"Max HP Progressive Shop Upgrade": 3012,
	"ATK Progressive Shop Upgrade": 3013,
	"SPD Progressive Shop Upgrade": 3014,
	"Crit Progressive Shop Upgrade": 3015,
	"Pick Up Range Progressive Shop Upgrade": 3016,
	"Haste Up Progressive Shop Upgrade": 3017,
	"Regen Progressive Shop Upgrade": 3018,
	"Defense Progressive Shop Upgrade": 3019,
	"Special Cooldown Reduction Progressive Shop Upgrade": 3020,
	"Skill Up Progressive Shop Upgrade": 3021,
	"EXP Gain Up Progressive Shop Upgrade": 3022,
	"Food Drops Up Progressive Shop Upgrade": 3023,
	"Money Gain Up Progressive Shop Upgrade": 3024,
	"Enhancement Rate Up Progressive Shop Upgrade": 3025,
	"Marketing Up Progressive Shop Upgrade": 3026,
}
# Items should have a defined default classification.
# In our case, we will make a dictionary from item name to classification.
DEFAULT_ITEM_CLASSIFICATIONS = {
	"HoloHouse": ItemClassification.progression,
	"HoloCoin": ItemClassification.filler,
	"Progressive Stage": ItemClassification.progression | ItemClassification.useful,
	"Progressive Stage (Hard)": ItemClassification.progression | ItemClassification.useful,
	"Time Stage 1": ItemClassification.progression,
	"Amelia Watson": ItemClassification.progression,
	"Gawr Gura": ItemClassification.progression,
	"Ninomae Inanis": ItemClassification.progression,
	"Takanashi Kiara": ItemClassification.progression,
	"Mori Calliope": ItemClassification.progression,
	"Hakos Baelz": ItemClassification.progression,
	"Ouro Kronii": ItemClassification.progression,
	"Ceres Fauna": ItemClassification.progression,
	"Nanashi Mumei": ItemClassification.progression,
	"Tsukumo Sana": ItemClassification.progression,
	"IRyS": ItemClassification.progression,
	"Shirakami Fubuki": ItemClassification.progression,
	"Ookami Mio": ItemClassification.progression,
	"Nekomata Okayu": ItemClassification.progression,
	"Inugami Korone": ItemClassification.progression,
	"Tokino Sora": ItemClassification.progression,
	"AZki": ItemClassification.progression,
	"Roboco-san": ItemClassification.progression,
	"Hoshimachi Suisei": ItemClassification.progression,
	"Sakura Miko": ItemClassification.progression,
	"Akai Haato": ItemClassification.progression,
	"Yozora Mel": ItemClassification.progression,
	"Natsuiro Matsuri": ItemClassification.progression,
	"Aki Rosenthal": ItemClassification.progression,
	"Yuzuki Choco": ItemClassification.progression,
	"Oozora Subaru": ItemClassification.progression,
	"Murasaki Shion": ItemClassification.progression,
	"Nakiri Ayame": ItemClassification.progression,
	"Minato Aqua": ItemClassification.progression,
	"Moona Hoshinova": ItemClassification.progression,
	"Airani Iofifteen": ItemClassification.progression,
	"Ayunda Risu": ItemClassification.progression,
	"Kureiji Ollie": ItemClassification.progression,
	"Pavolia Reine": ItemClassification.progression,
	"Anya Melfissa": ItemClassification.progression,
	"Kobo Kanaeru": ItemClassification.progression,
	"Kaela Kovalskia": ItemClassification.progression,
	"Vestia Zeta": ItemClassification.progression,
	"Usada Pekora": ItemClassification.progression,
	"Shirogane Noel": ItemClassification.progression,
	"Shiranui Flare": ItemClassification.progression,
	"Houshou Marine": ItemClassification.progression,
	"Kiryu Coco": ItemClassification.progression,
	"Amane Kanata": ItemClassification.progression,
	"Tsunomaki Watame": ItemClassification.progression,
	"Tokoyami Towa": ItemClassification.progression,
	"Himemori Luna": ItemClassification.progression,
	"Wamy Water": ItemClassification.progression,
	"Psycho Axe": ItemClassification.progression,
	"X-Potato": ItemClassification.progression,
	"Bounce Ball": ItemClassification.progression,
	"Sausage": ItemClassification.progression,
	"Glowstick": ItemClassification.progression,
	"Spider Cooking": ItemClassification.progression,
	"Plug Type Asacoco": ItemClassification.progression,
	"BL Book": ItemClassification.progression,
	"Elite Lava Bucket": ItemClassification.progression,
	"Holo Bomb": ItemClassification.progression,
	"Cutting Board": ItemClassification.progression,
	"Fan Beam": ItemClassification.progression,
	"Idol Song": ItemClassification.progression,
	"CEO's Tears": ItemClassification.progression,
	"EN's Curse": ItemClassification.progression,
	"Owl Dagger": ItemClassification.progression,
	"Energy Drink": ItemClassification.progression,
	"Plushie": ItemClassification.progression,
	"Limiter": ItemClassification.progression,
	"Beetle": ItemClassification.progression,
	"Kusogaki Shackles": ItemClassification.progression,
	"Ninja Headband": ItemClassification.progression,
	"Chicken's Feather": ItemClassification.progression,
	"Raven Feather": ItemClassification.progression,
	"Body Pillow": ItemClassification.progression,
	"Full Meal": ItemClassification.progression,
	"Piki Piki Piman": ItemClassification.progression,
	"Nurse's Horn": ItemClassification.progression,
	"Headphones": ItemClassification.progression,
	"Uber Sheep": ItemClassification.progression,
	"Knightly Milk": ItemClassification.progression,
	"Sake": ItemClassification.progression,
	"Face Mask": ItemClassification.progression,
	"Credit Card": ItemClassification.progression,
	"Gorilla's Paw": ItemClassification.progression,
	"Super Chatto Time!": ItemClassification.progression,
	"Halu": ItemClassification.progression,
	"Injection Type Asacoco": ItemClassification.progression,
	"Idol Costume": ItemClassification.progression,
	"GWS Pill": ItemClassification.progression,
	"Just Bandage": ItemClassification.progression,
	"Breastplate": ItemClassification.progression,
	"Study Glasses": ItemClassification.progression,
	"Blacksmith's Gear": ItemClassification.progression,
	"Hope Soda": ItemClassification.progression,
	"Stolen Piggy Bank": ItemClassification.progression,
	"Candy Kingdom Sweets": ItemClassification.progression,
	"Researcher's Coat": ItemClassification.progression,
	"Membership": ItemClassification.progression,
	"Devil Hat": ItemClassification.progression,
	"Focus Shades": ItemClassification.progression,
	"Corporation Pin": ItemClassification.progression,
	"Promise Tiara": ItemClassification.progression,
	"Special Attack Shop Upgrade": ItemClassification.progression,
	"Growth Progressive Shop Upgrade": ItemClassification.useful,
	"Reroll Progressive Shop Upgrade": ItemClassification.useful,
	"Eliminate Progressive Shop Upgrade": ItemClassification.useful,
	"Hold Progressive Shop Upgrade": ItemClassification.useful,
	"Customize Shop Upgrade": ItemClassification.useful,
	"Supports Shop Upgrade": ItemClassification.useful,
	"Material Find Shop Upgrade": ItemClassification.useful,
	"Stamps Shop Upgrade": ItemClassification.progression,
	"Enchantments Shop Upgrade": ItemClassification.useful,
	"Fandom Shop Upgrade": ItemClassification.useful,
	"Fan Letters Shop Upgrade": ItemClassification.progression,
	"Max HP Progressive Shop Upgrade": ItemClassification.progression,
	"ATK Progressive Shop Upgrade": ItemClassification.progression,
	"SPD Progressive Shop Upgrade": ItemClassification.progression,
	"Crit Progressive Shop Upgrade": ItemClassification.progression,
	"Pick Up Range Progressive Shop Upgrade": ItemClassification.progression,
	"Haste Up Progressive Shop Upgrade": ItemClassification.progression,
	"Regen Progressive Shop Upgrade": ItemClassification.useful,
	"Defense Progressive Shop Upgrade": ItemClassification.useful,
	"Special Cooldown Reduction Progressive Shop Upgrade": ItemClassification.useful,
	"Skill Up Progressive Shop Upgrade": ItemClassification.useful,
	"EXP Gain Up Progressive Shop Upgrade": ItemClassification.progression,
	"Food Drops Up Progressive Shop Upgrade": ItemClassification.useful,
	"Money Gain Up Progressive Shop Upgrade": ItemClassification.progression,
	"Enhancement Rate Up Progressive Shop Upgrade": ItemClassification.progression,
	"Marketing Up Progressive Shop Upgrade": ItemClassification.progression,
}


# Each Item instance must correctly report the "game" it belongs to.
# To make this simple, it is common practice to subclass the basic Item class and override the "game" field.
class HoloCureItem(Item):
	game = "HoloCure"


# Ontop of our regular itempool, our world must be able to create arbitrary amounts of filler as requested by core.
# To do this, it must define a function called world.get_filler_item_name(), which we will define in world.py later.
# For now, let's make a function that returns the name of a random filler item here in items.py.
def get_random_filler_item_name(world: HoloCureWorld) -> str:
	# APQuest has an option called "trap_chance".
	# This is the percentage chance that each filler item is a Math Trap instead of a Confetti Cannon.
	# For this purpose, we need to use a random generator.

	# IMPORTANT: Whenever you need to use a random generator, you must use world.random.
	# This ensures that generating with the same generator seed twice yields the same output.
	# DO NOT use a bare random object from Python's built-in random module.
#    if world.random.randint(0, 99) < world.options.trap_chance:
#        return "Math Trap"
	return "HoloCoin"


def create_item_with_correct_classification(world: HoloCureWorld, name: str) -> HoloCureItem:
	# Our world class must have a create_item() function that can create any of our items by name at any time.
	# So, we make this helper function that creates the item by name with the correct classification.
	# Note: This function's content could just be the contents of world.create_item in world.py directly,
	# but it seemed nicer to have it in its own function over here in items.py.
	classification = DEFAULT_ITEM_CLASSIFICATIONS[name]

	# It is perfectly normal and valid for an item's classification to differ based on the player's options.
	# In our case, Health Upgrades are only relevant to logic (and thus labeled as "progression") in hard mode.
#    if name == "Health Upgrade" and world.options.hard_mode:
#        classification = ItemClassification.progression

	return HoloCureItem(name, classification, ITEM_NAME_TO_ID[name], world.player)


# With those two helper functions defined, let's now get to actually creating and submitting our itempool.
def create_all_items(world: HoloCureWorld) -> None:
	# This is the function in which we will create all the items that this world submits to the multiworld item pool.
	# There must be exactly as many items as there are locations.
	# In our case, there are either six or seven locations.
	# We must make sure that when there are six locations, there are six items,
	# and when there are seven locations, there are seven items.

	# Creating items should generally be done via the world's create_item method.
	# First, we create a list containing all the items that always exist.

	itempool: list[Item] = [
		world.create_item("HoloHouse"),
	]

	stages: list[Item] = [
		world.create_item("Progressive Stage"),
		world.create_item("Progressive Stage"),
		world.create_item("Progressive Stage"),
		world.create_item("Progressive Stage"),
		world.create_item("Progressive Stage"),
		world.create_item("Progressive Stage"),
		world.create_item("Progressive Stage (Hard)"),
		world.create_item("Progressive Stage (Hard)"),
		world.create_item("Progressive Stage (Hard)"),
		world.create_item("Progressive Stage (Hard)"),
		world.create_item("Progressive Stage (Hard)"),
		world.create_item("Progressive Stage (Hard)"),
		world.create_item("Time Stage 1"),
	]

	characters: list[Item] = [
		world.create_item("Amelia Watson"),
		world.create_item("Gawr Gura"),
		world.create_item("Ninomae Inanis"),
		world.create_item("Takanashi Kiara"),
		world.create_item("Mori Calliope"),
		world.create_item("Hakos Baelz"),
		world.create_item("Ouro Kronii"),
		world.create_item("Ceres Fauna"),
		world.create_item("Nanashi Mumei"),
		world.create_item("Tsukumo Sana"),
		world.create_item("IRyS"),
		world.create_item("Shirakami Fubuki"),
		world.create_item("Ookami Mio"),
		world.create_item("Nekomata Okayu"),
		world.create_item("Inugami Korone"),
		world.create_item("Tokino Sora"),
		world.create_item("AZki"),
		world.create_item("Roboco-san"),
		world.create_item("Hoshimachi Suisei"),
		world.create_item("Sakura Miko"),
		world.create_item("Akai Haato"),
		world.create_item("Yozora Mel"),
		world.create_item("Natsuiro Matsuri"),
		world.create_item("Aki Rosenthal"),
		world.create_item("Yuzuki Choco"),
		world.create_item("Oozora Subaru"),
		world.create_item("Murasaki Shion"),
		world.create_item("Nakiri Ayame"),
		world.create_item("Minato Aqua"),
		world.create_item("Moona Hoshinova"),
		world.create_item("Airani Iofifteen"),
		world.create_item("Ayunda Risu"),
		world.create_item("Kureiji Ollie"),
		world.create_item("Pavolia Reine"),
		world.create_item("Anya Melfissa"),
		world.create_item("Kobo Kanaeru"),
		world.create_item("Kaela Kovalskia"),
		world.create_item("Vestia Zeta"),
		world.create_item("Usada Pekora"),
		world.create_item("Shirogane Noel"),
		world.create_item("Shiranui Flare"),
		world.create_item("Houshou Marine"),
		world.create_item("Kiryu Coco"),
		world.create_item("Amane Kanata"),
		world.create_item("Tsunomaki Watame"),
		world.create_item("Tokoyami Towa"),
		world.create_item("Himemori Luna"),
	]

	weapons: list[Item] = [
		world.create_item("Wamy Water"),
		world.create_item("Psycho Axe"),
		world.create_item("X-Potato"),
		world.create_item("Bounce Ball"),
		world.create_item("Sausage"),
		world.create_item("Glowstick"),
		world.create_item("Spider Cooking"),
		world.create_item("Plug Type Asacoco"),
		world.create_item("BL Book"),
		world.create_item("Elite Lava Bucket"),
		world.create_item("Holo Bomb"),
		world.create_item("Cutting Board"),
		world.create_item("Fan Beam"),
		world.create_item("Idol Song"),
		world.create_item("CEO's Tears"),
		world.create_item("EN's Curse"),
		world.create_item("Owl Dagger"),
	]

	items: list[Item] = [
		world.create_item("Energy Drink"),
		world.create_item("Plushie"),
		world.create_item("Limiter"),
		world.create_item("Beetle"),
		world.create_item("Kusogaki Shackles"),
		world.create_item("Ninja Headband"),
		world.create_item("Chicken's Feather"),
		world.create_item("Raven Feather"),
		world.create_item("Body Pillow"),
		world.create_item("Full Meal"),
		world.create_item("Piki Piki Piman"),
		world.create_item("Nurse's Horn"),
		world.create_item("Headphones"),
		world.create_item("Uber Sheep"),
		world.create_item("Knightly Milk"),
		world.create_item("Sake"),
		world.create_item("Face Mask"),
		world.create_item("Credit Card"),
		world.create_item("Gorilla's Paw"),
		world.create_item("Super Chatto Time!"),
		world.create_item("Halu"),
		world.create_item("Injection Type Asacoco"),
		world.create_item("Idol Costume"),
		world.create_item("GWS Pill"),
		world.create_item("Just Bandage"),
		world.create_item("Breastplate"),
		world.create_item("Study Glasses"),
		world.create_item("Blacksmith's Gear"),
		world.create_item("Hope Soda"),
		world.create_item("Stolen Piggy Bank"),
		world.create_item("Candy Kingdom Sweets"),
		world.create_item("Researcher's Coat"),
		world.create_item("Membership"),
		world.create_item("Devil Hat"),
		world.create_item("Focus Shades"),
		world.create_item("Corporation Pin"),
		world.create_item("Promise Tiara"),
	]

	shop: list[Item] = [
		world.create_item("Special Attack Shop Upgrade"),
		world.create_item("Growth Progressive Shop Upgrade"),
		world.create_item("Growth Progressive Shop Upgrade"),
		world.create_item("Growth Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Reroll Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Eliminate Progressive Shop Upgrade"),
		world.create_item("Hold Progressive Shop Upgrade"),
		world.create_item("Hold Progressive Shop Upgrade"),
		world.create_item("Hold Progressive Shop Upgrade"),
		world.create_item("Hold Progressive Shop Upgrade"),
		world.create_item("Hold Progressive Shop Upgrade"),
		world.create_item("Customize Shop Upgrade"),
		world.create_item("Supports Shop Upgrade"),
		world.create_item("Material Find Shop Upgrade"),
		world.create_item("Stamps Shop Upgrade"),
		world.create_item("Enchantments Shop Upgrade"),
		world.create_item("Fandom Shop Upgrade"),
		world.create_item("Fan Letters Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("Max HP Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("ATK Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("SPD Progressive Shop Upgrade"),
		world.create_item("Crit Progressive Shop Upgrade"),
		world.create_item("Crit Progressive Shop Upgrade"),
		world.create_item("Crit Progressive Shop Upgrade"),
		world.create_item("Crit Progressive Shop Upgrade"),
		world.create_item("Crit Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Pick Up Range Progressive Shop Upgrade"),
		world.create_item("Haste Up Progressive Shop Upgrade"),
		world.create_item("Haste Up Progressive Shop Upgrade"),
		world.create_item("Haste Up Progressive Shop Upgrade"),
		world.create_item("Haste Up Progressive Shop Upgrade"),
		world.create_item("Haste Up Progressive Shop Upgrade"),
		world.create_item("Regen Progressive Shop Upgrade"),
		world.create_item("Regen Progressive Shop Upgrade"),
		world.create_item("Regen Progressive Shop Upgrade"),
		world.create_item("Regen Progressive Shop Upgrade"),
		world.create_item("Regen Progressive Shop Upgrade"),
		world.create_item("Defense Progressive Shop Upgrade"),
		world.create_item("Defense Progressive Shop Upgrade"),
		world.create_item("Defense Progressive Shop Upgrade"),
		world.create_item("Defense Progressive Shop Upgrade"),
		world.create_item("Defense Progressive Shop Upgrade"),
		world.create_item("Special Cooldown Reduction Progressive Shop Upgrade"),
		world.create_item("Special Cooldown Reduction Progressive Shop Upgrade"),
		world.create_item("Special Cooldown Reduction Progressive Shop Upgrade"),
		world.create_item("Special Cooldown Reduction Progressive Shop Upgrade"),
		world.create_item("Special Cooldown Reduction Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("Skill Up Progressive Shop Upgrade"),
		world.create_item("EXP Gain Up Progressive Shop Upgrade"),
		world.create_item("EXP Gain Up Progressive Shop Upgrade"),
		world.create_item("EXP Gain Up Progressive Shop Upgrade"),
		world.create_item("EXP Gain Up Progressive Shop Upgrade"),
		world.create_item("EXP Gain Up Progressive Shop Upgrade"),
		world.create_item("Food Drops Up Progressive Shop Upgrade"),
		world.create_item("Food Drops Up Progressive Shop Upgrade"),
		world.create_item("Food Drops Up Progressive Shop Upgrade"),
		world.create_item("Food Drops Up Progressive Shop Upgrade"),
		world.create_item("Food Drops Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Money Gain Up Progressive Shop Upgrade"),
		world.create_item("Enhancement Rate Up Progressive Shop Upgrade"),
		world.create_item("Enhancement Rate Up Progressive Shop Upgrade"),
		world.create_item("Enhancement Rate Up Progressive Shop Upgrade"),
		world.create_item("Enhancement Rate Up Progressive Shop Upgrade"),
		world.create_item("Enhancement Rate Up Progressive Shop Upgrade"),
		world.create_item("Marketing Up Progressive Shop Upgrade"),
		world.create_item("Marketing Up Progressive Shop Upgrade"),
		world.create_item("Marketing Up Progressive Shop Upgrade"),
		world.create_item("Marketing Up Progressive Shop Upgrade"),
		world.create_item("Marketing Up Progressive Shop Upgrade"),
	]

	start_char_list = world.random.sample(characters, 5)
	start_weapon_list = world.random.sample(weapons, 7)
	start_items_list = world.random.sample(items, 9)
	[world.push_precollected(curItem) for curItem in start_char_list]
	[world.push_precollected(curItem) for curItem in start_weapon_list]
	[world.push_precollected(curItem) for curItem in start_items_list]

	itempool += stages
	itempool += [char for char in characters if char not in start_char_list]
	itempool += [weapon for weapon in weapons if weapon not in start_weapon_list]
	itempool += [item for item in items if item not in start_items_list]
	itempool += shop

	# Archipelago requires that each world submits as many locations as it submits items.
	# This is where we can use our filler and trap items.
	# APQuest has two of these: The Confetti Cannon and the Math Trap.
	# (Unfortunately, Archipelago is a bit ambiguous about its terminology here:
	#  "filler" is an ItemClassification separate from "trap", but in a lot of its functions,
	#  Archipelago will use "filler" to just mean "an additional item created to fill out the itempool".
	#  "Filler" in this sense can technically have any ItemClassification,
	#  but most commonly ItemClassification.filler or ItemClassification.trap.
	#  Starting here, the word "filler" will be used to collectively refer to APQuest's Confetti Cannon and Math Trap,
	#  which are ItemClassification.filler and ItemClassification.trap respectively.)
	# Creating filler items works the same as any other item. But there is a question:
	# How many filler items do we actually need to create?
	# In regions.py, we created either six or seven locations depending on the "extra_starting_chest" option.
	# In this function, we have created five or six items depending on whether the "hammer" option is enabled.
	# We *could* have a really complicated if-else tree checking the options again, but there is a better way.
	# We can compare the size of our itempool so far to the number of locations in our world.

	# The length of our itempool is easy to determine, since we have it as a list.
	number_of_items = len(itempool)

	# The number of locations is also easy to determine, but we have to be careful.
	# Just calling len(world.get_locations()) would report an incorrect number, because of our *event locations*.
	# What we actually want is the number of *unfilled* locations. Luckily, there is a helper method for this:
	number_of_unfilled_locations = len(world.multiworld.get_unfilled_locations(world.player))

	# Now, we just subtract the number of items from the number of locations to get the number of empty item slots.
	needed_number_of_filler_items = number_of_unfilled_locations - number_of_items

	# Finally, we create that many filler items and add them to the itempool.
	# To create our filler, we could just use world.create_item("Confetti Cannon").
	# But there is an alternative that works even better for most worlds, including APQuest.
	# As discussed above, our world must have a get_filler_item_name() function defined,
	# which must return the name of an infinitely repeatable filler item.
	# Defining this function enables the use of a helper function called world.create_filler().
	# You can just use this function directly to create as many filler items as you need to complete your itempool.
	itempool += [world.create_filler() for _ in range(needed_number_of_filler_items)]

	# But... is that the right option for your game? Let's explore that.
	# For some games, the concepts of "regular itempool filler" and "additionally created filler" are different.
	# These games might want / require specific amounts of specific filler items in their regular pool.
	# To achieve this, they will have to intentionally create the correct quantities using world.create_item().
	# They may still use world.create_filler() to fill up the rest of their itempool with "repeatable filler",
	# after creating their "specific quantity" filler and still having room left over.

	# But there are many other games which *only* have infinitely repeatable filler items.
	# They don't care about specific amounts of specific filler items, instead only caring about the proportions.
	# In this case, world.create_filler() can just be used for the entire filler itempool.
	# APQuest is one of these games:
	# Regardless of whether it's filler for the regular itempool or additional filler for item links / etc.,
	# we always just want a Confetti Cannon or a Math Trap depending on the "trap_chance" option.
	# We defined this behavior in our get_random_filler_item_name() function, which in world.py,
	# we'll bind to world.get_filler_item_name(). So, we can just use world.create_filler() for all of our filler.

	# Anyway. With our world's itempool finalized, we now need to submit it to the multiworld itempool.
	# This is how the generator actually knows about the existence of our items.
	world.multiworld.itempool += itempool

	# Sometimes, you might want the player to start with certain items already in their inventory.
	# These items are called "precollected items".
	# They will be sent as soon as they connect for the first time (depending on your client's item handling flag).
	# Players can add precollected items themselves via the generic "start_inventory" option.
	# If you want to add your own precollected items, you can do so via world.push_precollected().