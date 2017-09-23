/*
 * ChessMove.h
 *
 *  Created on: 23 баев„ 2017
 *      Author: Dolev
 */

#ifndef CHESSMOVE_H_
#define CHESSMOVE_H_
#include <stdbool.h>
#include "ChessPiece.h"
#define MAX_MOVES 28
typedef struct{
	Piece* piece;
	Location prevLoc;
	Location newLoc;
	bool wasPromoted;
	Piece* capturedPiece;
}ChessMove;

ChessMove* chessMoveCreate(Piece*, Location, Location, bool, Piece*);

ChessMove* chessMoveCopy(ChessMove*);

void chessMoveDestroy(ChessMove*);

#endif /* CHESSMOVE_H_ */
