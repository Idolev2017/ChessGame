#include "ChessGameWin.h"

#include <assert.h>
#include <stdio.h>



GameWin* GameWindowCreate(ChessGame* game) {
	GameWin* gameWin = (GameWin*) malloc(sizeof(GameWin));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	gameWin->simpleWindow = NULL;
	gameWin->panelButtons = NULL;
	gameWin->grid_texture = NULL;
	gameWin->p_white_texture = NULL;
	gameWin->p_black_texture = NULL;
	gameWin->b_white_texture = NULL;
	gameWin->b_black_texture = NULL;
	gameWin->q_white_texture = NULL;
	gameWin->q_black_texture = NULL;
	gameWin->k_white_texture = NULL;
	gameWin->k_black_texture = NULL;
	gameWin->n_white_texture = NULL;
	gameWin->n_black_texture = NULL;
	gameWin->r_white_texture = NULL;
	gameWin->r_black_texture = NULL;
	gameWin->chosenLoc = createLocation(NOT_CHOOSED,NOT_CHOOSED);
	if (gameWin == NULL ) {
		printf("Couldn't create GameWin struct\n");
		return NULL ;
	}
	// Create an application window with the following settings:
	gameWin->simpleWindow = simpleWindowCreate(NONE_WINDOW);
	// Check that the window was successfully created
	if (gameWin->simpleWindow == NULL ) {
		GameWindowDestroy(gameWin);
		return NULL;
	}
	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/grid.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		GameWindowDestroy(gameWin);
		return NULL;
	}
	gameWin->grid_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer,loadingSurface);
	if (gameWin->grid_texture == NULL) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		GameWindowDestroy(gameWin);
		return NULL;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	if(generatePieceTexture(gameWin) == GAME_WINDOW_FAILED){
		GameWindowDestroy(gameWin);
		return NULL;
	}
	bool canUndo = game->gameMode == 1 && !ChessArrayListIsEmpty(game->LastMoves) && game->gameDifficulty <=2;
	if(generatePanelButtons(gameWin,canUndo) == GAME_WINDOW_FAILED){
		GameWindowDestroy(gameWin);
		return NULL;
	}
	return gameWin;
}

GAME_WINDOW_MESSAGE generatePanelButtons(GameWin* gameWin,bool canUndo) {
	BUTTON_TYPE panelTypes[GAME_NUM_OF_PANEL_BUTTONS] = { GAME_RESTART_BUTTON,
			GAME_SAVE_BUTTON,
			GAME_LOAD_BUTTON,
			GAME_UNDO_BUTTON,
			GAME_MAIN_MENU_BUTTON,
			GAME_EXIT_BUTTON };
	bool panelActiveButtons[GAME_NUM_OF_PANEL_BUTTONS] = { true, true, true,true, true, true };
	bool panelClickableButtons[GAME_NUM_OF_PANEL_BUTTONS] = { true, true, true,canUndo, true, true };
	if (buttonArrayCreate(gameWin->panelButtons, panelTypes, panelActiveButtons,
			panelClickableButtons, GAME_NUM_OF_PANEL_BUTTONS) == BUTTON_FAILED) {

		free(gameWin->panelButtons);
		gameWin->panelButtons = NULL;
		return GAME_WINDOW_FAILED;
	}
	return GAME_WINDOW_SUCCESS;
}

GAME_WINDOW_MESSAGE generatePieceTexture(GameWin* gameWin){
	//PAWN
	SDL_Surface* loadingSurface = SDL_LoadBMP("./graphics/images/whitePawn.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->p_white_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->p_white_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/blackPawn.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->p_black_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->p_black_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	//BISHOP
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteBishop.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->b_white_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->b_white_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/blackBishop.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->b_black_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->b_black_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	//KNIGHT
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteKnight.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->n_white_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->n_white_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/blackKnight.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->n_black_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->n_black_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	//KING
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteKing.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->k_white_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->k_white_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/blackKing.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->k_black_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->k_black_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	//QUEEN
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteQueen.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->q_white_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->q_white_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/blackQueen.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->q_black_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->q_black_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	//ROOK
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/whiteRook.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->r_white_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->r_white_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/blackRook.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return GAME_WINDOW_FAILED;
	}
	gameWin->r_black_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer, loadingSurface);
	if (gameWin->r_black_texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return GAME_WINDOW_FAILED;
	}
	SDL_FreeSurface(loadingSurface);
	return GAME_WINDOW_SUCCESS;
}

