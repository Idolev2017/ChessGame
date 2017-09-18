#ifndef SPTICTACTOEGAMEWIN_H_
#define SPTICTACTOEGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "Button.h"
#include "../SPTicTacToe.h"
#include "..\MainAux.h"

typedef enum {
	SP_GAME_EVENT_X_WON,
	SP_GAME_EVENT_O_WON,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_QUIT,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_NONE
} SP_GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* xTexture;
	SDL_Texture* oTexture;
	SPTicTacToe* game;
}GameWin;

GameWin* spGameWindowCreate();
void spGameWindowDraw(GameWin*);
void spGameWindowDestroy(GameWin*);
SP_GAME_EVENT spGameWindowHandleEvent(GameWin* src, SDL_Event* event);


#endif
