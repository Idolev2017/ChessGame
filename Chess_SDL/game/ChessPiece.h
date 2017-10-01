/*
 * Piece.h
 *
 *  Created on: 23 баев„ 2017
 *      Author: Dolev
 */

#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ChessLocation.h"

#include "ChessAux.h"
#define LOC_LENGTH 6
//DON'T TOUCH THE ORDER OF ENUM TYPES !!!
typedef enum {
	PAWN,
	BISHOP,
	ROOK,
	QUEEN,
	KNIGHT,
	KING
}PieceType;

typedef enum {
	BLACK,
	WHITE
}Color;

/**
 * Struct: Piece
 * Description:
 * holds detailes about a Piece.
 * type can be Pawn, Knight, Bishop, Rook, King, Queen.
 * color is 0/1 = BLACK/WHITE
 * loc is leagl location on the gameboard.
 * numOfMoves is integer >= 0;
 */
typedef struct {
	PieceType type;
	Color color;
	Location loc;
	int numOfMoves;
} Piece;
/**
 * Name: pieceCreate
 * Description:
 * constructs a Piece object, allocates a memeory to it,
 * initialize its fields to the arguments who were given.
 * returns the new Piece.
 */
Piece* pieceCreate(PieceType type,Color color,int row,int col,int numOfMoves);
/**
 * Name: copyPiece
 * Description:
 * copies the Piece src with all of its fields and returns it.
 */
Piece* copyPiece(Piece* src);
/**
 * Name: pieceDestroy
 * Description:
 * if src != NULL then it gets freed.
 */
void pieceDestroy(Piece* src);
/**
 * Name: getPieceString
 * Description:
 * returns a string contains the name of the piece:
 * if fullName = true, then the full name of the piece will be returned,
 * otherwise, the first letter of the piece name will be returned
 * (uppercase letter for black pieces and lowercase for white pieces).
 * the exceptions are the Pawn and Knight pieces which in case fullName = false then
 * m/M will be returned for the Pawn and n/N for the Knight by the same rules.
 */
char* getPieceString(Piece* p, bool fullName);

#endif /* CHESSPIECE_H_ */
