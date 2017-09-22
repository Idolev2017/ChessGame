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

Location* chessMinimaxSuggestMove(ChessGame* game, unsigned int maxDepth, PieceType* type);

int chessRecursiveMiniMax(ChessGame* game,unsigned int maxDepth,bool maxFlag, int alpha, int beta);

int scoringFunction(ChessGame* game);

int pieceScoreFunction(Piece* piece,Color positiveColor);

#endif /* CHESSMINIMAX_H_ */
