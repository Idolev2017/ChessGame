#include "ChessGUIManager.h"

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
	gameWindowHide(guiManager->gameWin);

	guiManager->loadWin = loadWindowCreate(MAIN_WINDOW);
	if (guiManager->loadWin == NULL) {
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	loadWindowHide(guiManager->loadWin);

	guiManager->settingsWin = settingsWindowCreate(MAIN_WINDOW);
	if (guiManager->settingsWin == NULL) {
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	settingsWindowHide(guiManager->settingsWin);

	guiManager->game = gameCreate(HISTORY_SIZE,false);
	if(guiManager->game == NULL){
		ChessGUIManagerDestroy(guiManager);
		return NULL;
	}
	return guiManager;
}

void ChessGUIManagerDestroy(GuiManager* guiManager) {
	if (guiManager == NULL) {
		return;
	}
	if (guiManager->gameWin != NULL) {
		gameWindowDestroy(guiManager->gameWin);
	}
	if (guiManager->loadWin != NULL) {
		loadWindowDestroy(guiManager->loadWin);
	}
	if (guiManager->mainWin != NULL) {
		mainWindowDestroy(guiManager->mainWin);
	}
	if (guiManager->settingsWin != NULL) {
		settingsWindowDestroy(guiManager->settingsWin);
	}
	if (guiManager->game != NULL) {
		gameDestroy(guiManager->game);
	}
	free(guiManager);
}

MANAGER_EVENT ChessGUIManagerDraw(GuiManager* guiManager, SDL_Event* event) {
	if (!guiManager) {
		return MANAGER_QUIT;
	}
	switch(guiManager->activeWin){
	case MAIN_WINDOW_ACTIVE:
		if(mainWindowDraw(guiManager->mainWin) == MAIN_FAILED) return MANAGER_QUIT;
		break;
	case LOAD_WINDOW_ACTIVE:
		if(loadWindowDraw(guiManager->loadWin) == LOAD_FAILED) return MANAGER_QUIT;
		break;
	case SETTINGS_WINDOW_ACTIVE:
		if(settingsWindowDraw(guiManager->settingsWin) == SETTINGS_FAILED) return MANAGER_QUIT;
		break;
	case GAME_WINDOW_ACTIVE:
		if(gameWindowDraw(guiManager->gameWin,guiManager->game,event) == GAME_WINDOW_FAILED) return MANAGER_QUIT;
		break;
	}
	return MANAGER_NONE;
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
		settingsWindowShow(guiManager->settingsWin);
		break;
	case MAIN_LOAD_EVENT:
		mainWindowHide(guiManager->mainWin);
		guiManager->activeWin = LOAD_WINDOW_ACTIVE;
		guiManager->loadWin->simpleWindow->backWindow = MAIN_WINDOW;
		loadWindowShow(guiManager->loadWin);
		break;
	case MAIN_EXIT_EVENT:
		return MANAGER_QUIT;
	default:
		break;
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
		gameWindowHide(guiManager->gameWin);
		guiManager->activeWin = MAIN_WINDOW_ACTIVE;
		mainWindowShow(guiManager->mainWin);
		break;

	case GAME_SAVE_EVENT:
		if(addGameSlot(guiManager->loadWin,guiManager->game) == LOAD_FAILED) return MANAGER_NONE;
		break;

	case GAME_LOAD_EVENT:
		gameWindowHide(guiManager->gameWin);
		guiManager->activeWin = LOAD_WINDOW_ACTIVE;
		guiManager->loadWin->simpleWindow->backWindow = GAME_WINDOW;
		loadWindowShow(guiManager->loadWin);
		break;

	case GAME_MAIN_MENU_EVENT:
		gameWindowHide(guiManager->gameWin);
		guiManager->activeWin = MAIN_WINDOW_ACTIVE;
		mainWindowShow(guiManager->mainWin);
		break;
	case GAME_UNDO_EVENT:
		showWinnerMessage(gameCheckingWinnerGui(guiManager->game));
		break;
	case GAME_NONE_EVENT:
		break;

	case GAME_EXIT_EVENT:
		return MANAGER_QUIT;
	default:
		break;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToLoadEvent(GuiManager* guiManager,LOAD_EVENT event) {
	if (guiManager == NULL) {
		return MANAGER_QUIT;
	}
	char path[] = SLOT1_PATH;
	switch(event){
	case LOAD_LOAD_EVENT:
		loadWindowHide(guiManager->loadWin);
		path[strlen(path)-5] = guiManager->loadWin->chosenSlot + '0';
		if(!loadGame(guiManager->game,path)){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"LOAD","load didn't succeed", NULL);
			return MANAGER_QUIT;
		}
		guiManager->activeWin = GAME_WINDOW_ACTIVE;
		gameWindowShow(guiManager->gameWin);
		//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"LOAD","load succeeded", NULL);
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
	default:
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

	return MANAGER_NONE;
}

MANAGER_EVENT ChessGUIManagerHandleEvent(GuiManager* guiManager, SDL_Event* event) {
	if (guiManager == NULL || event == NULL) {
		return MANAGER_NONE;
	}
	MAIN_EVENT mainEvent;
	LOAD_EVENT loadEvent;
	SETTINGS_EVENT settingsEvent;
	GAME_EVENT gameEvent;
	switch(guiManager->activeWin){

	case MAIN_WINDOW_ACTIVE:
		mainEvent = mainWindowHandleEvent(guiManager->mainWin, event);
		return handleManagerDueToMainEvent(guiManager, mainEvent);

	case LOAD_WINDOW_ACTIVE:
		loadEvent = loadWindowHandleEvent(guiManager->loadWin,event);
		return handleManagerDueToLoadEvent(guiManager, loadEvent);

	case SETTINGS_WINDOW_ACTIVE:
		settingsEvent = settingsWindowManager(guiManager->settingsWin,guiManager->game, event);
		return handleManagerDueToSettingsEvent(guiManager, settingsEvent);

	case GAME_WINDOW_ACTIVE:
		gameEvent = gameWindowHandleEvent(guiManager->gameWin,guiManager->game, event);
		updateUndoButton(guiManager->gameWin,guiManager->game);
		if(!(event->type == SDL_MOUSEMOTION && guiManager->gameWin->chosenLoc.row == NOT_CHOOSED)) ChessGUIManagerDraw(guiManager,event);
		return handleManagerDueToGameEvent(guiManager, gameEvent);
	}
	return MANAGER_NONE;
}


