#ifndef chessTICTACTOEMAINWIN_H_
#define chessTICTACTOEMAINWIN_H_
#include "SimpleWindow.h"
#include <stdio.h>

#define MAIN_NUM_OF_BUTTONS 3

typedef enum{
	MAIN_SUCCESS,
	MAIN_FAILED
}MAIN_MESSAGE;

typedef enum {
	MAIN_EXIT_EVENT,
	MAIN_NEW_GAME_EVENT,
	MAIN_LOAD_EVENT,
	MAIN_INVALID_ARGUMENT_EVENT,
	MAIN_NONE_EVENT
} MAIN_EVENT;
/**
 * Struct: MainWin
 * Description:
 * symbols the Main window.
 * contains a simple Window object, array of buttons,
 * the texture of the BG.
 */
typedef struct{
	SimpleWindow* simpleWindow;
	Button** buttons;
	SDL_Texture* gridTexture;
}MainWin;
/**
 * Name: mainWindowCreate
 * Description:
 * Creates a MainWin object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * creates the instance of the matching simpleWindow.
 * returns a pointer to the new MainWin object that was created.
 */
MainWin* mainWindowCreate();
/**
 * Name: generateMainButtons
 * Description:
 * Creates a buttons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate MAIN_MESSAGE message.
 */
MAIN_MESSAGE generateMainButtons(MainWin* mainWin);
/**
 * Name: mainWindowDraw
 * Description:
 * Draws all the background and all of the buttons that suppose
 * be presented in main window.
 * returns an appropriate MAIN_MESSAGE message if it succeeded or not.
 */
MAIN_MESSAGE mainWindowDraw(MainWin* mainWin);
/**
 * Name: mainWindowDestroy
 * Description:
 * Destroys all the background and all of the buttons that suppose
 * be presented in main window.
 * frees mainWin memory.
 */
void mainWindowDestroy(MainWin* mainWin);
/**
 * Name: mainWindowHide
 * Description:
 * Hides the main window from the screen.
 */
void mainWindowHide(MainWin* mainWin);
/**
 * Name: mainWindowShow
 * Description:
 * Initializes the main window and present it on the screen.
 */
void mainWindowShow(MainWin* mainWin);
/**
 * Name: mainWindowHandleEvent
 * Description:
 * Handles the different events that occurred in the window by the user,
 * reacts accordingly.
 * returns an appropriate MAIN_EVENT message if it succeeded or not.
 */
MAIN_EVENT mainWindowHandleEvent(MainWin* mainWin, SDL_Event* event);

#endif
