#pragma once
#ifndef _MENU_HH
#define _MENU_HH

#include <utility>
#include "types.h"
#include "vectors.h"

#define MaxSubmenuLevels 20

typedef void(*Function)();
typedef void(*KeyboardHandler)(const char *);

class EpineGUI {
	private:
	Function mainMenu;
	Function currentMenu;
	Function lastSubmenu[MaxSubmenuLevels];
	int submenuLevel;

	const char *tipText;
	int currentOption;
	int optionCount;
	int lastOption[MaxSubmenuLevels];

	bool optionPress;
	bool leftPress;
	bool rightPress;
	bool leftHold;
	bool rightHold;
	bool upPress;
	bool downPress;
	bool squarePress;

	int instructionCount;
	bool setupIntructionsThisFrame;
	bool xInstruction;
	bool squareInstruction;
	bool lrInstruction;

	bool keyboardActive;
	KeyboardHandler keyboardHandler;

	template <typename T>
	struct scrollData {
		T *var;
		T min;
		T max;
		int decimals;
	};
	static scrollData<int> intScrollData;
	static scrollData<float> floatScrollData;



	enum Alignment { Left, Center, Right };

	static void intScrollKeyboardHandler(const char *text);
	static void floatScrollKeyboardHandler(const char *text);
	void playSound(const char *sound, const char *ref = "HUD_PLAYER_MENU");
	void drawText(const char *text, Vector2 pos, int size, Font font, const char *color, const char *alignment, bool outline);
	void positionMenuText(const char *text, float xPos, Alignment alignment);
	void colorEditor();

	bool fastScrolling;
	bool colorEditing;
	bool editingAlpha;

	Color *colorToEdit;
	Function colorChangeCallback;

	public:
	bool open;
	bool sounds;
	bool instructions;

	const char *title;
	int maxOptions;

	Color bannerColor;
	Color bannerTextColor;
	Color optionsActiveColor;
	Color optionsInactiveColor;
	Color bodyColor;
	Color scrollerColor;
	Color indicatorColor;
	Color instructionsColor;

	EpineGUI();
	EpineGUI(EpineGUI &menu);
	EpineGUI(Function main);

	static void drawCenterNotification(const char *text, int duration = 3000);
	static void drawFeedNotification(const char *text, const char *subtitle, const char *title = "Menu Base");

	void monitorButtons();
	void run();
	void changeSubmenu(Function submenu);
	void openKeyboard(KeyboardHandler handler, int maxLength, const char *defaultText = "");
	void banner(const char *text);

	bool hovered();
	bool pressed();
	bool scrolled();

	EpineGUI &option(const char *text);
	void spacer(const char *text);
	EpineGUI &data(const char *text);
	EpineGUI &data(bool b);
	EpineGUI &data(int i);
	EpineGUI &data(float f, int decimalPlaces);

	EpineGUI &scroller(int *i, int min, int max, bool fast, bool keyboard);
	EpineGUI &scroller(float *f, float min, float max, float increment, int decimalPlaces, bool fast, bool keyboard);
	EpineGUI &scroller(const char **textArray, int *index, int numItems, bool fast);
	EpineGUI &scroller(Font *font);

	EpineGUI &toggle(bool *b);
	EpineGUI &tip(const char *text);
	EpineGUI &submenu(Function sub);
	EpineGUI &keyboard(KeyboardHandler handler, int maxLength, const char *defaultText = "");
	EpineGUI &editColor(Color *color, bool editAlpha, Function callback = nullptr);

	template<typename F, typename... Args>
	EpineGUI &call(F func, Args&&... args) {
		if (pressed()) func(std::forward<Args>(args)...);
		return *this;
	}

	Hash vehicleToSpawn;
	EpineGUI &vehicleSpawn(Hash vehicleHash);
};
#endif
