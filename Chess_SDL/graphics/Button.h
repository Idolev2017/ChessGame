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
#include "textureGenerator.h"

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
	DIFFICULTY_5_BUTTON,
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
}ButtonMessage;


Button* buttonCreate(SDL_Renderer* renderer,BUTTON_TYPE type,bool isActive, bool isClickable);
ButtonMessage buttonArrayCreate(SDL_Renderer* renderer,Button** buttons,BUTTON_TYPE* types,bool* isActiveArray,bool* isClickableArray, int size);
void buttonDestroy(Button* button);
void buttonArrayDestroy(Button** buttons,int size);
Button* copyButton(Button* button);
ButtonMessage activateButton(Button* button);
ButtonMessage inactivateButton(Button* button);
ButtonMessage addButtonToRenderer(Button* button,SDL_Renderer* renderer);
Button* whichButtonWasClicked(Button** button, int size, int x, int y);
bool isClickOnButton(Button* button, int x, int y);
ButtonMessage typeToTextureAndRect(Button* button,SDL_Renderer* renderer, BUTTON_TYPE type);
void updateRectSizes(SDL_Rect* rect,int x, int y,int w, int h);
#endif /* GRAPHICS_H_ */
