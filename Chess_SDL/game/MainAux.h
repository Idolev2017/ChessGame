/*
 * MainAux.h
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: ido abulafya
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "ChessMiniMax.h"
#include <SDL.h>
#include <SDL_video.h>
GAME_MESSAGE chessPlayCom(ChessGame* game,bool consoleMode);

void printComMove(ChessGame* game,Location* move);

#endif /* MAINAUX_H_ */
