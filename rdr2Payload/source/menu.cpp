#include "../include/menu.h"
#include "../include/invoker/natives.h"
#include "../include/lib.h"
#include "../include/fontlist.h"

EpineGUI::EpineGUI() {}
EpineGUI::EpineGUI(EpineGUI &menu) {}
EpineGUI::EpineGUI(Function mainSubmenu) {
	mainMenu = mainSubmenu;
	open = false;
	sounds = true;
	instructions = true;
	maxOptions = 15;
}

void EpineGUI::playSound(const char *sound, const char *ref) {
	if (sounds) {
		AUDIO::_STOP_SOUND_WITH_NAME(sound, ref);
		AUDIO::PLAY_SOUND_FRONTEND(sound, ref, 1, 0);
	}
}

void EpineGUI::monitorButtons() {
	if (open) {
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_UP, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_DOWN, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_RIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_LEFT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_ACCEPT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_CANCEL, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_X, true);
		PAD::SET_INPUT_EXCLUSIVE(0, INPUT_FRONTEND_UP);
		PAD::SET_INPUT_EXCLUSIVE(0, INPUT_FRONTEND_RIGHT);
		PAD::SET_INPUT_EXCLUSIVE(0, INPUT_FRONTEND_LEFT);
		PAD::SET_INPUT_EXCLUSIVE(0, INPUT_FRONTEND_CANCEL);

		optionPress = false;
		leftPress = false;
		rightPress = false;
		leftHold = false;
		rightHold = false;
		upPress = false;
		downPress = false;
		squarePress = false;

		if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_CANCEL)) {
			if (currentMenu == mainMenu) {
				open = false;
				playSound("MENU_CLOSE");
			} else {
				submenuLevel--;
				currentMenu = lastSubmenu[submenuLevel];
				currentOption = lastOption[submenuLevel];
				if (colorEditing) 
					colorEditing = false;
			}
			playSound("BACK");
		} else if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_UP)) {
			upPress = true;
			currentOption--;
			if (currentOption < 1) currentOption = optionCount;

			playSound("NAV_UP");
		} else if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_DOWN)) {
			downPress = true;
			currentOption++;
			if (currentOption > optionCount)
				currentOption = 1;

			playSound("NAV_DOWN");
		} 
		else if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_RIGHT))   rightPress = true;
		else if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_LEFT))    leftPress = true;
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RIGHT))        rightHold = true;
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_LEFT))         leftHold = true;
		else if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_X))       squarePress = true;
	    else if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_ACCEPT)) {
			optionPress = true;
			playSound("SELECT");
		}
	} else {
		if (PAD::IS_CONTROL_PRESSED(0, INPUT_FRONTEND_RB) && PAD::IS_CONTROL_PRESSED(0, INPUT_FRONTEND_RS)) {
			open = true;
			optionPress = false;
			submenuLevel = 0;
			currentMenu = mainMenu;
			currentOption = 1;
			playSound("MENU_ENTER");
		}
	}
}

void EpineGUI::drawText(const char *text, EpineVec2 pos, int size, Font font, const char *color, const char *alignment, bool outline) {
	char buffer[512] = { 0 };
	sprintf(buffer, "<TEXTFORMAT INDENT='0' LEFTMARGIN='0' RIGHTMARGIN='0' LEADING='0'><FONT FACE='$%s' COLOR='#%s' SIZE='%i'><P ALIGN='%s'>%s</P></FONT></TEXTFORMAT>", fontList[font], color, size, alignment, text);

	const char *varString2 = MISC::VAR_STRING(42, "COLOR_STRING", nullptr, MISC::VAR_STRING(10, "LITERAL_STRING", buffer));
	UIDEBUG::_BG_DISPLAY_TEXT(
		varString2,
		pos.x,
		pos.y
	);
}

void EpineGUI::drawCenterNotification(const char *text, int duration) {
	const char *literalString = MISC::VAR_STRING(10, "LITERAL_STRING", text);
	UILOG::_UILOG_SET_CACHED_OBJECTIVE(literalString);
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();
}

