#include "ChessMainWin.h"
#include <SDL_video.h>
#include <stdio.h>

MainWin* mainWindowCreate() {
	MainWin* mainWin = NULL;
	mainWin = (MainWin*) malloc(sizeof(MainWin));
	if (mainWin == NULL ) {
		printMallocError();
		return NULL;
	}
	mainWin->simpleWindow = simpleWindowCreate(NONE_WINDOW);
	// Check that the window was successfully created
	if (mainWin->simpleWindow == NULL) {
		free(mainWin);
		return NULL ;
	}
	mainWin->num_of_buttons = MAIN_NUM_OF_BUTTONS;
	mainWin->buttons = (Button**) malloc(sizeof(Button*) * mainWin->num_of_buttons);
	if (mainWin->buttons == NULL ) {
		printMallocError();
		simpleWindowDestroy(mainWin->simpleWindow);
		free(mainWin);
		return NULL;
	}
	BUTTON_TYPE mainTypes[MAIN_NUM_OF_BUTTONS] = {MAIN_LOAD_BUTTON,MAIN_NEW_GAME_BUTTON,MAIN_EXIT_BUTTON,MAIN_TITLE_BUTTON};
	bool mainActiveButtons[MAIN_NUM_OF_BUTTONS] = {true,true,true,true};
	bool mainClickableButtons[MAIN_NUM_OF_BUTTONS] = {true,true,true,false};
	if(buttonArrayCreate(mainWin->buttons,mainTypes,mainActiveButtons,mainClickableButtons,MAIN_NUM_OF_BUTTONS) == BUTTON_FAILED){
		simpleWindowDestroy(mainWin->simpleWindow);
		free(mainWin->buttons);
		free(mainWin);
	}
	return mainWin;
}

void mainWindowDraw(MainWin* mainWin){
	simpleWindowDraw(mainWin->simpleWindow,mainWin->buttons,mainWin->num_of_buttons);
}

void mainWindowDestroy(MainWin* mainWin) {
	if (mainWin == NULL) return;

	simpleWindowDestroy(mainWin->simpleWindow);
	buttonArrayDestroy(mainWin->buttons,mainWin->num_of_buttons);
}

MAIN_EVENT mainWindowHandleEvent(MainWin* mainWin, SDL_Event* event) {
	if (!event) {
		return MAIN_INVALID_ARGUMENT_EVENT;
	}
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		button = whichButtonWasClicked(mainWin->buttons,mainWin->num_of_buttons,event->button.x, event->button.y);
		if(button == NULL) return MAIN_NONE_EVENT;
		if (button->type == MAIN_NEW_GAME_BUTTON) {
			return MAIN_NEW_GAME_EVENT;
		}
		else if (button->type == MAIN_LOAD_BUTTON) {
			return MAIN_LOAD_EVENT;
		}
		else if (button->type == MAIN_EXIT_BUTTON) {
			return MAIN_EXIT_EVENT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_EXIT_EVENT;
		}
		break;
	default:
		return MAIN_NONE_EVENT;
	}
	return MAIN_NONE_EVENT;
}

void mainWindowHide(MainWin* mainWin) {
	simpleWindowHide(mainWin->simpleWindow);
}

void mainWindowShow(MainWin* mainWin) {
	simpleWindowShow(mainWin->simpleWindow);
}