void updateUndoButton(GameWin* gameWin, ChessGame* game){
	if(gameWin == NULL || game == NULL) return;
	Button* undoButton = gameWin->panelButtons[UNDO_IN_ARRAY];
	undoButton->isClickable = game->gameMode == 1 && !ChessArrayListIsEmpty(game->LastMoves) && game->gameDifficulty <=2;
	return;
}

void GameWindowDestroy(GameWin* gameWin) {
	if (gameWin == NULL) return;
	if(gameWin->simpleWindow != NULL) simpleWindowDestroy(gameWin->simpleWindow);
	if(gameWin->panelButtons != NULL) buttonArrayDestroy(gameWin->panelButtons,GAME_NUM_OF_PANEL_BUTTONS);
	if(gameWin->grid_texture != NULL) SDL_DestroyTexture(gameWin->grid_texture);
	if(gameWin->p_white_texture != NULL) SDL_DestroyTexture(gameWin->p_white_texture);
	if(gameWin->p_black_texture != NULL) SDL_DestroyTexture(gameWin->p_black_texture);
	if(gameWin->b_white_texture != NULL) SDL_DestroyTexture(gameWin->b_white_texture);
	if(gameWin->b_black_texture != NULL) SDL_DestroyTexture(gameWin->b_black_texture);
	if(gameWin->q_white_texture != NULL) SDL_DestroyTexture(gameWin->q_white_texture);
	if(gameWin->q_black_texture != NULL) SDL_DestroyTexture(gameWin->q_black_texture);
	if(gameWin->k_white_texture != NULL) SDL_DestroyTexture(gameWin->k_white_texture);
	if(gameWin->k_black_texture != NULL) SDL_DestroyTexture(gameWin->k_black_texture);
	if(gameWin->n_white_texture != NULL) SDL_DestroyTexture(gameWin->n_white_texture);
	if(gameWin->n_black_texture != NULL) SDL_DestroyTexture(gameWin->n_black_texture);
	if(gameWin->r_white_texture != NULL) SDL_DestroyTexture(gameWin->r_white_texture);
	if(gameWin->r_black_texture != NULL) SDL_DestroyTexture(gameWin->r_black_texture);
	free(gameWin);
}

GAME_WINDOW_MESSAGE GameWindowDraw(GameWin* gameWin,ChessGame* game,SDL_Event* event,bool drawMoves,Step* steps,int numOfSteps) {
	if(gameWin == NULL){
		return GAME_WINDOW_FAILED;
	}
	for(int i = 0; i < GAME_NUM_OF_PANEL_BUTTONS; ++i){
		drawButton(gameWin->panelButtons[i],gameWin->simpleWindow->renderer);
	}
	SDL_Rect rec = { .x = PANEL_WIDTH, .y = 0, .w = GAME_BOARD_SIZE, .h = GAME_BOARD_SIZE };
	SDL_SetRenderDrawColor(gameWin->simpleWindow->renderer, 255, 255, 255, 255); //Background is white.
	SDL_RenderClear(gameWin->simpleWindow->renderer);
	SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->grid_texture, NULL, &rec);
	if(drawMoves) drawGetAllMoves(gameWin,steps,numOfSteps);
	int i = 0, j = 0;
	Step step;
	Location loc;
	for (i = 0; i < BOARD_LINE_SIZE; i++) {
		for (j = 0; j < BOARD_LINE_SIZE; j++) {
			loc = createLocation(i,j);
			rec = boardLocToRect(loc);
			if(equalLocations(loc,gameWin->chosenLoc) && event->type == SDL_MouseMotionEvent &&
					isClickedOnBoard(event->button.x,event->button.y)) continue;
			if(drawPiece(gameWin,&rec,getPieceString(getPieceOnBoard(game,false))[0]) == GAME_WINDOW_FAILED){
				return GAME_FAILED;
			}
		}
	}
	if(event->type == SDL_MouseMotionEvent && isClickedOnBoard(event->button.x,event->button.y)){
		rec.x = event->button.x;
		rec.y = event->button.y;
		rec.h = REC_SIZE;
		rec.w = REC_SIZE;
		if(drawPiece(gameWin,&rec,getPieceString(getPieceOnBoard(game,false))[0]) == GAME_WINDOW_FAILED){
			return GAME_FAILED;
		}
	}
	SDL_RenderPresent(gameWin->simpleWindow->renderer);
	return GAME_WINDOW_SUCCESS;
}

