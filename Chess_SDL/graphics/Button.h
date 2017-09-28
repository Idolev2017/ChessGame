/*
 * Button.h
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include "TextureGenerator.h"

typedef enum {
	//main window
	MAIN_NEW_GAME_BUTTON,
	MAIN_LOAD_BUTTON,
	MAIN_EXIT_BUTTON,

	//settings window
	SETTINGS_START_BUTTON,
	SETTINGS_NEXT_BUTTON,
	SETTINGS_BACK_BUTTON,
	GAME_MODE_TITLE_BUTTON,
	GAME_MODE_1_BUTTON,
	GAME_MODE_2_BUTTON,
	DIFFICULTY_TITLE_BUTTON,
	DIFFICULTY_1_BUTTON,
	DIFFICULTY_2_BUTTON,
	DIFFICULTY_3_BUTTON,
	DIFFICULTY_4_BUTTON,
	USER_COLOR_TITLE_BUTTON,
	COLOR_BLACK_PLAYER_BUTTON,
	COLOR_WHITE_PLAYER_BUTTON,

	//load window
	GAME_SLOT1_BUTTON,
	GAME_SLOT2_BUTTON,
	GAME_SLOT3_BUTTON,
	GAME_SLOT4_BUTTON,
	GAME_SLOT5_BUTTON,
	LOAD_LOAD_BUTTON,
	LOAD_BACK_BUTTON,

	//game window
	GAME_RESTART_BUTTON,
	GAME_SAVE_BUTTON,
	GAME_LOAD_BUTTON,
	GAME_UNDO_BUTTON,
	GAME_MAIN_MENU_BUTTON,
	GAME_EXIT_BUTTON,

} BUTTON_TYPE;
/**
 * Struct: Button
 * Description:
 * symbols a clickable (or not) image on the screen,
 * contains the differenet textures that the button can be presented with.
 * rect is the rectangle in which the button located.
 * type is the BUTTON_TYPE of the button.
 */
typedef struct{
	SDL_Rect rect;
	SDL_Texture* activeTexture;
	SDL_Texture* inactiveTexture;
	SDL_Texture* nonClickableTexture;
	bool isActive;
	bool isClickable;
	BUTTON_TYPE type;
}Button;

typedef enum{
	BUTTON_SUCCESS,
	BUTTON_FAILED
}BUTTON_MESSAGE;

/**
 * Name: buttonCreate
 * Description:
 * Creates a Button object, allocates a memory to it, initializes it and its fields to the values that are
 * in the arguments.
 * also prints error messages if these occurs.
 * returns a pointer to the new Button object that was created.
 */
Button* buttonCreate(SDL_Renderer* renderer,BUTTON_TYPE type,bool isActive, bool isClickable);
/**
 * Name: buttonArrayCreate
 * Description:
 * Creates a Button objects arrray.
 * if one of the buttons' creature failed then BUTTON_FAILED returned,
 * otherwise BUTTON_SUCCESS returned.
 */
BUTTON_MESSAGE buttonArrayCreate(SDL_Renderer* renderer,Button** buttons,BUTTON_TYPE* types,bool* isActiveArray,bool* isClickableArray, int size);
/**
 * Name: buttonDestroy
 * Description:
 * destroys the Button button and all of its fields,
 * frees button instance.
 */
void buttonDestroy(Button* button);
/**
 * Name: buttonArrayDestroy
 * Description:
 * destroys an array of buttons and all of their fields,
 * frees buttons array.
 */
void buttonArrayDestroy(Button** buttons,int size);
/**
 * Name: addButtonToRenderer
 * Description:
 * inserts the appropriate button texture to the renderer.
 * returns BUTTON_SUCCESS or BUTTON_FAILED if it secceeded or not.
 */
BUTTON_MESSAGE addButtonToRenderer(Button* button,SDL_Renderer* renderer);
/**
 * Name: whichButtonWasClicked
 * Description:
 * recieves an array of buttons and returns one of the buttons if he got clicked.
 */
Button* whichButtonWasClicked(Button** button, int size, int x, int y);
/**
 * Name: isClickOnButton
 * returns true if the mouse clicked took place in the button area,
 * otherwise returns false.
 */
bool isClickOnButton(Button* button, int x, int y);

/**
 * Name: typeToTextureAndRect
 * gets button, renderer and button type as arguments and match each
 * one of them to its texture and rectangle relative to the window.
 * return BUTTON_MESSAGE that symbols if it succeeded or not.
 */
BUTTON_MESSAGE typeToTextureAndRect(Button* button,SDL_Renderer* renderer, BUTTON_TYPE type);
/**
 * Name: createRect
 * gets x,y coordinated, width and height
 * and create rectangle with these details.
 * returns the rectangle that was created.
 */
SDL_Rect createRect(int x, int y,int w, int h);
#endif /* GRAPHICS_H_ */
