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
			800,                               // width, in pixels
			600,                               // height, in pixels
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
SIMPLE_WINDOW_MESSAGE simpleWindowDraw(SimpleWindow* simpleWin,Button** buttons,int numOfButtons){
	SDL_SetRenderDrawColor(simpleWin->renderer, 255, 255, 255, 255);
	SDL_RenderClear(simpleWin->renderer);
	for(int i = 0; i < numOfButtons; ++i){
		if(drawButton(buttons[i], simpleWin->renderer) == BUTTON_FAILED) return SIMPLE_WINDOW_FAILED;
	}
	SDL_RenderPresent(simpleWin->renderer);
	return SIMPLE_WINDOW_SUCCESS;
}
void simpleWindowDestroy(SimpleWindow* simpleWin){
	if(simpleWin == NULL) return;
	if (simpleWin->renderer != NULL ) {
		SDL_DestroyRenderer(simpleWin->renderer);
	}
	if (simpleWin->window != NULL ) {
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

