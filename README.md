# EthylGUI | A PS4 RDR2 Mod Menu Base
This repository contains a modified version of Ethylamine's PS4 RDR2 Mod Menu Base.

## TODO (UPCOMING THINGS)
### Menu
- **Automatically determine X and Y coordinate values for menu elements:**
  - Store the X and Y coordinates used to add/draw the initial menu item/control.
  - Automatically determine the next X and Y coordinates for drawing subsequent menu items, eliminating the need to provide X and Y values each time.
- **Improve Vectors and Color Structs:**
  - Enhance vectors and color structures to work similarly to ImGUI's `ImVec3()`, `ImColor()`, etc.
- **Rewrite the Menu Drawing Function Logic:**
  - Make the logic less redundant.
  - Improve efficiency.
  - Enhance maintainability.


A (very basic) mod menu GUI based on 2much4u's [PS4 GTA V Menu Base](https://github.com/2much4u/PS4-GTA-V-Menu-Base).
**Supports only the 1.29 patch of RDR 2 on both US & EU regions.**
Requires [Scene Collective/AlAzif's PS4 Payload SDK](https://github.com/Scene-Collective/ps4-payload-sdk) to compile.
Compatible with firmwares 5.05, 6.72, 7.55, and 9.00
Currently not compatible with GoldHEN's bin loader.
Just as customizable as 2much4u's GTA V Menu Base.

## Credits
Special Thanks to following devs, for their contribution and assistance:
- 2much4u
- 0x199
- AlAzif
- ChendoChap
