#include "ChessGUIManager.h"

#include <stdio.h>
#include <stdlib.h>

GuiManager* ChessGUIManagerCreate() {
	GuiManager* guiManager = (GuiManager*) malloc(sizeof(GuiManager));
	if (guiManager == NULL) {
		printMallocError();
		return NULL;
	}
	guiManager->game = NULL;
	guiManager->mainWin = NULL;
	guiManager->gameWin = NULL;
	guiManager->loadWin = NULL;
	guiManager->settingsWin = NULL;

	guiManager->mainWin = mainWindowCreate();
	if (guiManager->mainWin == NULL) {
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	guiManager->activeWin = MAIN_WINDOW_ACTIVE;

	guiManager->gameWin = gameWindowCreate();
	if (guiManager->gameWin == NULL) {
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	SDL_HideWindow(guiManager->gameWin->simpleWindow->window);

	guiManager->loadWin = loadWindowCreate(MAIN_WINDOW);
	if (guiManager->loadWin == NULL) {
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	SDL_HideWindow(guiManager->loadWin->simpleWindow->window);

	guiManager->settingsWin = settingsWindowCreate(MAIN_WINDOW);
	if (guiManager->settingsWin == NULL) {
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	SDL_HideWindow(guiManager->gameWin->simpleWindow->window);

	guiManager->game = gameCreate(HISTORY_SIZE,false);
	if(guiManager->game == NULL){
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	return guiManager;
}

void ChessGUIManagerDestroy(GuiManager* guiManager) {
	if (!guiManager) {
		return;
	}
	if (!guiManager->gameWin) {
		gameWindowDestroy(guiManager->gameWin);
	}
	if (!guiManager->loadWin) {
		loadWindowDestroy(guiManager->gameWin);
	}
	if (!guiManager->mainWin) {
		mainWindowDestroy(guiManager->gameWin);
	}
	if (!guiManager->settingsWin) {
		settingsWindowDestroy(guiManager->gameWin);
	}
	if (!guiManager->game) {
		gameDestroy(guiManager->game);
	}
	free(guiManager);
}

void ChessGUIManagerDraw(GuiManager* guiManager, SDL_Event* event) {
	if (!guiManager) {
		return;
	}
	switch(guiManager->activeWin){
	case MAIN_WINDOW_ACTIVE:
		mainWindowDraw(guiManager->mainWin);
		return;
	case LOAD_WINDOW_ACTIVE:
		loadWindowDraw(guiManager->loadWin);
		return;
	case SETTINGS_WINDOW_ACTIVE:
		settingsWindowDraw(guiManager->settingsWin);
		return;
	case GAME_WINDOW_ACTIVE:
		gameWindowDraw(guiManager->gameWin,guiManager->game,event,false,NULL,0);
		return;
	}
}

MANAGER_EVENT handleManagerDueToMainEvent(GuiManager* guiManager,MAIN_EVENT event) {
	if (guiManager == NULL) {
		return MANAGER_NONE;
	}
	switch(event){
	case MAIN_NEW_GAME_EVENT:
		mainWindowHide(guiManager->mainWin);
		guiManager->activeWin = SETTINGS_WINDOW_ACTIVE;
		guiManager->settingsWin->simpleWindow->backWindow = MAIN_WINDOW;
		gameWindowShow(guiManager->gameWin);
		break;
	case MAIN_LOAD_EVENT:
		mainWindowHide(guiManager->mainWin);
		guiManager->activeWin = LOAD_WINDOW_ACTIVE;
		guiManager->loadWin->simpleWindow->backWindow = MAIN_WINDOW;
		loadWindowShow(guiManager->loadWin);
		break;
	case MAIN_EXIT_EVENT:
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToGameEvent(GuiManager* guiManager,GAME_EVENT event) {
	switch(event){
	case GAME_WHITE_CHECK_EVENT:
	case GAME_BLACK_CHECK_EVENT:
		showWinnerMessage(event);
		break;

	case GAME_WHITE_CHECKMATE_EVENT:
	case GAME_BLACK_CHECKMATE_EVENT:
	case GAME_TIE_EVENT:
		showWinnerMessage(event);
		return MANAGER_QUIT;

	case GAME_SAVE_EVENT:
		if(addGameSlot(guiManager->loadWin,guiManager->game) == LOAD_FAILED) return MANAGER_QUIT;
		break;

	case GAME_LOAD_EVENT:
		gameWindowHide(guiManager->game);
		guiManager->activeWin = LOAD_WINDOW_ACTIVE;
		guiManager->loadWin->simpleWindow->backWindow = GAME_WINDOW;
		loadWindowShow(guiManager->loadWin);
		break;

	case GAME_MAIN_MENU_EVENT:
		gameWindowHide(guiManager->game);
		guiManager->activeWin = MAIN_WINDOW_ACTIVE;
		mainWindowShow(guiManager->mainWin);
		break;

	case GAME_NORMAL_EVENT:
	case GAME_NONE_EVENT:
		break;

	case GAME_EXIT_EVENT:
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToLoadEvent(GuiManager* guiManager,LOAD_EVENT event) {
	if (guiManager == NULL) {
		return MANAGER_NONE;
	}
	char path[] = SLOT1_PATH;
	bool flag = false;
	bool* loaded = &flag;
	switch(event){
	case LOAD_LOAD_EVENT:
		mainWindowHide(guiManager->mainWin);

		path[strlen(path)-5] = guiManager->loadWin->chosenSlot + '0';
		loadGame(guiManager->game,path,loaded);
		if(!loaded) return MANAGER_QUIT;

		guiManager->activeWin = GAME_WINDOW_ACTIVE;
		gameWindowShow(guiManager->gameWin);
		break;

	case LOAD_BACK_EVENT:
		loadWindowHide(guiManager->loadWin);
		if(guiManager->loadWin->simpleWindow->backWindow == MAIN_WINDOW){
			guiManager->activeWin = MAIN_WINDOW_ACTIVE;
			mainWindowShow(guiManager->mainWin);
		}
		else{
			guiManager->activeWin = GAME_WINDOW_ACTIVE;
			gameWindowShow(guiManager->gameWin);
		}
		break;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToSettingsEvent(GuiManager* guiManager,SETTINGS_EVENT event) {
	if (guiManager == NULL) {
		return MANAGER_NONE;
	}
	switch(event){
	case SETTINGS_START_EVENT:
		settingsWindowHide(guiManager->settingsWin);

		gameDestroy(guiManager->game);
		guiManager->game = gameCreate(HISTORY_SIZE,false);
		simpleSettingsSetter(guiManager->game,guiManager->settingsWin->difficultySelect,guiManager->settingsWin->gameModeSelect,
				guiManager->settingsWin->userColorSelect);

		guiManager->activeWin = GAME_WINDOW_ACTIVE;
		gameWindowShow(guiManager->gameWin);
		break;

	case SETTINGS_BACK_EVENT:
		settingsWindowHide(guiManager->settingsWin);
		guiManager->activeWin = MAIN_WINDOW_ACTIVE;
		mainWindowShow(guiManager->mainWin);
		break;
	case SETTINGS_NEXT_EVENT:
	case SETTINGS_NORMAL_EVENT:
	case SETTINGS_NONE_EVENT:
		break;

	case SETTINGS_INVALID_ARGUMENT_EVENT:
	case SETTINGS_EXIT_EVENT:
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;

	gameWindowDestroy(guiManager->gameWin);
	guiManager->gameWin = NULL;
	guiManager->activeWin = MAIN_WINDOW_ACTIVE;
	mainWindowShow(guiManager->mainWin);
	return MANAGER_NONE;
}

MANAGER_EVENT ChessGUIManagerHandleEvent(GuiManager* guiManager, SDL_Event* event) {
	if (guiManager == NULL || event == NULL) {
		return MANAGER_NONE;
	}
	switch(guiManager->activeWin){

	case MAIN_WINDOW_ACTIVE:
		MAIN_EVENT mainEvent = mainWindowHandleEvent(guiManager->mainWin, event);
		return handleManagerDueToMainEvent(guiManager, mainEvent);

	case LOAD_WINDOW_ACTIVE:
		LOAD_EVENT loadEvent = loadWindowHandleEvent(guiManager->loadWin, event,guiManager->game);
		return handleManagerDueToLoadEvent(guiManager, loadEvent);

	case SETTINGS_WINDOW_ACTIVE:
		SETTINGS_EVENT settingsEvent = settingsWindowManager(guiManager->settingsWin, event);
		return handleManagerDueToSettingsEvent(guiManager, settingsEvent);

	case GAME_WINDOW_ACTIVE:
		GAME_EVENT gameEvent = gameWindowHandleEvent(guiManager->gameWin, event);
		updateUndoButton(guiManager->game,guiManager->game);
		ChessGUIManagerDraw(guiManager,event);
		return handleManagerDueToGameEvent(guiManager, gameEvent);
	}
	return MANAGER_NONE;
}


