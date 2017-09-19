/*
 * ChessSettingsWin.c
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: ido abulafya
 */
#include "ChessSettingsWin.h"

SettingsWin* settingsWindowCreate(WINDOW_TYPE backType) {
	SettingsWin* settingsWin = NULL;
	settingsWin->simpleWindow = NULL;
	settingsWin->difficultyButtons = NULL;
	settingsWin->normalButtons = NULL;
	settingsWin->gameModeButtons = NULL;
	settingsWin->userColorButtons = NULL;
	settingsWin = (SettingsWin*) malloc(sizeof(SettingsWin));
	if (settingsWin == NULL) {
		printMallocError();
		return NULL;
	}
	settingsWin->simpleWindow = simpleWindowCreate(backType);
	// Check that the window was successfully created
	if (settingsWin->simpleWindow == NULL) {
		settingsWindowDestroy(settingsWin);
		return NULL;
	}
	if(generateDifficutyButtons(settingsWin) == SETTINGS_FAILED || generateGameModeButtons(settingsWin) == SETTINGS_FAILED ||
			generateUserColorButtons(settingsWin) == SETTINGS_FAILED || generateNormalButtons(settingsWin) == SETTINGS_FAILED){
		settingsWindowDestroy(settingsWin);
		return NULL;
	}
	return settingsWin;
}

SETTINGS_MESSAGE generateDifficutyButtons(SettingsWin* settingsWin) {
	settingsWin->difficultyButtons = (Button**) malloc(sizeof(Button*) * SETTINGS_NUM_OF_DIFFICULTY_BUTTONS);
	if (settingsWin->difficultyButtons == NULL) {
		printMallocError();
		return SETTINGS_FAILED;
	}
	BUTTON_TYPE difficultyTypes[SETTINGS_NUM_OF_DIFFICULTY_BUTTONS] = {
			DIFFICULTY_TITLE_BUTTON,
			DIFFICULTY_1_BUTTON,
			DIFFICULTY_2_BUTTON,
			DIFFICULTY_3_BUTTON,
			DIFFICULTY_4_BUTTON,
			DIFFICULTY_5_BUTTON };
	bool ActiveDifficultyButtons[SETTINGS_NUM_OF_DIFFICULTY_BUTTONS] = { true, false, false, false, false, false };
	bool ClickableDifficultyButtons[SETTINGS_NUM_OF_DIFFICULTY_BUTTONS] = { false, true, true, true, true, true };
	if (buttonArrayCreate(settingsWin->difficultyButtons, difficultyTypes, ActiveDifficultyButtons, ClickableDifficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS) == BUTTON_FAILED) {
		free(settingsWin->difficultyButtons);
		settingsWin->difficultyButtons = NULL;
		return SETTINGS_FAILED;
	}
	return SETTINGS_SUCCESS;
}

SETTINGS_MESSAGE generateGameModeButtons(SettingsWin* settingsWin) {
	settingsWin->gameModeButtons = (Button**) malloc(sizeof(Button*) * SETTINGS_NUM_OF_GAMEMODE_BUTTONS);
	if (settingsWin->gameModeButtons == NULL) {
		printMallocError();
		return SETTINGS_FAILED;
	}
	BUTTON_TYPE GameModeTypes[SETTINGS_NUM_OF_DIFFICULTY_BUTTONS] = {
			GAME_MODE_TITLE_BUTTON,
			GAME_MODE_1_BUTTON,
			GAME_MODE_2_BUTTON };
	bool ActiveGameModeButtons[SETTINGS_NUM_OF_GAMEMODE_BUTTONS] = {true, false, false};
	bool ClickableGameModeButtons[SETTINGS_NUM_OF_GAMEMODE_BUTTONS] = {false, true, true};
	if (buttonArrayCreate(settingsWin->gameModeButtons, GameModeTypes, ActiveGameModeButtons, ClickableGameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS) == BUTTON_FAILED) {
		free(settingsWin->gameModeButtons);
		settingsWin->gameModeButtons = NULL;
		return SETTINGS_FAILED;
	}
	return SETTINGS_SUCCESS;
}

