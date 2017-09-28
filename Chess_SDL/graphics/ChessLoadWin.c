/*
 * ChessLoadWin.c
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */

#include "ChessLoadWin.h"

LoadWin* loadWindowCreate(WINDOW_TYPE backType) {
	LoadWin* loadWin = (LoadWin*) malloc(sizeof(LoadWin));
	if (loadWin == NULL ) {
		printMallocError();
		return NULL;
	}
	loadWin->simpleWindow = NULL;
	loadWin->regularButtons = NULL;
	loadWin->slotsButtons = NULL;
	loadWin->chosenSlot = NOT_CHOOSED_SLOT;
	loadWin->gridTexture = NULL;
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
	loadWin->numOfSlots = scanSlotsInDirectory();

	SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/gameLoad.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		loadWindowDestroy(loadWin);
		return NULL;
	}

	loadWin->gridTexture = SDL_CreateTextureFromSurface(loadWin->simpleWindow->renderer,loadingSurface);
	if (loadWin->gridTexture == NULL) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		loadWindowDestroy(loadWin);
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	return loadWin;
}

void InitializeLoadWindow(LoadWin* loadWin){
	if(loadWin == NULL) return;
	if(loadWin->chosenSlot != NOT_CHOOSED_SLOT){
		loadWin->slotsButtons[loadWin->chosenSlot-1]->isActive = false;
		loadWin->regularButtons[LOAD_INDEX]->isClickable = false;
	}
}

LOAD_MESSAGE generateRegularButtons(LoadWin* loadWin) {
	loadWin->regularButtons = (Button**) malloc(sizeof(Button*) * LOAD_NUM_OF_REGULAR_BUTTONS);
	if (loadWin->regularButtons == NULL) {
		printMallocError();
		return LOAD_FAILED;
	}
	BUTTON_TYPE loadRegularTypes[LOAD_NUM_OF_REGULAR_BUTTONS] = {
			LOAD_BACK_BUTTON,
			LOAD_LOAD_BUTTON };
	bool loadActiveRegularButtons[LOAD_NUM_OF_REGULAR_BUTTONS] = {true,true};
	bool loadClickableRegularButtons[LOAD_NUM_OF_REGULAR_BUTTONS] = {true, false};
	if (buttonArrayCreate(loadWin->simpleWindow->renderer,loadWin->regularButtons, loadRegularTypes,loadActiveRegularButtons, loadClickableRegularButtons,LOAD_NUM_OF_REGULAR_BUTTONS) == BUTTON_FAILED) {
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
	if (buttonArrayCreate(loadWin->simpleWindow->renderer,loadWin->slotsButtons, loadSlotsTypes,loadActiveSlotsButtons, loadClickableSlotsButtons,LOAD_NUM_OF_SLOTS) == BUTTON_FAILED) {
		free(loadWin->slotsButtons);
		loadWin->slotsButtons = NULL;
		return LOAD_FAILED;
	}
	return LOAD_SUCCESS;
}

LOAD_MESSAGE loadWindowDraw(LoadWin* loadWin){
	SDL_Rect rec = { .x = 0, .y = 0, .w = WIDTH_SIZE, .h = HEIGHT_SIZE };
	SDL_SetRenderDrawColor(loadWin->simpleWindow->renderer, 255, 255, 255, 255); //Background is white.
	SDL_RenderClear(loadWin->simpleWindow->renderer);
	SDL_RenderCopy(loadWin->simpleWindow->renderer, loadWin->gridTexture, NULL, &rec);
	if(simpleWindowAddingButtons(loadWin->simpleWindow,loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS) == SIMPLE_WINDOW_FAILED) return LOAD_FAILED;
	if(simpleWindowAddingButtons(loadWin->simpleWindow,loadWin->slotsButtons,loadWin->numOfSlots) == SIMPLE_WINDOW_FAILED) return LOAD_FAILED;
	SDL_RenderPresent(loadWin->simpleWindow->renderer);
	return LOAD_SUCCESS;
}

void loadWindowDestroy(LoadWin* loadWin) {
	if (loadWin == NULL) return;
	buttonArrayDestroy(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS);
	buttonArrayDestroy(loadWin->slotsButtons,LOAD_NUM_OF_SLOTS);
	simpleWindowDestroy(loadWin->simpleWindow);
	free(loadWin);
}

LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin, SDL_Event* event) {
	if (!event || !loadWin) {
		return LOAD_INVALID_ARGUMENT_EVENT;
	}
	if(event->button.button != SDL_BUTTON_LEFT) return LOAD_NONE_EVENT;
	int prevSlot = loadWin->chosenSlot;
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		button = whichButtonWasClicked(loadWin->regularButtons,LOAD_NUM_OF_REGULAR_BUTTONS,event->button.x, event->button.y);
		if(button == NULL) button = whichButtonWasClicked(loadWin->slotsButtons,loadWin->numOfSlots,event->button.x, event->button.y);
		if(button == NULL) return LOAD_NONE_EVENT;
		switch(button->type){
		case LOAD_BACK_BUTTON:
			return LOAD_BACK_EVENT;
		case LOAD_LOAD_BUTTON:
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
		default:
			break;
		}
		switchActiveSlotButton(loadWin,prevSlot,loadWin->chosenSlot);
		loadWin->regularButtons[LOAD_INDEX]->isClickable = true;
		loadWin->regularButtons[LOAD_INDEX]->isActive = true;
		return LOAD_NORMAL_EVENT;
		break;
	}
	default:
		return LOAD_NONE_EVENT;
	}
	return LOAD_NONE_EVENT;
}

void loadWindowHide(LoadWin* loadWin) {
	simpleWindowHide(loadWin->simpleWindow);
}

void loadWindowShow(LoadWin* loadWin) {
	InitializeLoadWindow(loadWin);
	simpleWindowShow(loadWin->simpleWindow);
}

int scanSlotsInDirectory(){
	int numOfSlots = 0;
	char filePath[] = SLOT1_PATH;
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
	path[strlen(path) - 5] = '0';
	bool wasSaved = saveGame(game,path);
	if(!wasSaved){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SAVE ERROR","The game couldn't be saved",NULL);
		return LOAD_FAILED;
	}
	for(int i = loadWin->numOfSlots; 0 <= i;--i){
		path[strlen(path) - 5] = i + '0';
		if(i == LOAD_NUM_OF_SLOTS) {
			remove(path);
			continue;
		}
		newPath[strlen(path) - 5] = i + '0' + 1;
		rename(path,newPath);
	}
	loadWin->numOfSlots = min(5,loadWin->numOfSlots + 1);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Save game","The game was saved",NULL);
	return LOAD_SUCCESS;
}

void switchActiveSlotButton(LoadWin* loadWin,int prevSlot,int newSlot){
	loadWin->slotsButtons[newSlot-1]->isActive = true;
	if(prevSlot == newSlot) return;
	if(prevSlot != NOT_CHOOSED_SLOT){
		loadWin->slotsButtons[prevSlot-1]->isActive = false;
	}
}
