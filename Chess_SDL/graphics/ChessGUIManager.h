#ifndef CHESSGUIMANAGER_H_
#define CHESSGUIMANAGER_H_
#include "ChessGameWin.h"
#include "ChessMainWin.h"
#include "ChessLoadWin.h"
#include "ChessSettingsWin.h"

#include <stdio.h>
#include <stdlib.h>

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
/**
 * Struct: GuiManager
 * Description:
 * symbols an object that manages the Chess game due to the
 * events that user makes.
 * it holds 4 windows: main menu, load, settings and game.
 * game is the ChessGame object that runs the whole thing.
 * activeWin is the current window that the user uses.
 */
typedef struct {
	GameWin* gameWin;
	MainWin* mainWin;
	LoadWin* loadWin;
	SettingsWin* settingsWin;
	ChessGame* game;
	ACTIVE_WINDOW activeWin;
} GuiManager;
/**
 * Name: ChessGUIManagerCreate
 * Description:
 * Creates a GuiManager object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * returns a pointer to the new GuiManager object that was created.
 */
GuiManager* ChessGUIManagerCreate();
/**
 * Name: ChessGUIManagerDestroy
 * Description:
 * destroys the GUIManager button and all of its fields,
 * frees GUIManager instance.
 */
void ChessGUIManagerDestroy(GuiManager* guiManager);
/**
 * Name: ChessGUIManagerDraw
 * Description:
 * The function handles the transition between
 * the different windows according to the user's event.
 */
MANAGER_EVENT ChessGUIManagerDraw(GuiManager* guiManager, SDL_Event* event);
/**
 * Name: ChessGUIManagerHandleEvent
 * Description:
 * The function gets the user's event and calls the
 * dedicated function that suppose to handle events that
 * occurred in a specific window.
 */
MANAGER_EVENT ChessGUIManagerHandleEvent(GuiManager* guiManager, SDL_Event* event);
/**
 * Name: handleManagerDueToMainEvent
 * Description:
 * The function gets the user's event in the Main Menu window
 * and handles it by calling other dedicated functions.
 * returns an appropriate MANAGER_EVENT message.
 */
MANAGER_EVENT handleManagerDueToMainEvent(GuiManager* guiManager,MAIN_EVENT event);
/**
 * Name: handleManagerDueToGameEvent
 * Description:
 * The function gets the user's event in the Game window
 * and handles it by calling other dedicated functions.
 * returns an appropriate MANAGER_EVENT message.
 */
MANAGER_EVENT handleManagerDueToGameEvent(GuiManager* guiManager,GAME_EVENT event);
/**
 * Name: handleManagerDueToLoadEvent
 * Description:
 * The function gets the user's event in the Load window
 * and handles it by calling other dedicated functions.
 * returns an appropriate MANAGER_EVENT message.
 */
MANAGER_EVENT handleManagerDueToLoadEvent(GuiManager* guiManager,LOAD_EVENT event);
/**
 * Name: handleManagerDueToSettingsEvent
 * Description:
 * The function gets the user's event in the Settings window
 * and handles it by calling other dedicated functions.
 * returns an appropriate MANAGER_EVENT message.
 */
MANAGER_EVENT handleManagerDueToSettingsEvent(GuiManager* guiManager,SETTINGS_EVENT event);



#endif
