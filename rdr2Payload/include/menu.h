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
    // Function pointers for handling the main menu and current menu
    Function mainMenu;
    Function currentMenu;

    // Stack of function pointers for submenu navigation
    Function lastSubmenu[MaxSubmenuLevels];
    int submenuLevel;                 // Tracks the current submenu level

    const char *tipText;              // Tip text displayed in the menu
    int currentOption;                // Index of the current option
    int optionCount;                  // Total number of options in the current menu
    int lastOption[MaxSubmenuLevels]; // Stack to store the last option of each submenu level

    // Input states for various button presses
    bool optionPress;
    bool leftPress;
    bool rightPress;
    bool leftHold;
    bool rightHold;
    bool upPress;
    bool downPress;
    bool squarePress;

    // Instruction management
    int instructionCount;
    bool setupInstructionsThisFrame;
    bool xInstruction;
    bool squareInstruction;
    bool lrInstruction;

    // Keyboard input handling
    bool keyboardActive;
    KeyboardHandler keyboardHandler;

    // Template struct for scroll data
    template <typename T> 
	struct scrollData {
        T *var, min, max;
        int decimals;
    };

    // Static scroll data for int and float types
    static scrollData<int> intScrollData;
    static scrollData<float> floatScrollData;

    // Enumeration for text alignment
    enum Alignment { Left, Center, Right };

    // Static functions for handling keyboard input for scroll data
    static void intScrollKeyboardHandler(const char *text);
    static void floatScrollKeyboardHandler(const char *text);

    // Utility functions for playing sounds and drawing text
    void playSound(const char *sound, const char *ref = "HUD_PLAYER_MENU");
    void drawText(const char *text, Vector2 pos, int size, Font font, const char *color, const char *alignment, bool outline);
    void positionMenuText(const char *text, float xPos, Alignment alignment);
    void colorEditor();

    // Flags for special menu modes
    bool fastScrolling;
    bool colorEditing;
    bool editingAlpha;

    // Pointer to color being edited and a callback for color changes
    Color *colorToEdit;
    Function colorChangeCallback;

	public:
    // Public flags for menu state
    bool open;
    bool sounds;
    bool instructions;

    // EpineGUI title and maximum number of options
    const char *title;
    int maxOptions;

    // Color settings for various menu components
    Color bannerColor;
    Color bannerTextColor;
    Color optionsActiveColor;
    Color optionsInactiveColor;
    Color bodyColor;
    Color scrollerColor;
    Color indicatorColor;
    Color instructionsColor;

    // Constructors
    EpineGUI();
    EpineGUI(EpineGUI &menu);
    EpineGUI(Function main);

    // Static functions for drawing notifications
    static void drawCenterNotification(const char *text, int duration = 3000);
    static void drawFeedNotification(const char *text, const char *subtitle, const char *title = "EpineGUI Base");

    // EpineGUI operation functions
    void monitorButtons();
    void run();
    void changeSubmenu(Function submenu);
    void openKeyboard(KeyboardHandler handler, int maxLength, const char *defaultText = "");
    void banner(const char *text);

    // Input query functions
    bool hovered();
    bool pressed();
    bool scrolled();

    // EpineGUI item functions with chaining support
    EpineGUI &option(const char *text);
    void spacer(const char *text);
    EpineGUI &data(const char *text);
    EpineGUI &data(bool b);
    EpineGUI &data(int i);
    EpineGUI &data(float f, int decimalPlaces);

    // Scroller functions for various data types
    EpineGUI &scroller(int *i, int min, int max, bool fast, bool keyboard);
    EpineGUI &scroller(float *f, float min, float max, float increment, int decimalPlaces, bool fast, bool keyboard);
    EpineGUI &scroller(const char **textArray, int *index, int numItems, bool fast);
    EpineGUI &scroller(Font *font);

    // Toggle and tip functions
    EpineGUI &toggle(bool *b);
    EpineGUI &tip(const char *text);
    EpineGUI &submenu(Function sub);
    EpineGUI &keyboard(KeyboardHandler handler, int maxLength, const char *defaultText = "");
    EpineGUI &editColor(Color *color, bool editAlpha, Function callback = nullptr);

    // Template function for calling a function when pressed
    template<typename F, typename... Args>
    EpineGUI &call(F func, Args&&... args) {
        if (pressed()) func(std::forward<Args>(args)...);
        return *this;
    }

    // Vehicle spawn function
    Hash vehicleToSpawn;
    EpineGUI &vehicleSpawn(Hash vehicleHash);
};

#endif
