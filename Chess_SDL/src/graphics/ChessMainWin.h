#ifndef chessTICTACTOEMAINWIN_H_
#define chessTICTACTOEMAINWIN_H_
#include <SDL.h>
#include "SimpleWindow.h"

#define MAIN_NUM_OF_BUTTONS 4
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
	int num_of_buttons;
}MainWin;

MainWin* mainWindowCreate();
void mainWindowDraw(MainWin* mainWin);
void mainWindowDestroy(MainWin* mainWin);
void mainWindowHide(MainWin* mainWin);
void mainWindowShow(MainWin* mainWin);
MAIN_EVENT mainWindowHandleEvent(MainWin* mainWin, SDL_Event* event);

#endif
