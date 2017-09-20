#ifndef SPTICTACTOEGUIMANAGER_H_
#define SPTICTACTOEGUIMANAGER_H_
#include "ChessGameWin.h"
#include "ChessMainWin.h"
#include "ChessLoadWin.h"
#include "ChessSettingsWin.h"

typedef enum{
	MAIN_WINDOW_ACTIVE,
	GAME_WINDOW_ACTIVE,
	LOAD_WINDOW_ACTIVE,
	SETTINGS_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
	MANAGER_QUIT,
	MANAGER_NONE,
}MANAGER_EVENT;

typedef struct {
	GameWin* gameWin;
	MainWin* mainWin;
	LoadWin* loadWin;
	SettingsWin* settingsWin;
	ChessGame* game;
	ACTIVE_WINDOW activeWin;
} GuiManager;

GuiManager* spManagerCreate();

void spManagerDestroy(GuiManager* src);

void spManagerDraw(GuiManager* src);

LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin,ChessGame* game,int numOfSlots, SDL_Event* event);



#endif
