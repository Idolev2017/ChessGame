/*
 * simpleWindow.c
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */
#include "SimpleWindow.h"

SimpleWindow* simpleWindowCreate(WINDOW_TYPE backWindow) {
	SimpleWindow* simpleWin = NULL;
	simpleWin = (SimpleWindow*) malloc(sizeof(SimpleWindow));
	if (simpleWin == NULL ) {
		printMallocError();
		return NULL ;
	}
	simpleWin->window = NULL;
	simpleWin->renderer = NULL;
	// Create an application window with the following settings:
	simpleWin->window = SDL_CreateWindow("CHESS", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			WIDTH_SIZE,                               // width, in pixels
			HEIGHT_SIZE,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
	);
	// Check that the window was successfully created
	if (simpleWin->window == NULL) {
		simpleWindowDestroy(simpleWin);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	simpleWin->renderer = SDL_CreateRenderer(simpleWin->window, -1,SDL_RENDERER_ACCELERATED);
	if (simpleWin->renderer == NULL) {
		simpleWindowDestroy(simpleWin);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	simpleWin->backWindow = backWindow;
	return simpleWin;
}
SIMPLE_WINDOW_MESSAGE simpleWindowAddingButtons(SimpleWindow* simpleWin,Button** buttons,int numOfButtons){
	if(!simpleWin || !buttons) return SIMPLE_WINDOW_FAILED;
	for(int i = 0; i < numOfButtons; ++i){
		if(addButtonToRenderer(buttons[i], simpleWin->renderer) == BUTTON_FAILED)  return SIMPLE_WINDOW_FAILED;
	}
	return SIMPLE_WINDOW_SUCCESS;
}
void simpleWindowDestroy(SimpleWindow* simpleWin){
	if(simpleWin == NULL) return;
	if (simpleWin->renderer != NULL) {
		SDL_DestroyRenderer(simpleWin->renderer);
	}
	if (simpleWin->window != NULL) {
		SDL_DestroyWindow(simpleWin->window);
	}
	free(simpleWin);
}
void simpleWindowHide(SimpleWindow* simpleWin) {
	SDL_HideWindow(simpleWin->window);
}
void simpleWindowShow(SimpleWindow* simpleWin) {
	SDL_ShowWindow(simpleWin->window);
}