void drawGetAllMoves(GameWin* gameWin,Step* steps,int numOfSteps){
	if(gameWin == NULL || steps == NULL || numOfSteps == 0) return;
	SDL_Rect rec;
	Step step;
	for(int i = 0; i < numOfSteps; ++i){
		step = steps[i];
		rec = boardLocToRect(step.dest);
		fillRecColor(gameWin,&rec,step.class);
	}
}

GAME_EVENT drawPiece(GameWin* gameWin,SDL_Rect* rec, char piece){
	switch(piece){
	case 'r':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->r_white_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'k':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->k_white_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'm':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->p_white_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'q':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->q_white_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'b':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->b_white_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'n':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->n_white_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'R':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->r_black_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'K':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->k_black_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'M':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->q_black_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'Q':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->q_black_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'B':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->b_black_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	case 'N':
		if(SDL_RenderCopy(gameWin->simpleWindow->renderer, gameWin->n_black_texture, NULL, &rec) == -1) return GAME_WINDOW_FAILED;
		break;
	}
	return GAME_WINDOW_SUCCESS;
}

void fillRecColor(GameWin* gameWin,SDL_Rect* rec,MoveClass moveClass){
	switch(moveClass){
	case Threatened:
		SDL_SetRenderDrawColor(gameWin->simpleWindow->renderer,255,0,0,1);
		break;
	case EatSomeone:
		SDL_SetRenderDrawColor(gameWin->simpleWindow->renderer,0,255,0,1);
		break;
	case ThreatenedAndEat:
		SDL_SetRenderDrawColor(gameWin->simpleWindow->renderer,210,85,250,1);
		break;
	case NormalStep:
		SDL_SetRenderDrawColor(gameWin->simpleWindow->renderer,240,215,130,1);
		break;
	}
	SDL_RenderFillRect(gameWin->simpleWindow->renderer,rec);
}

GAME_EVENT GameWindowHandleEvent(GameWin* gameWin, SDL_Event* event) {
	if (event == NULL || gameWin == NULL ) {
		return GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		spTicTacToeSetMove(gameWin->game, event->button.y / 200,
				event->button.x / 200);
		char winner = spTicTacToeCheckWinner(gameWin->game);
		if (winner == SP_PLAYER_1_SYMBOL) {
			return GAME_EVENT_X_WON;
		} else if (winner == SP_PLAYER_2_SYMBOL) {
			return GAME_EVENT_O_WON;
		} else if (spTicTacToeIsGameOver(gameWin->game)) {
			return GAME_EVENT_TIE;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return GAME_EXIT_EVENT;
		}
		break;
	default:
		return GAME_NONE_EVENT;
	}
	return GAME_NONE_EVENT;
}

Location mouseLocToBoardLoc(int x, int y){
	x = x - PANEL_WIDTH;
	y = y - PANEL_WIDTH;
	Location loc = createLocation(floor(x / REC_SIZE),floor(y / REC_SIZE)); //start from 0.
	return loc;
}

SDL_Rect boardLocToRect(Location loc){
	SDL_Rect rec = {
			.x = PANEL_WIDTH + loc.col * REC_SIZE,
			.y = PANEL_WIDTH + (GAME_N_ROWS-1-loc.row) * REC_SIZE,
			.h = REC_SIZE,
			.w = REC_SIZE,
	};
	return rec;
}

bool isClickedOnBoard(int x, int y){
	return PANEL_WIDTH <= x;
}
