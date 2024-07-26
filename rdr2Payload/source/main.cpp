#include "../include/lib.h"
#include "../include/invoker/natives.h"
#include "../include/menu.h"

bool init = false;
int frameCount = 0;
EpineGUI menu;

void mainMenu() {
	menu.banner("Main Menu");
	menu.option("Self Options");
	menu.option("Vehicle Spawner");
	menu.option("Settings");
}

extern "C" void _main(void) {
	if (!init) {
		initLibs();
		menu = EpineGUI(mainMenu);
		init = true;
	}

	int newFrameCount = MISC::GET_FRAME_COUNT();
	if (newFrameCount > frameCount) {
		frameCount = newFrameCount;

		menu.monitorButtons();

		if (menu.open) {
			menu.run();
		}
	}
}