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
#include "Button.h"
#include "../game/MainAux.h"
#define WIDTH_SIZE 800
#define HEIGHT_SIZE 600
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
/**
 * Name: simpleWindowCreate
 * Description:
 * Creates a SimpleWindow object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * returns a pointer to the new LoadWin object that was created.
 */
SimpleWindow* simpleWindowCreate(WINDOW_TYPE backWindow);
/**
 * Name: simpleWindowAddingButtons
 * Description:
 * adds the buttons from the givan Button array to
 * the renderer of the given simpleWindow.
 */
SIMPLE_WINDOW_MESSAGE simpleWindowAddingButtons(SimpleWindow* simpleWin,Button** buttons,int numOfButtons);
/**
 * Name: simpleWindowDestroy
 * Description:
 * Destroys the window and his renderer.
 */
void simpleWindowDestroy(SimpleWindow* simpleWin);
/**
 * Name: simpleWindowHide
 * Description:
 * Hides the matching window from the screen.
 */
void simpleWindowHide(SimpleWindow* simpleWin);
/**
 * Name: simpleWindowShow
 * Description:
 * Initializes the matching window and present it on the screen.
 */
void simpleWindowShow(SimpleWindow* simpleWin);

#endif /* GRAPHICS_SIMPLEWINDOW_H_ */
