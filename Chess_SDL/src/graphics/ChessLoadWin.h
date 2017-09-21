/*
 * ChessLoadWin.h
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */

#ifndef GRAPHICS_CHESSLOADWIN_H_
#define GRAPHICS_CHESSLOADWIN_H_

#include <SDL.h>
#include "SimpleWindow.h"
#include <SDL_video.h>
#include <stdio.h>

#define LOAD_NUM_OF_REGULAR_BUTTONS 2
#define LOAD_NUM_OF_SLOTS 5
#define SLOT1_PATH ".//src//GameSlots//gameSlot1.xml"
#define NOT_CHOOSED_SLOT 0
#define LOAD_INDEX 1

typedef enum{
	LOAD_SUCCESS,
	LOAD_FAILED
}LOAD_MESSAGE;

typedef enum {
	LOAD_SLOT1_EVENT,
	LOAD_SLOT2_EVENT,
	LOAD_SLOT3_EVENT,
	LOAD_SLOT4_EVENT,
	LOAD_SLOT5_EVENT,
	LOAD_BACK_EVENT,
	LOAD_LOAD_EVENT,
	LOAD_EXIT_EVENT,
	LOAD_NORMAL_EVENT,
	LOAD_INVALID_ARGUMENT_EVENT,
	LOAD_NONE_EVENT
} LOAD_EVENT;

typedef struct{
	SimpleWindow* simpleWindow;
	Button** regularButtons;
	Button** slotsButtons;
	int numOfSlots;
	int chosenSlot;
	SDL_Texture* gridTexture;
}LoadWin;

LoadWin* loadWindowCreate(WINDOW_TYPE backType);
LOAD_MESSAGE generateRegularButtons(LoadWin* loadWin);
LOAD_MESSAGE generateSlotsButtons(LoadWin* loadWin);
LOAD_MESSAGE loadWindowDraw(LoadWin* loadWin);
void loadWindowDestroy(LoadWin* loadWin);
LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin,ChessGame* game, SDL_Event* event);
int scanSlotsInDirectory();
LOAD_MESSAGE addGameSlot(LoadWin* loadWin,ChessGame* game);
void switchActiveSlotButton(LoadWin* loadWin,int prevSlot,int newSlot);
void loadWindowHide(LoadWin* loadWin);
void loadWindowShow(LoadWin* loadWin);
#endif /* GRAPHICS_CHESSLOADWIN_H_ */
