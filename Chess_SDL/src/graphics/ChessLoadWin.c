/*
 * ChessLoadWin.c
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */

#include "ChessLoadWin.h"



LoadWin* loadWindowCreate(WINDOW_TYPE backType) {
	LoadWin* loadWin = NULL;
	loadWin->simpleWindow = NULL;
	loadWin->regularButtons = NULL;
	loadWin->slotsButtons = NULL;
	loadWin = (LoadWin*) malloc(sizeof(LoadWin));
	if (loadWin == NULL ) {
		printMallocError();
		return NULL;
	}
	loadWin->simpleWindow = simpleWindowCreate(backType);
	// Check that the window was successfully created
	if (loadWin->simpleWindow == NULL) {
		loadWindowDestroy(loadWin);
		return NULL;
	}

	if(generateRegularButtons(loadWin) == LOAD_FAILED || generateSlotsButtons(loadWin) == LOAD_FAILED){
		loadWindowDestroy(loadWin);
		return NULL;
	}
	return loadWin;
}

LOAD_MESSAGE generateRegularButtons(LoadWin* loadWin) {
	loadWin->regularButtons = (Button**) malloc(sizeof(Button*) * LOAD_NUM_OF_REGULAR_BUTTONS);
	if (loadWin->regularButtons == NULL) {
		printMallocError();
		return LOAD_FAILED;
	}
	BUTTON_TYPE loadRegularTypes[LOAD_NUM_OF_REGULAR_BUTTONS] = {
			LOAD_TITLE_BUTTON,
			LOAD_BACK_BUTTON,
			LOAD_BUTTON };
	bool loadActiveRegularButtons[LOAD_NUM_OF_REGULAR_BUTTONS] = {true,true,false};
	bool loadClickableRegularButtons[LOAD_NUM_OF_REGULAR_BUTTONS] = {false,true, false};
	if (buttonArrayCreate(loadWin->regularButtons, loadRegularTypes,loadActiveRegularButtons, loadClickableRegularButtons,LOAD_NUM_OF_REGULAR_BUTTONS) == BUTTON_FAILED) {
		free(loadWin->regularButtons);
		loadWin->regularButtons = NULL;
		return LOAD_FAILED;
	}
	return LOAD_SUCCESS;
}

LOAD_MESSAGE generateSlotsButtons(LoadWin* loadWin) {
	loadWin->slotsButtons = (Button**) malloc(sizeof(Button*) * LOAD_NUM_OF_SLOTS);
	if (loadWin->slotsButtons == NULL) {
		printMallocError();
		return LOAD_FAILED;
	}
	BUTTON_TYPE loadSlotsTypes[LOAD_NUM_OF_SLOTS] = {
			GAME_SLOT1_BUTTON,
			GAME_SLOT2_BUTTON,
			GAME_SLOT3_BUTTON,
			GAME_SLOT4_BUTTON,
			GAME_SLOT5_BUTTON };

	bool loadActiveSlotsButtons[LOAD_NUM_OF_SLOTS] = {false,false,false,false,false};
	bool loadClickableSlotsButtons[LOAD_NUM_OF_SLOTS] = {true,true, true,true,true};
	if (buttonArrayCreate(loadWin->slotsButtons, loadSlotsTypes,loadActiveSlotsButtons, loadClickableSlotsButtons,LOAD_NUM_OF_SLOTS) == BUTTON_FAILED) {
		free(loadWin->slotsButtons);
		loadWin->slotsButtons = NULL;
		return LOAD_FAILED;
	}
	return LOAD_SUCCESS;
}

LOAD_MESSAGE loadWindowDraw(LoadWin* loadWin, int numOfSlots){
	if(simpleWindowDraw(loadWin->simpleWindow,loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS) == SIMPLE_WINDOW_FAILED ||
			simpleWindowDraw(loadWin->simpleWindow,loadWin->slotsButtons,numOfSlots) == SIMPLE_WINDOW_FAILED){
		return LOAD_FAILED;
	}
	return LOAD_SUCCESS;
}

void loadWindowDestroy(LoadWin* loadWin) {
	if (loadWin == NULL) return;
	simpleWindowDestroy(loadWin->simpleWindow);
	buttonArrayDestroy(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS);
	buttonArrayDestroy(loadWin->slotsButtons,LOAD_NUM_OF_SLOTS);
	free(loadWin);
}

LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin,int numOfSlots, SDL_Event* event) {
	if (!event) {
		return LOAD_INVALID_ARGUMENT_EVENT;
	}
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		button = whichButtonWasClicked(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS,event->button.x, event->button.y);
		if(button == NULL) button = whichButtonWasClicked(loadWin->slotsButtons,numOfSlots,event->button.x, event->button.y);
		if(button == NULL) return LOAD_NONE_EVENT;
		switch(button->type){
		case LOAD_BACK_BUTTON:
			return LOAD_BACK_EVENT;
		case LOAD_BUTTON:
			return LOAD_LOAD_EVENT;
		case GAME_SLOT1_BUTTON:
			return LOAD_SLOT1_EVENT;
		case GAME_SLOT2_BUTTON:
			return LOAD_SLOT2_EVENT;
		case GAME_SLOT3_BUTTON:
			return LOAD_SLOT3_EVENT;
		case GAME_SLOT4_BUTTON:
			return LOAD_SLOT4_EVENT;
		case GAME_SLOT5_BUTTON:
			return LOAD_SLOT5_EVENT;
		default:
			return LOAD_NONE_EVENT;
		}
		break;
	}
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return LOAD_EXIT_EVENT;
		}
		break;
	default:
		return LOAD_NONE_EVENT;
	}
	return LOAD_NONE_EVENT;
}

void loadWindowHide(LoadWin* loadWin) {
	simpleWindowHide(loadWin->simpleWindow);
}

void loadWindowShow(LoadWin* loadWin) {
	simpleWindowShow(loadWin->simpleWindow);
}

