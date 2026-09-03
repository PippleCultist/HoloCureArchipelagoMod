# HoloCure Archipelago Mod
[![Github All Releases](https://img.shields.io/github/downloads/PippleCultist/HoloCureArchipelagoMod/HoloCureArchipelagoMod.dll)](https://github.com/PippleCultist/HoloCureArchipelagoMod/releases)

A HoloCure mod that integrates Archipelago with the game. Archipelago is a randomizer that lets you play by yourself via localhost or randomized with other people's different games through archipelago.gg.

Currently in Alpha, so there may be potential bugs/crashes that occur.

## AI Disclosure
I have not used AI to write any code or contribute to this project. I cannot confirm if the dependencies that this project uses have any AI usage or not. If you wish to contribute to this project, please refrain from using AI.

## Installation Steps
# Follow these instructions if you've used mods before December 2025
- Run `AurieManager.exe` and uninstall Aurie from `HoloCure.exe`
    - The latest version of Aurie is moving away from AurieManager and is instead patching the game to run the mods. This has the benefit of not requiring admin privileges anymore and easily disabling mods by deleting the mods folder or replacing the original exe without crashing.
# Normal installation steps
- Download `HoloCureArchipelagoMod.dll`, `APCpp.dll`, and `CallbackManagerMod.dll` from the latest version of the mod https://github.com/PippleCultist/HoloCureArchipelagoMod/releases
- Download `AurieInstaller.exe` from the latest version of Aurie https://github.com/AurieFramework/Aurie/releases
- Launch `AurieInstaller.exe`, click `Find my game!`, and select `HoloCure.exe`
    - You can find `HoloCure.exe` through Steam by clicking `Browse local files`
- Click `Confirm Version`
- Go to the folder where `HoloCure.exe` is located and copy over `APCpp.dll` into it
- Go to the `mods` folder where `HoloCure.exe` is located and locate the `Aurie` folder.
    - In the `Aurie` folder, copy over `HoloCureArchipelagoMod.dll` and `CallbackManagerMod.dll`
- Running the game either using the executable or through Steam should now launch the mods as well
## Common Issues
- If you deleted the mods folder and are seeing `Missing game executable`, you most likely didn't click `Uninstall Aurie` in AurieManager before deleting the folder. To fix this issue, uninstall Aurie through AurieManager.
## Before Playing
Make sure to make a backup of `AppData\Local\HoloCure\save_n.dat`, `AppData\Local\HoloCure\save.dat`, `AppData\Local\HoloCure\backup_save_n.dat`, and `AppData\Local\HoloCure\backup_save.dat` if they exist. Whenever playing a new archipelago game, make sure to delete `AppData\Local\HoloCure\ArchipelagoSave.dat` to have a clean start.

## How to play

First, you need a room to connect to. For this, you or someone you know has to generate a game.  
This will not be explained here,
but you can check the [Archipelago Setup Guide](/tutorial/Archipelago/setup_en#generating-a-game).

You also need to have [Archipelago](https://github.com/ArchipelagoMW/Archipelago/releases/latest) installed
and the [The HoloCure apworld](https://github.com/PippleCultist/HoloCureArchipelagoMod/releases) installed into Archipelago.

From here, connecting to your HoloCure slot is easy. There are two scenarios.

### Webhost Room

If your room is hosted on a WebHost (e.g. [archipelago.gg](https://archipelago.gg)),
you should get the link and port (e.g. archipelago.gg:38281).
Then you launch HoloCure, and a separate window named HoloCure Archipelago Mod will open. 
There will be a window in the GUI named Connect, and you should put the address in the field named IP. For Player Name, you put the assigned player name that was set in the YAML file. Password is only required if the apworld is set to require one.

### Locally hosted room

If your room does not have a WebHost room page available, you can launch HoloCure manually.  

Usually the address will be in the format of localhost:port number. Copy this into the IP field. The rest of the steps are the same as the Webhost Room.
