/*
 * ChessSettingsWin.c
 *
 *  Created on: 19 בספט׳ 2017
 *      Author: ido abulafya
 */
#include "ChessSettingsWin.h"

SettingsWin* settingsWindowCreate(WINDOW_TYPE backType) {
	SettingsWin* settingsWin = (SettingsWin*) malloc(sizeof(SettingsWin));
	if (settingsWin == NULL) {
		printMallocError();
		return NULL;
	}
	settingsWin->simpleWindow = NULL;
	settingsWin->difficultyButtons = NULL;
	settingsWin->normalButtons = NULL;
	settingsWin->gameModeButtons = NULL;
	settingsWin->userColorButtons = NULL;
	settingsWin->gridTexture = NULL;
	settingsWin->difficultySelect = NOT_CHOOSED_SETTINGS;
	settingsWin->gameModeSelect = NOT_CHOOSED_SETTINGS;
	settingsWin->userColorSelect = NOT_CHOOSED_SETTINGS;
	settingsWin->state = GAME_MODE_STATE;
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

	SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/gameSettings.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		settingsWindowDestroy(settingsWin);
		return NULL;
	}

	settingsWin->gridTexture = SDL_CreateTextureFromSurface(settingsWin->simpleWindow->renderer,loadingSurface);
	if (settingsWin->gridTexture == NULL) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		settingsWindowDestroy(settingsWin);
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	return settingsWin;
}

SETTINGS_MESSAGE updateSettingsWindow(SettingsWin* settingsWin){
	settingsWin->difficultySelect = NOT_CHOOSED_SETTINGS;
	settingsWin->gameModeSelect = NOT_CHOOSED_SETTINGS;
	settingsWin->userColorSelect = NOT_CHOOSED_SETTINGS;
	buttonArrayDestroy(settingsWin->difficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS);
	free(settingsWin->difficultyButtons);
	settingsWin->difficultyButtons = NULL;

	buttonArrayDestroy(settingsWin->gameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS);
	free(settingsWin->gameModeButtons);
	settingsWin->gameModeButtons = NULL;

	buttonArrayDestroy(settingsWin->userColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS);
	free(settingsWin->userColorButtons);
	settingsWin->userColorButtons = NULL;

	buttonArrayDestroy(settingsWin->normalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS);
	free(settingsWin->normalButtons);
	settingsWin->normalButtons = NULL;

	if(generateDifficutyButtons(settingsWin) == SETTINGS_FAILED || generateGameModeButtons(settingsWin) == SETTINGS_FAILED ||
			generateUserColorButtons(settingsWin) == SETTINGS_FAILED || generateNormalButtons(settingsWin) == SETTINGS_FAILED){
		return SETTINGS_FAILED;
	}
	return SETTINGS_SUCCESS;
}

