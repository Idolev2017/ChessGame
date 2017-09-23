/*
 ============================================================================
 Name        : Chess_SDL.c
 Author      : 
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include<SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MainAux.h"
#include "../graphics/ChessGUIManager.h"
int consoleMode();
int guiMode();
#define HistorySize 6
#define MAX_LEN 1024
#define DESTROY_GAME_AND_LINE(game, line) {\
		free(line);\
		gameDestroy(game);\
		return 0;\
}
#define SP_BUFF_SET() {	               \
		setvbuf(stdout,NULL,_IONBF,0); 	   \
		setvbuf(stderr,NULL,_IONBF,0);     \
		setvbuf(stdin,NULL,_IONBF,0);      \
}


int main(int argc, char** argv) {
	return guiMode();
}

int guiMode(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	GuiManager* guiManager = ChessGUIManagerCreate();
	if (guiManager == NULL ) {
		SDL_Quit();
		return 0;
	}
	SDL_Event event;
	while (1) {
		SDL_WaitEvent(&event);
		if (event.window.event == SDL_WINDOWEVENT_CLOSE || ChessGUIManagerHandleEvent(guiManager, &event) == MANAGER_QUIT) {
			break;
		}
		if(event.type != SDL_MOUSEMOTION || guiManager->gameWin->chosenLoc.row != NOT_CHOOSED)
			ChessGUIManagerDraw(guiManager,&event);
	}
	ChessGUIManagerDestroy(guiManager);
	SDL_Quit();
	return 0;
}
int consoleMode(){
	SP_BUFF_SET();
	ChessGame* game = gameCreate(HistorySize,true);
	if(game == NULL) return 0;
	ChessCommand cmd;
	GAME_MESSAGE gameMSG = GAME_SUCCESS;
	char* line = (char*) malloc(MAX_LEN*sizeof(char));
	if(line == NULL){
		gameDestroy(game);
		return 0;
	}
	GAME_STATUS status;

	while(true){
		if(game->gameMode == 1 && game->currentPlayer != game->userColor){
			if(chessPlayCom(game,true) == GAME_FAILED) DESTROY_GAME_AND_LINE(game, line)
			status = printWinner(game);
			if(status == CHECKMATE || status == TIE) DESTROY_GAME_AND_LINE(game, line)
		}
		if(gameMSG == GAME_SUCCESS) gamePrintBoard(game);

		printf("%s player - enter your move:\n",getCurrentPlayerString(game));
		if(fgets(line,MAX_LEN,stdin) == NULL) DESTROY_GAME_AND_LINE(game, line)

		cmd = ChessCommandParser(line);
		gameMSG = SetCommand(game, cmd);
		if(gameMSG == GAME_FAILED || gameMSG == GAME_QUITED) DESTROY_GAME_AND_LINE(game, line)
		if(gameMSG == GAME_SUCCESS){
			status = printWinner(game);
			if(status == CHECKMATE || status == TIE) DESTROY_GAME_AND_LINE(game, line)
		}

	}
}
