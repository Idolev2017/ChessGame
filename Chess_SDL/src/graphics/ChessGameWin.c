#include "ChessGameWin.h"

#include <assert.h>
#include <stdio.h>

GameWin* gameWindowCreate() {
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
	gameWin->savedLastMove = true;
	if (gameWin == NULL ) {
		printf("Couldn't create GameWin struct\n");
		return NULL ;
	}
	// Create an application window with the following settings:
	gameWin->simpleWindow = simpleWindowCreate(NONE_WINDOW);
	// Check that the window was successfully created
	if (gameWin->simpleWindow == NULL ) {
		gameWindowDestroy(gameWin);
		return NULL;
	}
	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/grid.bmp");
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		gameWindowDestroy(gameWin);
		return NULL;
	}
	gameWin->grid_texture = SDL_CreateTextureFromSurface(gameWin->simpleWindow->renderer,loadingSurface);
	if (gameWin->grid_texture == NULL) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		gameWindowDestroy(gameWin);
		return NULL;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	if(generatePieceTexture(gameWin) == GAME_WINDOW_FAILED){
		gameWindowDestroy(gameWin);
		return NULL;
	}
	if(generatePanelButtons(gameWin,false) == GAME_WINDOW_FAILED){
		gameWindowDestroy(gameWin);
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

void gameWindowDestroy(GameWin* gameWin) {
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

GAME_WINDOW_MESSAGE gameWindowDraw(GameWin* gameWin,ChessGame* game,SDL_Event* event,bool drawMoves,Step* steps,int numOfSteps) {
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

GAME_EVENT gameWindowHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event) {
	if (event == NULL || gameWin == NULL ) {
		return GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		if(!isClickedOnBoard(event->button.x,event->button.y) && event->button.button == SDL_BUTTON_LEFT) {
			gameWin->chosenLoc = createLocation(NOT_CHOOSED,NOT_CHOOSED);
			return gameWindowPanelHandleEvent(gameWin,event);
		}
		else return gameWindowBoardHandleEvent(gameWin,event);
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

GAME_EVENT gameWindowPanelHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event){
	if(!gameWin || !game) return GAME_EXIT_EVENT;
	gameWin->chosenLoc = createLocation(NOT_CHOOSED,NOT_CHOOSED);
	Button* button;
	int prevDifficulty,prevGameMode,prevUserColor;
	GAME_MESSAGE msg;
	bool exit;
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:{
		button = whichButtonWasClicked(gameWin->panelButtons,GAME_NUM_OF_PANEL_BUTTONS,event->button.x, event->button.y);
		switch(button->type){
		case GAME_RESTART_BUTTON:
			gameRestartGui(prevDifficulty, prevGameMode, prevUserColor, game);
			gameWin->savedLastMove = true;
			return GAME_NORMAL_EVENT;

		case GAME_SAVE_BUTTON:
			gameWin->savedLastMove = true;
			return GAME_SAVE_EVENT;

		case GAME_LOAD_BUTTON:
			gameWin->savedLastMove = true;
			return GAME_LOAD_EVENT;

		case GAME_UNDO_BUTTON:
			gameWin->savedLastMove = false;
			return gameUndoGui(game);

		case GAME_MAIN_MENU_BUTTON:
			if(gameWin->savedLastMove) return GAME_MAIN_MENU_EVENT;
			exit = confirmExitFromGame();
			if(exit) return GAME_MAIN_MENU_EVENT;
			return GAME_NONE_EVENT;

		case GAME_EXIT_BUTTON:
			if(gameWin->savedLastMove) return GAME_EXIT_EVENT;
			exit = confirmExitFromGame();
			if(exit) return GAME_EXIT_EVENT;
			return GAME_NONE_EVENT;
		}
	}
	break;
	default:
		return GAME_NONE_EVENT;
	}
	return GAME_NONE_EVENT;
}

GAME_EVENT gameWindowBoardHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event){
	Location tmpLoc;
	GAME_MESSAGE msg;
	GAME_EVENT winnerEvent;

	switch (event->type) {

	case SDL_MOUSEBUTTONDOWN:
		if(event->button.button == SDL_BUTTON_RIGHT){
			drawGetAllMoves()
		}
		else if(event->button.button == SDL_BUTTON_LEFT){
			tmpLoc = mouseLocToBoardLoc(event->button.x,event->button.y);
			if(getPieceOnBoard(game,tmpLoc) != NULL && getPieceOnBoard(game,tmpLoc)->color == game->currentPlayer){
				gameWin->chosenLoc = tmpLoc;
			}
		}
		break;


	case SDL_MOUSEBUTTONUP:{
		if(event->button.button != SDL_BUTTON_LEFT) return GAME_NONE_EVENT;
		if(gameWin->chosenLoc.row == NOT_CHOOSED) return GAME_NONE_EVENT;
		tmpLoc = mouseLocToBoardLoc(event->button.x,event->button.y);
		if((msg = playMove(game,gameWin->chosenLoc,tmpLoc,false)) == GAME_FAILED) return GAME_EXIT_EVENT;
		gameWin->chosenLoc = createLocation(NOT_CHOOSED,NOT_CHOOSED);
		if(playMove(game,gameWin->chosenLoc,tmpLoc,false) != GAME_SUCCESS) return GAME_NORMAL_EVENT;
		//move is legal
		winnerEvent = gameCheckingWinnerGui(game);
		if(game->gameMode == 2) return winnerEvent;
		else{
			showWinnerMessage(winnerEvent);
			SDL_Delay(1000);
			if(chessPlayCom(game) == GAME_FAILED) return GAME_EXIT_EVENT;
			return gameCheckingWinnerGui(game);
		}

	}
	break;
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

bool confirmExitFromGame(){
	SDL_MessageBoxButtonData buttons[] = {
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "cancel" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};
	SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{ 255,   0,   0 },
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{   0, 255,   0 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{ 255, 255,   0 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{   0,   0, 255 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{ 255,   0, 255 }
			}
	};
	SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"warning", /* .title */
			"Are you sure you want to exit before saving the game?", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return 1;
	}
	return (buttonid == 1) ? true : false;
}

void gameRestartGui(int prevDifficulty, int prevGameMode, int prevUserColor, ChessGame* game) {
	prevDifficulty = game->gameDifficulty;
	prevGameMode = game->gameMode;
	prevUserColor = game->userColor;
	gameInitialization(game, true, HISTORY_SIZE);
	simpleSettingsSetter(game, prevDifficulty, prevGameMode, prevUserColor);
}

GAME_EVENT gameUndoGui(ChessGame* game){
	GAME_MESSAGE msg;
	msg = undoPrevMove(game,false);
	if(msg == GAME_FAILED) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error",
				"undo move cannot be done",NULL);
		return GAME_EXIT_EVENT;
	}
	if(msg == GAME_SUCCESS) return GAME_NORMAL_EVENT;
	if(msg == GAME_NO_HISTORY) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Empty history","move cannot be undone",NULL);
	}
	else if(msg == GAME_INVALID_ARGUMENT) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Invalid move","Undo command not available in 2 players mode",NULL);
	}
	return GAME_NONE_EVENT;
}

