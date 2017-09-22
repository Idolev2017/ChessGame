#ifndef SPTICTACTOEGAMEWIN_H_
#define SPTICTACTOEGAMEWIN_H_
#include "SimpleWindow.h"
#include "../SPTicTacToe.h"
#include "../MainAux.h"
#include <math.h>

#define PANEL_WIDTH 200
#define GAME_BOARD_SIZE 600
#define GAME_NUM_OF_PANEL_BUTTONS 6
#define UNDO_IN_ARRAY 3
#define BOARD_LINE_SIZE 8
#define REC_SIZE (GAME_BOARD_SIZE / BOARD_LINE_SIZE)
#define NOT_CHOOSED -10

typedef enum{
	GAME_WINDOW_SUCCESS,
	GAME_WINDOW_FAILED
}GAME_WINDOW_MESSAGE;

typedef enum {
	GAME_WHITE_CHECK_EVENT,
	GAME_BLACK_CHECK_EVENT,
	GAME_WHITE_CHECKMATE_EVENT,
	GAME_BLACK_CHECKMATE_EVENT,
	GAME_TIE_EVENT,
	GAME_SAVE_EVENT,
	GAME_LOAD_EVENT,
	GAME_MAIN_MENU_EVENT,
	GAME_EXIT_EVENT,
	GAME_NONE_EVENT,
	GAME_NORMAL_EVENT,
	GAME_EVENT_INVALID_ARGUMENT
} GAME_EVENT;

typedef struct{
	SDL_Texture* grid_texture;
	SDL_Texture* p_white_texture;
	SDL_Texture* p_black_texture;
	SDL_Texture* b_white_texture;
	SDL_Texture* b_black_texture;
	SDL_Texture* q_white_texture;
	SDL_Texture* q_black_texture;
	SDL_Texture* k_white_texture;
	SDL_Texture* k_black_texture;
	SDL_Texture* n_white_texture;
	SDL_Texture* n_black_texture;
	SDL_Texture* r_white_texture;
	SDL_Texture* r_black_texture;
}GameTextures;

typedef struct{
	SimpleWindow* simpleWindow;
	Button** panelButtons;
	GameTextures* gameTextures;
	Step* steps;
	int numOfSteps;
	Location  chosenLoc;
	Location getAllMovesLoc;
	bool savedLastMove;

}GameWin;


GameWin* gameWindowCreate();
GAME_WINDOW_MESSAGE generatePanelButtons(GameWin* gameWin,bool canUndo);
void updateUndoButton(GameWin* gameWin,ChessGame* game);
GAME_WINDOW_MESSAGE gameWindowDraw(GameWin* gameWin,ChessGame* game,SDL_Event* event);
void drawGetAllMoves(GameWin* gameWin);
GAME_WINDOW_MESSAGE drawPiece(GameWin* gameWin,SDL_Rect* rec, char piece);
void fillRecColor(GameWin* gameWin,SDL_Rect* rec,MoveClass moveClass);
void gameWindowDestroy(GameWin*);
GAME_EVENT gameWindowHandleEvent(GameWin* src,ChessGame* game, SDL_Event* event);
GAME_EVENT gameWindowPanelHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event);
GAME_EVENT gameWindowBoardHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event);
void destroyStepsArray(GameWin* gameWin);
Location mouseLocToBoardLoc(int x, int y);
SDL_Rect boardLocToRect(Location loc);
bool isClickedOnBoard(int x, int y);
bool confirmExitFromGame();
GAME_EVENT gameUndoGui(ChessGame* game);
void gameRestartGui(int prevDifficulty, int prevGameMode, int prevUserColor, ChessGame* game);
void gameWindowHide(GameWin* gameWin);
void gameWindowShow(GameWin* gameWin);
GAME_EVENT gameCheckingWinnerGui(ChessGame* game);
void showWinnerMessage(GAME_EVENT event);

GameTextures* gameTexturesCreate(GameWin* gameWin);
GAME_WINDOW_MESSAGE generateGameTexture(GameWin* gameWin);
void gameTexturesDestroy(GameTextures* gameTextures);
#endif
