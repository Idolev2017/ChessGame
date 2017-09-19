#ifndef SPTICTACTOEGAMEWIN_H_
#define SPTICTACTOEGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "SimpleWindow.h"
#include "../SPTicTacToe.h"
#include "..\MainAux.h"


#define GAME_NUM_OF_PANEL_EVENTS 6

typedef enum{
	GAME_WINDOW_SUCCESS,
	GAME_WINDOW_FAILED
}GAME_WINDOW_MESSAGE;

typedef enum {
	GAME_WHITH_CHECK_EVENT,
	GAME_BLACK_CHECK_EVENT,
	GAME_WHITH_CHECKMATE_EVENT,
	GAME_BLACK_CHECKMATE_EVENT,
	GAME_TIE_EVENT,
	GAME_RESTART_EVENT,
	GAME_SAVE_EVENT,
	GAME_LOAD_EVENT,
	GAME_UNDO_EVENT,
	GAME_MAIN_MENU_EVENT,
	GAME_EXIT_EVENT,
} GAME_EVENT;


typedef struct{
	SimpleWindow* simpleWindow;
	Button** panelButtons;
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
}GameWin;


GameWin* GameWindowCreate();
void GameWindowDraw(GameWin*);
void GameWindowDestroy(GameWin*);
GAME_EVENT GameWindowHandleEvent(GameWin* src, SDL_Event* event);


#endif
