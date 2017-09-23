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

SettingsWin* settingsWindowCreate(WINDOW_TYPE backType);
SETTINGS_MESSAGE updateSettingsWindow(SettingsWin* settingsWin);
void loadInitializeSelect(SettingsWin* settingsWin);
void updateNormalButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateDifficutyButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateGameModeButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateUserColorButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateNormalButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE settingsWindowDraw(SettingsWin* settingsWin);
void settingsWindowDestroy(SettingsWin* settingsWin);
SETTINGS_EVENT settingsWindowManager(SettingsWin* settingsWin,ChessGame* game, SDL_Event* event);
void settingsWindowHide(SettingsWin* settingsWin);
void settingsWindowShow(SettingsWin* settingsWin);
SETTINGS_EVENT settingsWindowHandleEvent(SettingsWin* settingsWin, SDL_Event* event);
SETTINGS_EVENT difficultyHandleEvent(SettingsWin* settingsWin, Button* button);
SETTINGS_EVENT gameModeHandleEvent(SettingsWin* settingsWin, Button* button);
SETTINGS_EVENT userColorHandleEvent(SettingsWin* settingsWin, Button* button);
void switchActiveButtons(Button** buttons, int prevButton,int newButton);
void promoteState(SettingsWin* settingsWin);
void demoteState(SettingsWin* settingsWin);

#endif /* GRAPHICS_CHESSSETTINGSWIN_H_ */