SETTINGS_MESSAGE generateUserColorButtons(SettingsWin* settingsWin) {
	settingsWin->userColorButtons = (Button**) malloc(sizeof(Button*) * SETTINGS_NUM_OF_USERCOLOR_BUTTONS);
	if (settingsWin->userColorButtons == NULL) {
		printMallocError();
		return SETTINGS_FAILED;
	}
	BUTTON_TYPE userColorTypes[SETTINGS_NUM_OF_USERCOLOR_BUTTONS] = {
			USER_COLOR_TITLE_BUTTON,
			COLOR_BLACK_PLAYER_BUTTON,
			COLOR_WHITE_PLAYER_BUTTON };
	bool ActiveUserColorButtons[SETTINGS_NUM_OF_USERCOLOR_BUTTONS] = {true, false, false};
	bool ClickableUserColorButtons[SETTINGS_NUM_OF_USERCOLOR_BUTTONS] = {false, true, true};
	if (buttonArrayCreate(settingsWin->userColorButtons, userColorTypes, ActiveUserColorButtons, ClickableUserColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS) == BUTTON_FAILED) {
		free(settingsWin->userColorButtons);
		settingsWin->userColorButtons = NULL;
		return SETTINGS_FAILED;
	}
	return SETTINGS_SUCCESS;
}

SETTINGS_MESSAGE generateNormalButtons(SettingsWin* settingsWin) {
	settingsWin->normalButtons = (Button**) malloc(sizeof(Button*) * SETTINGS_NUM_OF_NORMAL_BUTTONS);
	if (settingsWin->normalButtons == NULL) {
		printMallocError();
		return SETTINGS_FAILED;
	}
	BUTTON_TYPE normalTypes[SETTINGS_NUM_OF_NORMAL_BUTTONS] = {
			SETTINGS_START_BUTTON,
			SETTINGS_NEXT_BUTTON,
			SETTINGS_BACK_BUTTON };
	bool ActiveNormalButtons[SETTINGS_NUM_OF_NORMAL_BUTTONS] = {true, false, false};
	bool ClickableNormalButtons[SETTINGS_NUM_OF_NORMAL_BUTTONS] = {false, true, true};
	if (buttonArrayCreate(settingsWin->normalButtons, normalTypes, ActiveNormalButtons, ClickableNormalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS) == BUTTON_FAILED) {
		free(settingsWin->normalButtons);
		settingsWin->normalButtons = NULL;
		return SETTINGS_FAILED;
	}
	return SETTINGS_SUCCESS;
}

SETTINGS_MESSAGE settingsWindowDraw(SettingsWin* settingsWin, SETTING_STATE state){
	switch(state){
	case DIFFICULTY_STATE:
		if (simpleWindowDraw(settingsWin->simpleWindow,settingsWin->difficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS) == SIMPLE_WINDOW_FAILED ||
				drawButton(settingsWin->normalButtons[1], settingsWin->simpleWindow->renderer) == BUTTON_FAILED) // drawing next button
			return SETTINGS_FAILED;
		break;
	case GAME_MODE_STATE:
		if (simpleWindowDraw(settingsWin->simpleWindow,settingsWin->gameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS) == SIMPLE_WINDOW_FAILED ||
				drawButton(settingsWin->normalButtons[1], settingsWin->simpleWindow->renderer) == BUTTON_FAILED) // drawing next button
			return SETTINGS_FAILED;
		break;
	case USER_COLOR_STATE:
		if (simpleWindowDraw(settingsWin->simpleWindow,settingsWin->userColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS) == SIMPLE_WINDOW_FAILED ||
				drawButton(settingsWin->normalButtons[0], settingsWin->simpleWindow->renderer) == BUTTON_FAILED) // drawing start button
			return SETTINGS_FAILED;
		break;
	}
	if (drawButton(settingsWin->normalButtons[2], settingsWin->simpleWindow->renderer) == BUTTON_FAILED) return SETTINGS_FAILED; // drawing back button
	return SETTINGS_SUCCESS;
}