void gameWindowHide(GameWin* gameWin) {
	simpleWindowHide(gameWin->simpleWindow);
}

void gameWindowShow(GameWin* gameWin) {
	simpleWindowShow(gameWin->simpleWindow);
}

GAME_EVENT gameCheckingWinnerGui(ChessGame* game){
	GAME_STATUS winnerStatus = checkingWinner(game);
	switch(winnerStatus){
	case CHECK:
		return GetCurrentPlayer(game) == WHITE ? GAME_WHITE_CHECK_EVENT : GAME_BLACK_CHECK_EVENT;
	case CHECKMATE:
		return GetCurrentPlayer(game) == WHITE ? GAME_WHITE_CHECKMATE_EVENT : GAME_BLACK_CHECKMATE_EVENT;
	case TIE:
		return GAME_TIE_EVENT;
	}
	return GAME_NORMAL_EVENT;
}

void showWinnerMessage(GAME_EVENT event){
	switch(event){
	case GAME_WHITE_CHECK_EVENT:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "white king threatened",NULL);
		break;
	case GAME_BLACK_CHECK_EVENT:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "black king threatened",NULL);
		break;
	case GAME_WHITE_CHECKMATE_EVENT:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "white player won",NULL);
		break;
	case GAME_BLACK_CHECKMATE_EVENT:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "black player won",NULL);
		break;
	case GAME_TIE_EVENT:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "it's a TIE",NULL);
		break;
	case GAME_NONE_EVENT:
		break;
	}
}
