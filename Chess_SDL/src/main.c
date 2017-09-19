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
#include "graphics/ChessMainWin.h"
//#include "graphics/ChessGUIManager.h"

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	MainWin* mainWin = mainWindowCreate();
//	GuiManager* manager = spManagerCreate();
//	if (manager == NULL ) {
//		SDL_Quit();
//		return 0;
//	}
//	SDL_Event event;
//	while (1) {
//		SDL_WaitEvent(&event);
//		if (spManagerHandleEvent(manager, &event) == MANAGER_QUTT) {
//			break;
//		}
//		spManagerDraw(manager);
//	}
//	spManagerDestroy(manager);
	SDL_Quit();
	return 0;
}
