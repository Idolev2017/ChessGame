/*
 * ChessMove.h
 *
 *  Created on: 23 баев„ 2017
 *      Author: Dolev
 */

#ifndef CHESSMOVE_H_
#define CHESSMOVE_H_
#include "ChessPiece.h"
#include <stdbool.h>

typedef struct{
	Piece* piece;
	Location prevLoc;
	Location newLoc;
	bool wasPromoted;
	Piece* capturedPiece;
}ChessMove;

ChessMove* createChessMove(Piece*, Location, Location, bool, Piece*);

ChessMove* copyChessMove(ChessMove*);

void destroyChessMove(ChessMove*);

#endif /* CHESSMOVE_H_ */
