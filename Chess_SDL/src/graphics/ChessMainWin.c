#include "ChessMainWin.h"


MainWin* mainWindowCreate() {
	MainWin* mainWin = NULL;
	mainWin = (MainWin*) malloc(sizeof(MainWin));
	if (mainWin == NULL ) {
		printMallocError();
		return NULL;
	}
	mainWin->simpleWindow = NULL;
	mainWin->buttons = NULL;
	mainWin->gridTexture = NULL;
	mainWin->simpleWindow = simpleWindowCreate(NONE_WINDOW);
	// Check that the window was successfully created
	if (mainWin->simpleWindow == NULL) {
		mainWindowDestroy(mainWin);
		return NULL;
	}
	if(generateMainButtons(mainWin) == MAIN_FAILED){
		mainWindowDestroy(mainWin);
		return NULL;
	}

	SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/gameMain.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		mainWindowDestroy(mainWin);
		return NULL;
	}

	mainWin->gridTexture = SDL_CreateTextureFromSurface(mainWin->simpleWindow->renderer,loadingSurface);
	if (mainWin->gridTexture == NULL) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		mainWindowDestroy(mainWin);
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	return mainWin;
}

MAIN_MESSAGE generateMainButtons(MainWin* mainWin){
	mainWin->buttons = (Button**) malloc(sizeof(Button*) * MAIN_NUM_OF_BUTTONS);
	if (mainWin->buttons == NULL) {
		printMallocError();
		return MAIN_FAILED;
	}
	BUTTON_TYPE mainRegularTypes[MAIN_NUM_OF_BUTTONS] = {
			MAIN_NEW_GAME_BUTTON,
			MAIN_LOAD_BUTTON,
			MAIN_EXIT_BUTTON };
	bool mainActiveRegularButtons[MAIN_NUM_OF_BUTTONS] = {true,true,true};
	bool mainClickableRegularButtons[MAIN_NUM_OF_BUTTONS] = {true, true,true};
	if (buttonArrayCreate(mainWin->simpleWindow->renderer,mainWin->buttons, mainRegularTypes,mainActiveRegularButtons, mainClickableRegularButtons,MAIN_NUM_OF_BUTTONS) == BUTTON_FAILED) {
		free(mainWin->buttons);
		mainWin->buttons = NULL;
		return MAIN_FAILED;
	}
	return MAIN_SUCCESS;
}

MAIN_MESSAGE mainWindowDraw(MainWin* mainWin){
	SDL_Rect rec = { .x = 0, .y = 0, .w = WIDTH_SIZE, .h = HEIGHT_SIZE };
	SDL_SetRenderDrawColor(mainWin->simpleWindow->renderer, 255, 255, 255, 255); //Background is white.
	SDL_RenderClear(mainWin->simpleWindow->renderer);
	SDL_RenderCopy(mainWin->simpleWindow->renderer, mainWin->gridTexture, NULL, &rec);
	if(simpleWindowAddingButtons(mainWin->simpleWindow,mainWin->buttons,MAIN_NUM_OF_BUTTONS) == SIMPLE_WINDOW_FAILED) return MAIN_FAILED;
	SDL_RenderPresent(mainWin->simpleWindow->renderer);
	return MAIN_SUCCESS;
}

void mainWindowDestroy(MainWin* mainWin) {
	if(!mainWin) return;
	simpleWindowDestroy(mainWin->simpleWindow);
	buttonArrayDestroy(mainWin->buttons,MAIN_NUM_OF_BUTTONS);
	free(mainWin);
}

MAIN_EVENT mainWindowHandleEvent(MainWin* mainWin, SDL_Event* event) {
	if (!event) return MAIN_EXIT_EVENT;
	if(event->button.button != SDL_BUTTON_LEFT) return MAIN_NONE_EVENT;
	Button* button;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		button = whichButtonWasClicked(mainWin->buttons,MAIN_NUM_OF_BUTTONS,event->button.x, event->button.y);
		if(button == NULL) return MAIN_NONE_EVENT;

		switch(button->type){
		case MAIN_NEW_GAME_BUTTON:
			return MAIN_NEW_GAME_EVENT;
		case MAIN_LOAD_BUTTON:
			return MAIN_LOAD_EVENT;
		case MAIN_EXIT_BUTTON:
			return MAIN_EXIT_EVENT;
		default:
			break;
		}
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
