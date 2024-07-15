# EthylGUI | A PS4 RDR2 Mod Menu Base
This repository contains a modified version of Ethylamine's PS4 RDR2 Mod Menu Base.

---

A very basic mod menu GUI based on 2much4u's [PS4 GTA V Menu Base](https://github.com/2much4u/PS4-GTA-V-Menu-Base). **Supports only the 1.29 patch of RDR 2 in both US & EU regions.** Requires [Scene Collective/AlAzif's PS4 Payload SDK](https://github.com/Scene-Collective/ps4-payload-sdk) to compile. Compatible with firmwares 5.05, 6.72, 7.55, and 9.00. Currently not compatible with GoldHEN's bin loader. Just as customizable as 2much4u's GTA V Menu Base.

---

## TODO (Upcoming Features)
### Menu
- **Automatic X and Y Coordinate Calculation for Menu Elements:**
  - Store the initial X and Y coordinates used for adding/drawing the first menu item/control.
  - Automatically calculate the next X and Y coordinates for subsequent menu items, eliminating the need to manually provide X and Y values each time.
- **Improve Vector and Color Structures:**
  - Enhance vectors and color structures to work similarly to ImGUI's `ImVec3()`, `ImColor()`, etc.
- **Refactor Menu Drawing Logic:**
  - Reduce redundancy in the logic.
  - Improve efficiency.
  - Enhance maintainability.
---

## Credits

Special thanks to the following developers for their contributions and assistance:
- 2much4u
- 0x199
- AlAzif
- ChendoChap
