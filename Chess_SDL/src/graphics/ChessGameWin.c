#include "ChessGameWin.h"

#include <assert.h>
#include <stdio.h>


GameWin* spGameWindowCreate() {
	GameWin* res = (GameWin*) calloc(sizeof(GameWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	res->game = spTicTacToeCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spGameWindowDestroy(res);
		return NULL ;
	}
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Tic-Tac-Toe", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			600,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/grid.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a texture for the X symbol
	loadingSurface = SDL_LoadBMP("./graphics/images/x.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->xTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->xTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the O symbol
	loadingSurface = SDL_LoadBMP("./graphics/images/o.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->oTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->oTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spGameWindowDestroy(GameWin* src) {
	if (!src) {
		return;
	}
	spTicTacToeDestroy(src->game);
	if (src->oTexture != NULL ) {
		SDL_DestroyTexture(src->oTexture);
	}
	if (src->xTexture != NULL ) {
		SDL_DestroyTexture(src->xTexture);
	}
	if (src->bgTexture != NULL ) {
		SDL_DestroyTexture(src->bgTexture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}

void spGameWindowDraw(GameWin* src) {
	if(src == NULL){
		return;
	}
	SDL_Rect rec = { .x = 0, .y = 0, .w = 600, .h = 600 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &rec);

	int i = 0, j = 0;
	for (i = 0; i < SP_N_ROWS; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			rec.x = j * 200;
			rec.y = i * 200;
			rec.h = 200;
			rec.w = 200;
			if (src->game->board[i][j] == SP_PLAYER_1_SYMBOL) {
				SDL_RenderCopy(src->renderer, src->xTexture, NULL, &rec);
			} else if (src->game->board[i][j] == SP_PLAYER_2_SYMBOL) {
				SDL_RenderCopy(src->renderer, src->oTexture, NULL, &rec);
			}
		}
	}
	SDL_RenderPresent(src->renderer);
}

SP_GAME_EVENT spGameWindowHandleEvent(GameWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		spTicTacToeSetMove(src->game, event->button.y / 200,
				event->button.x / 200);
		char winner = spTicTacToeCheckWinner(src->game);
		if (winner == SP_PLAYER_1_SYMBOL) {
			return SP_GAME_EVENT_X_WON;
		} else if (winner == SP_PLAYER_2_SYMBOL) {
			return SP_GAME_EVENT_O_WON;
		} else if (spTicTacToeIsGameOver(src->game)) {
			return SP_GAME_EVENT_TIE;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_EVENT_QUIT;
		}
		break;
	default:
		return SP_GAME_EVENT_NONE;
	}
	return SP_GAME_EVENT_NONE;
}
