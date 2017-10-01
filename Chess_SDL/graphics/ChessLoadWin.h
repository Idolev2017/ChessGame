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
#define SLOT1_PATH "gameSlots/gameSlot1.xml"
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
/**
 * Struct: LoadWin
 * Description:
 * symbols the Load window.
 * contains a simple Window object, two arrays of buttons,
 * the number of available slots to load,
 * the slot that has been chosen and the texture of the BG.
 */
typedef struct{
	SimpleWindow* simpleWindow;
	Button** regularButtons;
	Button** slotsButtons;
	int numOfSlots;
	int chosenSlot;
	SDL_Texture* gridTexture;
}LoadWin;
/**
 * Name: loadWindowCreate
 * Description:
 * Creates a LoadWin object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * creates the instance of the matching simpleWindow.
 * returns a pointer to the new LoadWin object that was created.
 */
LoadWin* loadWindowCreate(WINDOW_TYPE backType);
/**
 * Name: InitializeLoadWindow
 * Description:
 * initializes all loadWindow buttons to not active and not clickable.
 */
void InitializeLoadWindow(LoadWin* loadWin);
/**
 * Name: generateRegularButtons
 * Description:
 * Creates a regularButtons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate LOAD_MESSAGE message.
 */
LOAD_MESSAGE generateRegularButtons(LoadWin* loadWin);
/**
 * Name: generateSlotsButtons
 * Description:
 * Creates a SlotsButtons array, allocates a memory to it, initializes it and its fields to
 * the current values.
 * also prints memory error messages if these occurs.
 * returns an appropriate LOAD_MESSAGE message.
 */
LOAD_MESSAGE generateSlotsButtons(LoadWin* loadWin);
/**
 * Name: loadWindowDraw
 * Description:
 * Draws all the background and all of the buttons that suppose
 * be presented in load window.
 * returns an appropriate LOAD_MESSAGE message if it succeeded or not.
 */
LOAD_MESSAGE loadWindowDraw(LoadWin* loadWin);
/**
 * Name: loadWindowDestroy
 * Description:
 * Destroys all the background and all of the buttons that suppose
 * be presented in load window.
 * frees loadWin memory.
 */
void loadWindowDestroy(LoadWin* loadWin);
/**
 * Name: loadWindowHandleEvent
 * Description:
 * Handles the different events that occurred in the window by the user,
 * reacts accordingly.
 * returns an appropriate LOAD_EVENT message if it succeeded or not.
 */
LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin, SDL_Event* event);
/**
 * Name: scanSlotsInDirectory
 * Description:
 * Scans the saved games directory which is called gameSlots,
 * and returns the number of found files that have already been saved
 * and appeared in the directory.
 */
int scanSlotsInDirectory();
/**
 * Name: addGameSlot
 * Description:
 * A function that been called after the user clicked on
 * save in the game window.
 * returns an appropriate LOAD_MESSAGE message if it succeeded or not.
 */
LOAD_MESSAGE addGameSlot(LoadWin* loadWin,ChessGame* game);
/**
 * Name: switchActiveSlotButton
 * Description:
 * Changes the button that was the last one that has been selected
 * by the user to be active and one before it to be inactive.
 */
void switchActiveSlotButton(LoadWin* loadWin,int prevSlot,int newSlot);
/**
 * Name: loadWindowHide
 * Description:
 * Hides the load window from the screen.
 */
void loadWindowHide(LoadWin* loadWin);
/**
 * Name: loadWindowShow
 * Description:
 * Initializes the load window and present it on the screen.
 */
void loadWindowShow(LoadWin* loadWin);
#endif /* GRAPHICS_CHESSLOADWIN_H_ */
