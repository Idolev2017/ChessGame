/*
 * ChessLoadWin.c
 *
 *  Created on: 18 ����� 2017
 *      Author: Dolev
 */

#include "ChessLoadWin.h"

LoadWin* loadWindowCreate(WINDOW_TYPE backType) {
	LoadWin* loadWin = NULL;
	loadWin = (LoadWin*) malloc(sizeof(LoadWin));
	if (loadWin == NULL ) {
		printMallocError();
		return NULL;
	}
	loadWin->simpleWindow = NULL;
	loadWin->regularButtons = NULL;
	loadWin->slotsButtons = NULL;
	loadWin->chosenSlot = NOT_CHOOSED_SLOT;
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
	loadWin->numOfSlots = scanSlotsInDirectory();;
	return loadWin;
}

LOAD_MESSAGE InitializeLoadWindow(LoadWin* loadWin){
	loadWin->chosenSlot = NOT_CHOOSED_SLOT;
	buttonArrayDestroy(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS);
	free(loadWin->regularButtons);
	loadWin->regularButtons = NULL;

	buttonArrayDestroy(loadWin->slotsButtons,LOAD_NUM_OF_SLOTS);
	free(loadWin->slotsButtons);
	loadWin->slotsButtons = NULL;

	if(generateRegularButtons(loadWin) == LOAD_FAILED || generateSlotsButtons(loadWin) == LOAD_FAILED){
		loadWindowDestroy(loadWin);
		return LOAD_FAILED;
	}
	return LOAD_SUCCESS;
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
			LOAD_LOAD_BUTTON };
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

LOAD_MESSAGE loadWindowDraw(LoadWin* loadWin){

	if(simpleWindowDraw(loadWin->simpleWindow,loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS) == SIMPLE_WINDOW_FAILED ||
			simpleWindowDraw(loadWin->simpleWindow,loadWin->slotsButtons,loadWin->numOfSlots) == SIMPLE_WINDOW_FAILED){
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

LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin,ChessGame* game, SDL_Event* event) {
	if (!event) {
		return LOAD_INVALID_ARGUMENT_EVENT;
	}
	if(event->button.button == SDL_BUTTON_RIGHT) return LOAD_NONE_EVENT;
	int prevSlot = loadWin->chosenSlot;
	Button* button;
	char path[] = SLOT1_PATH;
	bool flag = false;
	bool* loaded = &flag;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		button = whichButtonWasClicked(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS,event->button.x, event->button.y);
		if(button == NULL) button = whichButtonWasClicked(loadWin->slotsButtons,loadWin->numOfSlots,event->button.x, event->button.y);
		if(button == NULL) return LOAD_NONE_EVENT;
		switch(button->type){
		case LOAD_BACK_BUTTON:
			return LOAD_BACK_EVENT;
		case LOAD_LOAD_BUTTON:
			if(loadWin->chosenSlot == NOT_CHOOSED_SLOT) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR","load button is clickable", NULL);
				return LOAD_EXIT_EVENT;
			}
			path[strlen(path) - 5] = loadWin->chosenSlot + '0';
			loadGame(game,path,loaded);
			if(loaded == false) {
				printf("Game cannot be loaded from %s\n",path);
				return LOAD_EXIT_EVENT;
			}
			return LOAD_LOAD_EVENT;
			break;
		case GAME_SLOT1_BUTTON:
			loadWin->chosenSlot = 1;
			break;
		case GAME_SLOT2_BUTTON:
			loadWin->chosenSlot = 2;
			break;
		case GAME_SLOT3_BUTTON:
			loadWin->chosenSlot = 3;
			break;
		case GAME_SLOT4_BUTTON:
			loadWin->chosenSlot = 4;
			break;
		case GAME_SLOT5_BUTTON:
			loadWin->chosenSlot = 5;
			break;
		}
		switchActiveSlotButton(loadWin,prevSlot,loadWin->chosenSlot);
		loadWin->regularButtons[LOAD_INDEX]->isClickable = true;
		return LOAD_NORMAL_EVENT;
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

int scanSlotsInDirectory(){
	int numOfSlots = 0;
	char filePath[] = ".//src//GameSlots//gameSlot1.xml";
	FILE* file;
	for(int i = 1; i <= LOAD_NUM_OF_SLOTS; ++i){
		filePath[strlen(filePath) - 5] = i + '0';
		file = fopen(filePath, "r");
		if(file != NULL){
			numOfSlots++;
			fclose(file);
		}
		else{
			return numOfSlots;
		}
	}
	return numOfSlots;
}

LOAD_MESSAGE addGameSlot(LoadWin* loadWin,ChessGame* game){
	char path[] = SLOT1_PATH;
	char newPath[] = SLOT1_PATH;
	for(int i = loadWin->numOfSlots; 1<=i;--i){
		path[strlen(path) - 5] = i + '0';
		if(i == LOAD_NUM_OF_SLOTS) {
			remove(path);
			continue;
		}
		newPath[strlen(path) - 5] = i + '0' + 1;
		rename(path,newPath);
	}
	path[strlen(path) - 5] = '1';
	if(saveGame(game,path) == GAME_FAILED) return LOAD_FAILED;
	loadWin->numOfSlots = max(5,loadWin->numOfSlots + 1);
	return LOAD_SUCCESS;
}

void switchActiveSlotButton(LoadWin* loadWin,int prevSlot,int newSlot){
	loadWin->slotsButtons[newSlot-1]->isActive = true;
	if(prevSlot != NOT_CHOOSED_SLOT){
		loadWin->slotsButtons[prevSlot-1]->isActive = false;
	}
}
