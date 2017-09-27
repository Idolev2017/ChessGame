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

/**
 * Struct: ChessMove
 * Description:
 * holds detailes about a specific chess move in the game.
 * the Piece piece is moving from location prevLoc to newLoc,
 * if it ate an enemy piece in that move then capturedPiece = true,
 * if the move was to the enemy's first line (i.e. the farthest from the current piece's base)
 * then wasPromoted = true.
 */
typedef struct{
	Piece* piece;
	Location prevLoc;
	Location newLoc;
	bool wasPromoted;
	Piece* capturedPiece;
}ChessMove;
/**
 * Name: chessMoveCreate
 * Description:
 * constructs a ChessMove object, allocates a memeory to him,
 * initialize its fields to the arguments.
 * returns the new chess move.
 */
ChessMove* chessMoveCreate(Piece*, Location, Location, bool, Piece*);
/**
 * Name: chessMoveCopy
 * Description:
 * constructs a new ChessMove object, with the same data of the arguments.
 * i.e. copies the argument object and returns the copied object.
 */
ChessMove* chessMoveCopy(ChessMove*);
/**
 * Name: chessMoveDestroy
 * Description:
 * destroys the argument ChessMove object: destroys the piece and capturedPiece.
 * frees the memory allocated.
 */
void chessMoveDestroy(ChessMove*);

#endif /* CHESSMOVE_H_ */