void settingsWindowDestroy(SettingsWin* settingsWin) {
	if (settingsWin == NULL) return;
	simpleWindowDestroy(settingsWin->simpleWindow);
	buttonArrayDestroy(settingsWin->difficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS);
	buttonArrayDestroy(settingsWin->gameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS);
	buttonArrayDestroy(settingsWin->userColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS);
	buttonArrayDestroy(settingsWin->normalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS);

}

SETTINGS_EVENT settingsWindowHandleEvent(SettingsWin* settingsWin, SDL_Event* event,SETTING_STATE state) {
	if (!event) {
		return SETTINGS_FAILED;
	}
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		switch(state){
		case DIFFICULTY_STATE:
			button = whichButtonWasClicked(settingsWin->difficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS,event->button.x, event->button.y);
			if(button == NULL) button = whichButtonWasClicked(settingsWin->normalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS,event->button.x, event->button.y);
			return difficultyHandleEvent(button);
		case GAME_MODE_STATE:
			button = whichButtonWasClicked(settingsWin->gameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS,event->button.x, event->button.y);
			if(button == NULL) button = whichButtonWasClicked(settingsWin->normalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS,event->button.x, event->button.y);
			return gameModeHandleEvent(button);
		case USER_COLOR_STATE:
			button = whichButtonWasClicked(settingsWin->userColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS,event->button.x, event->button.y);
			if(button == NULL) button = whichButtonWasClicked(settingsWin->normalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS,event->button.x, event->button.y);
			return userColorHandleEvent(button);
		default:
			break;
		}
		break;
	}
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			return SETTINGS_EXIT_EVENT;
		break;
	default:
		break;
	}
	return SETTINGS_NONE_EVENT;
}

SETTINGS_EVENT difficultyHandleEvent(Button* button){
	if(button == NULL) return SETTINGS_NONE_EVENT;
	switch(button->type){
	case DIFFICULTY_1_BUTTON:
		return DIFFICULTY_1_EVENT;
		break;
	case DIFFICULTY_2_BUTTON:
		return DIFFICULTY_2_EVENT;
		break;
	case DIFFICULTY_3_BUTTON:
		return DIFFICULTY_3_EVENT;
		break;
	case DIFFICULTY_4_BUTTON:
		return DIFFICULTY_4_EVENT;
		break;
	case DIFFICULTY_5_BUTTON:
		return DIFFICULTY_5_EVENT;
		break;
	case SETTINGS_NEXT_BUTTON:
		return SETTINGS_NEXT_EVENT;
		break;
	case SETTINGS_BACK_BUTTON:
		return SETTINGS_BACK_EVENT;
		break;
	default:
		return SETTINGS_NONE_EVENT;

	}
}

SETTINGS_EVENT gameModeHandleEvent(Button* button){
	if(button == NULL) return SETTINGS_NONE_EVENT;
	switch(button->type){
	case GAME_MODE_1_BUTTON:
		return GAME_MODE_1_EVENT;
		break;
	case GAME_MODE_2_BUTTON:
		return GAME_MODE_2_EVENT;
		break;
	case SETTINGS_NEXT_BUTTON:
		return SETTINGS_NEXT_EVENT;
		break;
	case SETTINGS_BACK_BUTTON:
		return SETTINGS_BACK_EVENT;
		break;
	default:
		return SETTINGS_NONE_EVENT;
	}
}

SETTINGS_EVENT userColorHandleEvent(Button* button){
	if(button == NULL) return SETTINGS_NONE_EVENT;
	switch(button->type){
	case GAME_MODE_1_BUTTON:
		return GAME_MODE_1_EVENT;
		break;
	case GAME_MODE_2_BUTTON:
		return GAME_MODE_2_EVENT;
		break;
	case SETTINGS_START_BUTTON:
		return SETTING_START_EVENT;
		break;
	case SETTINGS_BACK_BUTTON:
		return SETTINGS_BACK_EVENT;
		break;
	default:
		return SETTINGS_NONE_EVENT;
	}
}

void settingsWindowHide(SettingsWin* settingsWin) {
	simpleWindowHide(settingsWin->simpleWindow);
}

void settingsWindowShow(SettingsWin* settingsWin) {
	simpleWindowShow(settingsWin->simpleWindow);
}
