/*
 * ChessSettingsWin.h
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: ido abulafya
 */

#ifndef GRAPHICS_CHESSSETTINGSWIN_H_
#define GRAPHICS_CHESSSETTINGSWIN_H_

#include "SimpleWindow.h"

#define SETTINGS_NUM_OF_DIFFICULTY_BUTTONS 5
#define SETTINGS_NUM_OF_USERCOLOR_BUTTONS 3
#define SETTINGS_NUM_OF_GAMEMODE_BUTTONS 3
#define SETTINGS_NUM_OF_NORMAL_BUTTONS 4
#define NOT_CHOOSED_SETTINGS -1
#define START_INDEX 0
#define NEXT_INDEX 1
#define BACK_INDEX 2

typedef enum{
	SETTINGS_SUCCESS,
	SETTINGS_FAILED
}SETTINGS_MESSAGE;

typedef enum{
	GAME_MODE_STATE,
	DIFFICULTY_STATE,
	USER_COLOR_STATE
}SETTING_STATE;

typedef enum {
	SETTINGS_START_EVENT,
	SETTINGS_NEXT_EVENT,
	SETTINGS_BACK_EVENT,
	SETTINGS_NORMAL_EVENT,
	SETTINGS_INVALID_ARGUMENT_EVENT,
	SETTINGS_EXIT_EVENT,
	SETTINGS_NONE_EVENT
} SETTINGS_EVENT;
/**
 * Struct: SettingsWin
 * Description:
 * symbols the Settings window.
 * contains a simple Window object, four arrays of buttons,
 * the selected values integers, the current state of the program,
 * and the texture of the BG.
 */
typedef struct{
	SimpleWindow* simpleWindow;
	Button** difficultyButtons;
	Button** gameModeButtons;
	Button** userColorButtons;
	Button** normalButtons; //start,next,back
	int difficultySelect;
	int gameModeSelect;
	int userColorSelect;
	SETTING_STATE state;
	SDL_Texture* gridTexture;
}SettingsWin;
/**
 * Name: settingsWindowCreate
 * Description:
 * Creates a SettingsWin object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * creates the instance of the matching simpleWindow.
 * returns a pointer to the new SettingsWin object that was created.
 */
SettingsWin* settingsWindowCreate(WINDOW_TYPE backType);
/**
 * Name: initializeSettingsWindow
 * Description:
 * initializes all settingsWin buttons to not active and not clickable.
 */
SETTINGS_MESSAGE initializeSettingsWindow(SettingsWin* settingsWin);
/**
 * Name: updateNormalButtons
 * Description:
 * That function is responsible to turn on and turn off the different
 * buttons that exist due to the current state and due to the user selections.
 */
void updateNormalButtons(SettingsWin* settingsWin);
/**
 * Name: generateDifficutyButtons
 * Description:
 * Creates a difficutyButtons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate SETTINGS_MESSAGE message.
 */
SETTINGS_MESSAGE generateDifficutyButtons(SettingsWin* settingsWin);
/**
 * Name: generateGameModeButtons
 * Description:
 * Creates a gameModeButtons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate SETTINGS_MESSAGE message.
 */
SETTINGS_MESSAGE generateGameModeButtons(SettingsWin* settingsWin);
/**
 * Name: generateUserColorButtons
 * Description:
 * Creates a userColorButtons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate SETTINGS_MESSAGE message.
 */
SETTINGS_MESSAGE generateUserColorButtons(SettingsWin* settingsWin);
/**
 * Name: generateNormalButtons
 * Description:
 * Creates a normalButtons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate SETTINGS_MESSAGE message.
 */
SETTINGS_MESSAGE generateNormalButtons(SettingsWin* settingsWin);
/**
 * Name: settingsWindowDraw
 * Description:
 * Draws all the background and all of the buttons that suppose
 * be presented in load window.
 * returns an appropriate SETTINGS_MESSAGE message if it succeeded or not.
 */
SETTINGS_MESSAGE settingsWindowDraw(SettingsWin* settingsWin);
/**
 * Name: settingsWindowDestroy
 * Description:
 * Destroys all the background and all of the buttons that suppose
 * be presented in load window.
 * frees settingsWin memory.
 */
void settingsWindowDestroy(SettingsWin* settingsWin);
/**
 * Name: settingsWindowManager
 * Description:
 * A function that manages all the transition between the
 * different states in setting window: game mode, difficulty, user color.
 */
SETTINGS_EVENT settingsWindowManager(SettingsWin* settingsWin,ChessGame* game, SDL_Event* event);
/**
 * Name: settingsWindowHide
 * Description:
 * Hides the setting window from the screen.
 */
void settingsWindowHide(SettingsWin* settingsWin);
/**
 * Name: settingsWindowShow
 * Description:
 * Initializes the settings window and present it on the screen.
 */
void settingsWindowShow(SettingsWin* settingsWin);
/**
 * Name: settingsWindowHandleEvent
 * Description:
 * Handles the different events that occurred in the window by the user,
 * reacts accordingly and calls the matching function that handles a specific state.
 * returns an appropriate SETTINGS_EVENT message if it succeeded or not.
 */
SETTINGS_EVENT settingsWindowHandleEvent(SettingsWin* settingsWin, SDL_Event* event);
/**
 * Name: difficultyHandleEvent
 * Description:
 * Handles the different events that occurred in the difficulty state by the user,
 * reacts accordingly.
 * returns an appropriate SETTINGS_EVENT message if it succeeded or not.
 */
SETTINGS_EVENT difficultyHandleEvent(SettingsWin* settingsWin, Button* button);
/**
 * Name: gameModeHandleEvent
 * Description:
 * Handles the different events that occurred in the game mode state by the user,
 * reacts accordingly.
 * returns an appropriate SETTINGS_EVENT message if it succeeded or not.
 */
SETTINGS_EVENT gameModeHandleEvent(SettingsWin* settingsWin, Button* button);
/**
 * Name: userColorHandleEvent
 * Description:
 * Handles the different events that occurred in the user color state by the user,
 * reacts accordingly.
 * returns an appropriate SETTINGS_EVENT message if it succeeded or not.
 */
SETTINGS_EVENT userColorHandleEvent(SettingsWin* settingsWin, Button* button);
/**
 * Name: switchActiveButtons
 * Description:
 * A function that manages all the transition between the selected
 * buttons. turns on the last one that has been selected.
 */
void switchActiveButtons(Button** buttons, int prevButton,int newButton);
/**
 * Name: promoteState
 * Description:
 * A function that promotes the current state to the next one.
 */
void promoteState(SettingsWin* settingsWin);
/**
 * Name: demoteState
 * Description:
 * A function that demotes the current state to the previous one.
 */
void demoteState(SettingsWin* settingsWin);

#endif /* GRAPHICS_CHESSSETTINGSWIN_H_ */