void EpineGUI::run() {
	optionCount = 0;
	tipText = nullptr;
	setupIntructionsThisFrame = false;
	xInstruction = false;
	squareInstruction = false;
	lrInstruction = false;

	currentMenu();

	// Constants for drawing
	float MenuOptionHeight = 20.035f;
	float MenuOptionWidth = 0.23f;
	float MenuOptionX = 0.825f;
	float BannerHeight = 0.083f;
	float BannerY = 0.1175f;
	float IndicatorHeight = 0.005f;
	float ScrollerOffset = 0.1415f;
	float UpIndicatorY = 0.159f;
	float DownIndicatorOffset = 0.161f;

	// Calculate heights and widths
	float totalCurrentOptionsH = currentOption * MenuOptionHeight;
	float totalMaximumOptionsH = maxOptions * MenuOptionHeight;
	float totalOptionsH = optionCount * MenuOptionHeight;
	float ScrollerHeight = MenuOptionHeight;
	float IndicatorWidth = MenuOptionWidth;
	float IndicatorHeight = 0.005f;

	// Draw banner + banner title
	GRAPHICS::DRAW_RECT(MenuOptionX, BannerY, MenuOptionWidth, BannerHeight, 201, 0, 44, 255, false, true);
	drawText("Epine Menu", EpineVec2(0.660f, 0.1f), 45, Redemption, "004B93", "CENTER", true);


	// Body and Scroller
	if (optionCount > maxOptions) {
		float bodyHeight = totalMaximumOptionsH;
		float bodyY = (bodyHeight / 2) + 0.159f;
		// Calculate Body height and position, then Draw body
		GRAPHICS::DRAW_RECT(MenuOptionX, bodyY, MenuOptionWidth, bodyHeight, 0, 0, 0, 255, false, true);

		// Calculate/Define Scroller position, then Draw scroller
		float scrollerY = (currentOption > maxOptions) ? totalMaximumOptionsH : totalCurrentOptionsH;
		scrollerY += 0.1415f;
		GRAPHICS::DRAW_RECT(MenuOptionX, scrollerY, MenuOptionWidth, ScrollerHeight, 255, 255, 255, 255, false, true);

		// Draw Up indicator
		if (currentOption > maxOptions)
			GRAPHICS::DRAW_RECT(MenuOptionX, 0.159f, IndicatorWidth, IndicatorHeight, 0, 0, 0, 255, false, true);

		// Draw Down indicator
		if (currentOption != optionCount)
			GRAPHICS::DRAW_RECT(MenuOptionX, (totalMaximumOptionsH + 0.161f), IndicatorWidth, IndicatorHeight, 0, 0, 0, 255, false, true);
	} else {
		// Define Body height and position, then draw body
		float bodyHeight = totalOptionsH;
		float bodyY = (bodyHeight / 2) + 0.159f;
		GRAPHICS::DRAW_RECT(MenuOptionX, bodyY, MenuOptionWidth, bodyHeight, 0, 0, 0, 255, false, true);

		// Define Scroller position, then draw scoller
		float scrollerY = totalCurrentOptionsH + 0.1415f;
		GRAPHICS::DRAW_RECT(MenuOptionX, scrollerY, MenuOptionWidth, ScrollerHeight, 255, 255, 255, 255, false, true);
	}

	// Handle keyboard
	if (keyboardActive) {
		int keyboardStatus = MISC::UPDATE_ONSCREEN_KEYBOARD();
		if (keyboardStatus == 1) {
			keyboardHandler(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
			keyboardActive = false;
		} else if (keyboardStatus == 2 || keyboardStatus == 3)
			keyboardActive = false;
	}
}

void EpineGUI::changeSubmenu(Function submenu) {
	lastSubmenu[submenuLevel] = currentMenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	optionPress = false;
	currentMenu = submenu;
	submenuLevel++;
}

void EpineGUI::openKeyboard(KeyboardHandler handler, int maxLength, const char *defaultText) {
	MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardHandler = handler;
	keyboardActive = true;
}

EpineGUI::scrollData<int> EpineGUI::intScrollData;
EpineGUI::scrollData<float> EpineGUI::floatScrollData;
void EpineGUI::intScrollKeyboardHandler(const char *text) {
	int i = atoi(text);
	if (i <= intScrollData.max && i >= intScrollData.min) {
		*intScrollData.var = i;
	} else {
		char buffer[70] = { 0 };
		sprintf(buffer, "~r~Error: input must be between %i and %i", intScrollData.min, intScrollData.max);
		drawCenterNotification(buffer);
	}
}
void EpineGUI::floatScrollKeyboardHandler(const char *text) {
	float f = (float)atof(text);
	if (f <= floatScrollData.max && f >= floatScrollData.min) {
		*floatScrollData.var = f;
	} else {
		char buffer1[70] = { 0 };
		char buffer2[70] = { 0 };
		sprintf(buffer1, "~r~Error: input must be between %%.%if and %%.%if", floatScrollData.decimals, floatScrollData.decimals);
		sprintf(buffer2, buffer1, floatScrollData.min, floatScrollData.max);
		drawCenterNotification(buffer2);
	}
}

void EpineGUI::banner(const char *text) { title = text; }
bool EpineGUI::hovered() { return currentOption == optionCount; }

bool EpineGUI::pressed() {
	if (hovered()) {
		xInstruction = true;
		if (optionPress)
			return true;
	}
	return false;
}

bool EpineGUI::scrolled() {
	if (hovered()) {
		lrInstruction = true;
		if (rightPress || leftPress || (fastScrolling && rightHold) || (fastScrolling && leftHold))
			return true;
	}
	return false;
}

void EpineGUI::positionMenuText(const char *text, float xPos, Alignment alignment) {
	int optionIndex = 0;
	if (currentOption <= maxOptions && optionCount <= maxOptions) {
		optionIndex = optionCount;
	} else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption) {
		optionIndex = optionCount - (currentOption - maxOptions);
	}
	if (optionIndex != 0) {
		drawText(text, { xPos, optionIndex * 0.035f + 0.125f }, 23, Hapna, hovered() ? "000000" : "FFFFFF", "LEFT", false);
	}
}

