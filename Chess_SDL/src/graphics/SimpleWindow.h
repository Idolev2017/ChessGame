/*
 * simpleWindow.h
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */

#ifndef GRAPHICS_SIMPLEWINDOW_H_
#define GRAPHICS_SIMPLEWINDOW_H_
#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include "Button.h"
#include "../MainAux.h"

typedef enum{
	SIMPLE_WINDOW_SUCCESS,
	SIMPLE_WINDOW_FAILED
}SIMPLE_WINDOW_MESSAGE;

typedef enum{
	MAIN_WINDOW,
	SETTINGS_WINDOW,
	LOAD_WINDOW,
	GAME_WINDOW,
	NONE_WINDOW
}WINDOW_TYPE;

typedef struct {
	//SDL_Window* window;
	SDL_Window* window;
	SDL_Renderer* renderer;
	WINDOW_TYPE backWindow;
} SimpleWindow;

SimpleWindow* simpleWindowCreate(WINDOW_TYPE backWindow);
SIMPLE_WINDOW_MESSAGE simpleWindowDraw(SimpleWindow* simpleWin,Button** buttons,int numOfButtons);
void simpleWindowDestroy(SimpleWindow* simpleWin);
void simpleWindowHide(SimpleWindow* simpleWin);
void simpleWindowShow(SimpleWindow* simpleWin);

#endif /* GRAPHICS_SIMPLEWINDOW_H_ */
