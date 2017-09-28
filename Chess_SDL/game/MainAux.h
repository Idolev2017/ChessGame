/*
 * MainAux.h
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: ido abulafya
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "ChessMiniMax.h"
/**
 * Name: chessPlayCom
 * Description:
 * A function that handles the computer's turn and play the game
 *  as it told her by the AI (MiniMax procedure).
 */
GAME_MESSAGE chessPlayCom(ChessGame* game,bool consoleMode);
/**
 * Name: printComMove
 * Description:
 * prints the move that the computer took in the following format:
 * "Computer: move <PieceName> at <PieceSource> to <PieceDestination>\n"
 */
void printComMove(ChessGame* game,Location* move);

#endif /* MAINAUX_H_ */
