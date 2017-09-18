#include "ChessGUIManager.h"

#include <stdio.h>
#include <stdlib.h>

GuiManager* spManagerCreate() {
	GuiManager* res = (GuiManager*) malloc(sizeof(GuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = mainWindowCreate();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
	res->gameWin = NULL;
	res->activeWin = MAIN_WINDOW_ACTIVE;
	return res;
}

void spManagerDestroy(GuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == GAME_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->gameWin);
	}
	mainWindowDestroy(src->mainWin);
	free(src);
}

void spManagerDraw(GuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == MAIN_WINDOW_ACTIVE) {
		mainWindowDraw(src->mainWin);
	} else {
		spGameWindowDraw(src->gameWin);
	}
}

MANAGER_EVENT handleManagerDueToMainEvent(GuiManager* src,MAIN_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == MAIN_NEW_GAME_EVENT) {
		mainWindowHide(src->mainWin);
		src->gameWin = spGameWindowCreate();
		if (src->gameWin == NULL ) {
			printf("Couldn't create game window\n");
			return MANAGER_QUTT;
		}
		src->activeWin = GAME_WINDOW_ACTIVE;
	}
	if (event == MAIN_EXIT_EVENT) {
		return MANAGER_QUTT;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToGameEvent(GuiManager* src,
		SP_GAME_EVENT event) {
	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == SP_GAME_EVENT_X_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
				NULL );
	} else if (event == SP_GAME_EVENT_O_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
				NULL );
	} else if (event == SP_GAME_EVENT_TIE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
				"it's a tie", NULL );
	}
	spGameWindowDestroy(src->gameWin);
	src->gameWin = NULL;
	src->activeWin = MAIN_WINDOW_ACTIVE;
	mainWindowShow(src->mainWin);
	return MANAGER_NONE;
}

MANAGER_EVENT spManagerHandleEvent(GuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return MANAGER_NONE;
	}
	if (src->activeWin == MAIN_WINDOW_ACTIVE) {
		MAIN_EVENT mainEvent = mainWindowHandleEvent(src->mainWin, event);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else {
		SP_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
		spManagerDraw(src);
		return handleManagerDueToGameEvent(src, gameEvent);
	}
	return MANAGER_NONE;
}
