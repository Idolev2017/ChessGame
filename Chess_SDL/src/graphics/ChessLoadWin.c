/*
 * ChessLoadWin.c
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */

#include "ChessLoadWin.h"
#include <SDL_video.h>
#include <stdio.h>

LoadWin* loadWindowCreate() {
	LoadWin* loadWin = NULL;
	loadWin = (LoadWin*) malloc(sizeof(LoadWin));
	if (loadWin == NULL ) {
		printMallocError();
		return NULL;
	}
	loadWin->simpleWindow = simpleWindowCreate(NONE_WINDOW);
	// Check that the window was successfully created
	if (loadWin->simpleWindow == NULL) {
		free(loadWin);
		return NULL ;
	}
	loadWin->regularButtons = (Button**) malloc(sizeof(Button*) * LOAD_NUM_OF_REGULAR_BUTTONS);
	if (loadWin->regularButtons == NULL) {
		printMallocError();
		simpleWindowDestroy(loadWin->simpleWindow);
		free(loadWin);
		return NULL;
	}
	loadWin->slotsButtons = (Button**) malloc(sizeof(Button*) * LOAD_NUM_OF_SLOTS);
	if (loadWin->slotsButtons == NULL) {
		printMallocError();
		simpleWindowDestroy(loadWin->simpleWindow);
		free(loadWin->regularButtons);
		free(loadWin);
		return NULL;
	}
	loadWin->num_of_slots = scanSlotsInDirectory();

	BUTTON_TYPE loadRegularTypes[LOAD_NUM_OF_REGULAR_BUTTONS] = {LOAD_BACK_BUTTON,LOAD_BUTTON,LOAD_TITLE_BUTTON};
	bool loadActiveRegularButtons[LOAD_NUM_OF_REGULAR_BUTTONS] = {true,false,true};
	bool loadClickableRegularButtons[LOAD_NUM_OF_REGULAR_BUTTONS] = {true,false,false};
	if(buttonArrayCreate(loadWin->regularButtons,loadRegularTypes,loadActiveRegularButtons,loadClickableRegularButtons,LOAD_NUM_OF_REGULAR_BUTTONS) == BUTTON_FAILED){
		simpleWindowDestroy(loadWin->simpleWindow);
		free(loadWin->regularButtons);
		free(loadWin->slotsButtons);
		free(loadWin);
		return NULL;
	}

	BUTTON_TYPE loadSlotsTypes[LOAD_NUM_OF_SLOTS] = {GAME_SLOT1_BUTTON,GAME_SLOT2_BUTTON,GAME_SLOT3_BUTTON,
			GAME_SLOT4_BUTTON,GAME_SLOT5_BUTTON};
	bool loadActiveSlotsButtons[LOAD_NUM_OF_SLOTS] = {false,false,false,false,false};
	bool loadClickableSlotsButtons[LOAD_NUM_OF_SLOTS] = {true,true,true,true,true};
	if(buttonArrayCreate(loadWin->slotsButtons,loadSlotsTypes,loadActiveSlotsButtons,loadClickableSlotsButtons,LOAD_NUM_OF_SLOTS) == BUTTON_FAILED){
		simpleWindowDestroy(loadWin->simpleWindow);
		free(loadWin->slotsButtons);
		buttonArrayDestroy(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS);
		free(loadWin);
		return NULL;
	}
	return loadWin;
}
void loadWindowDraw(LoadWin* loadWin){
	simpleWindowDraw(loadWin->simpleWindow,loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS);
	simpleWindowDraw(loadWin->simpleWindow,loadWin->slotsButtons,loadWin->num_of_slots);
}

void loadWindowDestroy(LoadWin* loadWin) {
	if (loadWin == NULL) return;
	simpleWindowDestroy(loadWin->simpleWindow);
	buttonArrayDestroy(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS);
	buttonArrayDestroy(loadWin->slotsButtons,LOAD_NUM_OF_SLOTS);
}

LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin, SDL_Event* event) {
	if (!event) {
		return LOAD_INVALID_ARGUMENT_EVENT;
	}
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		button = whichButtonWasClicked(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS,event->button.x, event->button.y);
		if(button == NULL) button = whichButtonWasClicked(loadWin->slotsButtons,loadWin->num_of_slots,event->button.x, event->button.y);
		if(button == NULL) return LOAD_NONE_EVENT;
		if (button->type == LOAD_BACK_BUTTON) {
			return LOAD_BACK_EVENT;
		}
		else if (button->type == LOAD_BUTTON) {
			return LOAD_LOAD_EVENT;
		}
		else if (button->type == GAME_SLOT1_BUTTON) {
			return LOAD_SLOT1_EVENT;
		}
		else if (button->type == GAME_SLOT2_BUTTON) {
			return LOAD_SLOT2_EVENT;
		}
		else if (button->type == GAME_SLOT3_BUTTON) {
			return LOAD_SLOT3_EVENT;
		}
		else if (button->type == GAME_SLOT4_BUTTON) {
			return LOAD_SLOT4_EVENT;
		}
		else if (button->type == GAME_SLOT5_BUTTON) {
			return LOAD_SLOT5_EVENT;
		}
		break;
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

int scanSlotsInDirectory(){
	return 1;
}
