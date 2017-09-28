/*
 * ChessMiniMax.h
 *
 *  Created on: 1 בספט׳ 2017
 *      Author: Dolev
 */

#ifndef CHESSMINIMAX_H_
#define CHESSMINIMAX_H_

#define ERROR 123456
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ChessGame.h"
/**
 * Name: chessMinimaxSuggestMove
 * Description:
 * That is a shell function to chessRecursiveMiniMax.
 * eventually, returns a Locations array which contains the source of the piece that it decided to move
 * and also the destination - where the piece will be moved.
 */
Location* chessMinimaxSuggestMove(ChessGame* game, unsigned int maxDepth, int* type);
/**
 * Name: chessRecursiveMiniMax
 * Description:
 * computing what is the best move the computer can take against the user due to a MiniMax
 * algorithm which uses an scoring function that rates the gameBoard in different conditions.
 * It also uses alpha-beta pruning in order to reduce computations and to optimize the program.
 * That's a recursive function because it moves forward with steps in the game.
 * returns the score that was computed.
 */
int chessRecursiveMiniMax(ChessGame* game,unsigned int maxDepth,bool maxFlag, int alpha, int beta);
/**
 * Name: scoringFunction
 * Description:
 * This is the function that computes the scoring function of the current condition
 * of the game gameboard.
 * returns the score that was computed.
 */
int scoringFunction(ChessGame* game);
/**
 * Name: pieceScoreFunction
 * Description:
 * returns the score of a specific piece due to the current player:
 * positive for computer turn, negative for user turn.
 */
int pieceScoreFunction(Piece* piece,Color positiveColor);

#endif /* CHESSMINIMAX_H_ */