EpineGUI &EpineGUI::option(const char *text) {
	optionCount++;
	positionMenuText(text, 0.715f, Left);
	return *this;
}

void EpineGUI::spacer(const char *text) {
	char buffer[60] = { 0 };
	sprintf(buffer, "~italic~%s", text);

	optionCount++;
	positionMenuText(buffer, 0.825f, Center);

	if (hovered()) {
		if (upPress)         currentOption--;
		else if (downPress)  currentOption++;
	}
}

EpineGUI &EpineGUI::data(const char *text) {
	positionMenuText(text, 0.935f, Right);
	return *this;
}

EpineGUI &EpineGUI::data(bool b) {
	return b ? data("On") : data("Off");
}

EpineGUI &EpineGUI::data(int i) {
	char buffer[30] = { 0 };
	sprintf(buffer, "%i", i);
	return data(buffer);
}

EpineGUI &EpineGUI::data(float f, int decimalPlaces) {
	char formatBuffer[10] = { 0 };
	char dataBuffer[30] = { 0 };
	sprintf(formatBuffer, "%%.%if", decimalPlaces);
	sprintf(dataBuffer, formatBuffer, f);
	return data(dataBuffer);
}

EpineGUI &EpineGUI::scroller(int *i, int min, int max, bool fast, bool keyboard) {
	if (!hovered()) return data(*i);

	char buffer[30] = { 0 };
	lrInstruction = true;
	fastScrolling = fast;

	if (rightPress || (rightHold && fast)) {
		playSound("NAV_RIGHT");
		// TODO: Comment this line
		*i = (*i >= max) ? min : (*i + 1);
	} else if (leftPress || (leftHold && fast)) {
		playSound("NAV_LEFT");
		// TODO: Comment this line
		*i = (*i <= min) ? max : (*i - 1);
	}

	if (keyboard) {
		squareInstruction = true;
		if (squarePress) {
			intScrollData = { i, min, max, 0 };
			sprintf(buffer, "%i", max);
			openKeyboard(
				intScrollKeyboardHandler,
				strlen(buffer) + 1
			);
		}
	}

	sprintf(buffer, "&lt; %i &gt;", *i);
	return data(buffer);
}

EpineGUI &EpineGUI::scroller(float *f, float min, float max, float increment, int decimalPlaces, bool fast, bool keyboard) {
	if (!hovered()) return data(*f, decimalPlaces);

	char buffer1[30] = { 0 };
	lrInstruction = true;
	fastScrolling = fast;

	if (rightPress || (rightHold && fast)) {
		// TODO: Comment this line
		*f = (*f >= max) ? min : (*f + increment);
	} else if (leftPress || (leftHold && fast)) {
		playSound("NAV_LEFT");
		// TODO: Comment this line
		*f = (*f <= min) ? max : (*f - increment);
	}

	if (keyboard) {
		squareInstruction = true;
		if (squarePress) {
			floatScrollData = { f, min, max, decimalPlaces };
			sprintf(buffer1, "%i", (int)max);
			openKeyboard(
				floatScrollKeyboardHandler,
				strlen(buffer1) + decimalPlaces + 1
			);
		}
	}

	// TODO: Comment this part
	char buffer2[30] = { 0 };
	sprintf(buffer1, "&lt; %%.%if &gt;", decimalPlaces);
	sprintf(buffer2, buffer1, *f);
	return data(buffer2);

}

EpineGUI &EpineGUI::scroller(const char **textArray, int *index, int numItems, bool fast) {
	char buffer[60] = { 0 };

	numItems--;
	if (hovered()) {
		lrInstruction = true;
		fastScrolling = fast;
		if (rightPress || (rightHold && fast)) {
			playSound("NAV_RIGHT");
			if (*index >= numItems) {
				*index = 0;
			} else {
				*index = *index + 1;
			}
		} else if (leftPress || (leftHold && fast)) {
			playSound("NAV_LEFT");
			if (*index <= 0) {
				*index = numItems;
			} else {
				*index = *index - 1;
			}
		}
	}

	if (hovered()) {
		sprintf(buffer, "&lt; %s &gt;", textArray[*index]);
		return data(buffer);
	}
	return data(textArray[*index]);
}

EpineGUI &EpineGUI::toggle(bool *b) {
	if (pressed())
		*b = !*b;

	return data(*b);
}

EpineGUI &EpineGUI::tip(const char *text) {
	if (hovered())
		tipText = text;

	return *this;
}

EpineGUI &EpineGUI::submenu(Function sub) {
	if (pressed())
		changeSubmenu(sub);

	return *this;
}

EpineGUI &EpineGUI::keyboard(KeyboardHandler handler, int maxLength, const char *defaultText) {
	if (pressed())
		openKeyboard(handler, maxLength, defaultText);

	return *this;
}

EpineGUI &EpineGUI::vehicleSpawn(Hash vehicleHash) {
	if (pressed())
		vehicleToSpawn = vehicleHash;

	return *this;
}
