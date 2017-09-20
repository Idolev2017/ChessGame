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

GuiManager* ChessGUIManagerCreate();
void ChessGUIManagerDestroy(GuiManager* guiManager);
void ChessGUIManagerDraw(GuiManager* guiManager, SDL_Event* event);

MANAGER_EVENT ChessGUIManagerHandleEvent(GuiManager* guiManager, SDL_Event* event);
MANAGER_EVENT handleManagerDueToMainEvent(GuiManager* guiManager,MAIN_EVENT event);
MANAGER_EVENT handleManagerDueToGameEvent(GuiManager* guiManager,GAME_EVENT event);
MANAGER_EVENT handleManagerDueToLoadEvent(GuiManager* guiManager,LOAD_EVENT event);
MANAGER_EVENT handleManagerDueToSettingsEvent(GuiManager* guiManager,SETTINGS_EVENT event);



#endif