void updateNormalButtons(SettingsWin* settingsWin){

	settingsWin->normalButtons[START_INDEX]->isClickable = false;
	settingsWin->normalButtons[NEXT_INDEX]->isClickable = false;

	switch(settingsWin->state){
	case DIFFICULTY_STATE:
		settingsWin->normalButtons[NEXT_INDEX]->isClickable = (settingsWin->difficultySelect != NOT_CHOOSED_SETTINGS)? true : false;
		break;
	case GAME_MODE_STATE:
		if(settingsWin->gameModeSelect == 2) settingsWin->normalButtons[START_INDEX]->isClickable = true;
		else settingsWin->normalButtons[NEXT_INDEX]->isClickable = (settingsWin->gameModeSelect != NOT_CHOOSED_SETTINGS) ? true : false;
		break;
	case USER_COLOR_STATE:
		settingsWin->normalButtons[START_INDEX]->isClickable = (settingsWin->userColorSelect != NOT_CHOOSED_SETTINGS) ? true : false;
		break;
	}
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
	if (buttonArrayCreate(settingsWin->simpleWindow->renderer,settingsWin->difficultyButtons, difficultyTypes, ActiveDifficultyButtons, ClickableDifficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS) == BUTTON_FAILED) {
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
	if (buttonArrayCreate(settingsWin->simpleWindow->renderer,settingsWin->gameModeButtons, GameModeTypes, ActiveGameModeButtons, ClickableGameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS) == BUTTON_FAILED) {
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
	if (buttonArrayCreate(settingsWin->simpleWindow->renderer,settingsWin->userColorButtons, userColorTypes, ActiveUserColorButtons, ClickableUserColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS) == BUTTON_FAILED) {
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
	bool ActiveNormalButtons[SETTINGS_NUM_OF_NORMAL_BUTTONS] = {true, true, true};
	bool ClickableNormalButtons[SETTINGS_NUM_OF_NORMAL_BUTTONS] = {false, false, true};
	if (buttonArrayCreate(settingsWin->simpleWindow->renderer,settingsWin->normalButtons, normalTypes, ActiveNormalButtons, ClickableNormalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS) == BUTTON_FAILED) {
		free(settingsWin->normalButtons);
		settingsWin->normalButtons = NULL;
		return SETTINGS_FAILED;
	}
	return SETTINGS_SUCCESS;
}

SETTINGS_MESSAGE settingsWindowDraw(SettingsWin* settingsWin){
	SDL_Rect rec = { .x = 0, .y = 0, .w = WIDTH_SIZE, .h = HEIGHT_SIZE };
	SDL_SetRenderDrawColor(settingsWin->simpleWindow->renderer, 255, 255, 255, 255); //Background is white.
	SDL_RenderClear(settingsWin->simpleWindow->renderer);
	SDL_RenderCopy(settingsWin->simpleWindow->renderer, settingsWin->gridTexture, NULL, &rec);

	int gameModeButton = (settingsWin->gameModeSelect == 2) ? START_INDEX : NEXT_INDEX;
	switch(settingsWin->state){
	case DIFFICULTY_STATE:
		simpleWindowAddingButtons(settingsWin->simpleWindow,settingsWin->difficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS);
		addButtonToRenderer(settingsWin->normalButtons[NEXT_INDEX], settingsWin->simpleWindow->renderer); // drawing next button
		return SETTINGS_FAILED;
		break;
	case GAME_MODE_STATE:
		simpleWindowAddingButtons(settingsWin->simpleWindow,settingsWin->gameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS);
		addButtonToRenderer(settingsWin->normalButtons[gameModeButton], settingsWin->simpleWindow->renderer); // drawing next button
		return SETTINGS_FAILED;
		break;
	case USER_COLOR_STATE:
		simpleWindowAddingButtons(settingsWin->simpleWindow,settingsWin->userColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS);
		addButtonToRenderer(settingsWin->normalButtons[START_INDEX], settingsWin->simpleWindow->renderer); // drawing start button
		return SETTINGS_FAILED;
		break;
	}
	addButtonToRenderer(settingsWin->normalButtons[BACK_INDEX], settingsWin->simpleWindow->renderer); // drawing back button
	SDL_RenderPresent(settingsWin->simpleWindow->renderer);
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

SETTINGS_EVENT settingsWindowManager(SettingsWin* settingsWin,ChessGame* game, SDL_Event* event){
	if (!event || !game || !settingsWin) return SETTINGS_EXIT_EVENT;
	if(event->button.button != SDL_BUTTON_LEFT) return SETTINGS_NONE_EVENT;
	SETTINGS_EVENT setEvent;
	setEvent = settingsWindowHandleEvent(settingsWin,event);
	if(setEvent == SETTINGS_START_EVENT){
		simpleSettingsSetter(game,settingsWin->difficultySelect,settingsWin->gameModeSelect,settingsWin->userColorSelect);
		return SETTINGS_START_EVENT;
	}
	else if(setEvent == SETTINGS_NEXT_EVENT) {
		promoteState(settingsWin);
		updateNormalButtons(settingsWin);
		return SETTINGS_NORMAL_EVENT;
	}
	else if(setEvent == SETTINGS_BACK_EVENT) {
		if(settingsWin->state == GAME_MODE_STATE) return SETTINGS_BACK_EVENT;
		demoteState(settingsWin);
		updateNormalButtons(settingsWin);
		return SETTINGS_NORMAL_EVENT;
	}
	return setEvent;

}

SETTINGS_EVENT settingsWindowHandleEvent(SettingsWin* settingsWin, SDL_Event* event) {
	if (!event) {
		return SETTINGS_FAILED;
	}
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		button = whichButtonWasClicked(settingsWin->normalButtons,SETTINGS_NUM_OF_NORMAL_BUTTONS,event->button.x, event->button.y);
		switch(settingsWin->state){
		case DIFFICULTY_STATE:
			if(button == NULL) button = whichButtonWasClicked(settingsWin->difficultyButtons,SETTINGS_NUM_OF_DIFFICULTY_BUTTONS,event->button.x, event->button.y);
			return difficultyHandleEvent(settingsWin,button);
		case GAME_MODE_STATE:
			if(button == NULL) button = whichButtonWasClicked(settingsWin->gameModeButtons,SETTINGS_NUM_OF_GAMEMODE_BUTTONS,event->button.x, event->button.y);
			return gameModeHandleEvent(settingsWin,button);
		case USER_COLOR_STATE:
			if(button == NULL) button = whichButtonWasClicked(settingsWin->userColorButtons,SETTINGS_NUM_OF_USERCOLOR_BUTTONS,event->button.x, event->button.y);
			return userColorHandleEvent(settingsWin,button);
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

SETTINGS_EVENT difficultyHandleEvent(SettingsWin* settingsWin, Button* button){
	if(button == NULL) return SETTINGS_NONE_EVENT;
	int prevDifficulty = settingsWin->difficultySelect;
	switch(button->type){
	case DIFFICULTY_1_BUTTON:
		settingsWin->difficultySelect = 1;
		break;
	case DIFFICULTY_2_BUTTON:
		settingsWin->difficultySelect = 2;
		break;
	case DIFFICULTY_3_BUTTON:
		settingsWin->difficultySelect = 3;
		break;
	case DIFFICULTY_4_BUTTON:
		settingsWin->difficultySelect = 4;
		break;
	case DIFFICULTY_5_BUTTON:
		settingsWin->difficultySelect = 5;
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
	if(settingsWin->difficultySelect == prevDifficulty) return SETTINGS_NONE_EVENT;
	switchActiveButtons(settingsWin->difficultyButtons,prevDifficulty, settingsWin->difficultySelect);
	settingsWin->normalButtons[NEXT_INDEX]->isClickable = true;
	return SETTINGS_NORMAL_EVENT;
}

SETTINGS_EVENT gameModeHandleEvent(SettingsWin* settingsWin, Button* button){
	if(button == NULL) return SETTINGS_NONE_EVENT;
	int prevGameMode = settingsWin->gameModeSelect;
	switch(button->type){
	case GAME_MODE_1_BUTTON:
		settingsWin->gameModeSelect = 1;
		break;
	case GAME_MODE_2_BUTTON:
		settingsWin->gameModeSelect = 2;
		break;
	case SETTINGS_NEXT_BUTTON:
		return SETTINGS_NEXT_EVENT;
		break;
	case SETTINGS_BACK_BUTTON:
		return SETTINGS_BACK_EVENT;
		break;
	case SETTINGS_START_BUTTON:
		return SETTINGS_START_EVENT;
		break;
	default:
		return SETTINGS_NONE_EVENT;
	}
	if(settingsWin->gameModeSelect == prevGameMode) return SETTINGS_NONE_EVENT;
	switchActiveButtons(settingsWin->gameModeButtons,prevGameMode,settingsWin->gameModeSelect);

	if(settingsWin->gameModeSelect == 2) {
		settingsWin->normalButtons[START_INDEX]->isClickable = true;
		settingsWin->normalButtons[NEXT_INDEX]->isClickable = false;
	}
	else {
		settingsWin->normalButtons[NEXT_INDEX]->isClickable = true ;
		settingsWin->normalButtons[START_INDEX]->isClickable = false;
	}
	return SETTINGS_NORMAL_EVENT;
}

SETTINGS_EVENT userColorHandleEvent(SettingsWin* settingsWin, Button* button){
	if(button == NULL) return SETTINGS_NONE_EVENT;
	int prevUserColor = settingsWin->userColorSelect;
	switch(button->type){
	case COLOR_BLACK_PLAYER_BUTTON:
		settingsWin->userColorSelect = 0;
		break;
	case COLOR_WHITE_PLAYER_BUTTON:
		settingsWin->userColorSelect = 1;
		break;
	case SETTINGS_START_BUTTON:
		return SETTINGS_START_EVENT;
		break;
	case SETTINGS_BACK_BUTTON:
		return SETTINGS_BACK_EVENT;
		break;
	default:
		return SETTINGS_NONE_EVENT;
	}
	if(settingsWin->userColorSelect == prevUserColor) return SETTINGS_NONE_EVENT;
	switchActiveButtons(settingsWin->userColorButtons,prevUserColor,settingsWin->userColorSelect);
	settingsWin->normalButtons[START_INDEX]->isClickable = true;
	return SETTINGS_NORMAL_EVENT;
}

void settingsWindowHide(SettingsWin* settingsWin) {
	simpleWindowHide(settingsWin->simpleWindow);
}

void settingsWindowShow(SettingsWin* settingsWin) {
	updateNormalButtons(settingsWin);
	simpleWindowShow(settingsWin->simpleWindow);
}

void switchActiveButtons(Button** buttons, int prevButton,int newButton){
	buttons[newButton]->isActive = true;
	if(prevButton != NOT_CHOOSED_SETTINGS) buttons[prevButton]->isActive = false;
}

void promoteState(SettingsWin* settingsWin){
	if(!settingsWin) return;
	SETTING_STATE state = settingsWin->state;
	switch(state){
	case GAME_MODE_STATE:
		settingsWin->state = DIFFICULTY_STATE;
		break;
	case DIFFICULTY_STATE:
		settingsWin->state = USER_COLOR_STATE;
		break;
	default:
		break;
	}
}

void demoteState(SettingsWin* settingsWin){
	if(!settingsWin) return;
	SETTING_STATE state = settingsWin->state;
	switch(state){
	case DIFFICULTY_STATE:
		settingsWin->state = GAME_MODE_STATE;
		break;
	case USER_COLOR_STATE:
		settingsWin->state = DIFFICULTY_STATE;
		break;
	default:
		break;
	}
}
