#ifndef chessTICTACTOEMAINWIN_H_
#define chessTICTACTOEMAINWIN_H_
#include "SimpleWindow.h"
#include <stdio.h>

#define MAIN_NUM_OF_BUTTONS 4

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

typedef struct{
	SimpleWindow* simpleWindow;
	Button** buttons;
}MainWin;

MainWin* mainWindowCreate();
MAIN_MESSAGE generateMainButtons(MainWin* mainWin);
MAIN_MESSAGE mainWindowDraw(MainWin* mainWin);
void mainWindowDestroy(MainWin* mainWin);
void mainWindowHide(MainWin* mainWin);
void mainWindowShow(MainWin* mainWin);
MAIN_EVENT mainWindowHandleEvent(MainWin* mainWin, SDL_Event* event);

#endif
