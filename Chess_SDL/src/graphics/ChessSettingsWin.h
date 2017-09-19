/*
 * ChessSettingsWin.h
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: ido abulafya
 */

#ifndef GRAPHICS_CHESSSETTINGSWIN_H_
#define GRAPHICS_CHESSSETTINGSWIN_H_

#include "SimpleWindow.h"

#define SETTINGS_NUM_OF_DIFFICULTY_BUTTONS 6
#define SETTINGS_NUM_OF_USERCOLOR_BUTTONS 3
#define SETTINGS_NUM_OF_GAMEMODE_BUTTONS 3
#define SETTINGS_NUM_OF_NORMAL_BUTTONS 4

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
	SETTING_START_EVENT,
	SETTINGS_NEXT_EVENT,
	SETTINGS_BACK_EVENT,
	GAME_MODE_1_EVENT,
	GAME_MODE_2_EVENT,
	DIFFICULTY_1_EVENT,
	DIFFICULTY_2_EVENT,
	DIFFICULTY_3_EVENT,
	DIFFICULTY_4_EVENT,
	DIFFICULTY_5_EVENT,
	COLOR_BLACK_PLAYER_EVENT,
	COLOR_WHITE_PLAYER_EVENT,
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
}SettingsWin;

SettingsWin* settingsWindowCreate(WINDOW_TYPE backType);
SETTINGS_MESSAGE generateDifficutyButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateGameModeButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateUserColorButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE generateNormalButtons(SettingsWin* settingsWin);
SETTINGS_MESSAGE settingsWindowDraw(SettingsWin* settingsWin,SETTING_STATE state);
void settingsWindowDestroy(SettingsWin* settingsWin);
void settingsWindowHide(SettingsWin* settingsWin);
void settingsWindowShow(SettingsWin* settingsWin);
SETTINGS_EVENT settingsWindowHandleEvent(SettingsWin* settingsWin, SDL_Event* event,SETTING_STATE state);
SETTINGS_EVENT difficultyHandleEvent(Button* button);
SETTINGS_EVENT gameModeHandleEvent(Button* button);
SETTINGS_EVENT userColorHandleEvent(Button* button);

#endif /* GRAPHICS_CHESSSETTINGSWIN_H_ */
