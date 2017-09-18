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

typedef struct {
	int row;
	int col;
} Location;

typedef struct {
	PieceType type;
	Color color;
	Location loc;
} Piece;

Piece* pieceCreate(PieceType type, int color, int row, int col);
Piece* copyPiece(Piece* src);
Location createLocation(int row, int col);
Location copyLocation(Location loc);
void pieceDestroy(Piece* src);
char* getPieceString(Piece* p, bool fullName);
Location parseLocation(char* str);
bool isLegalLoc(Location loc);
bool equalLocations(Location loc1, Location loc2);
void printLoc(Location loc);
bool isRepresentLocation(char* str);
int compareFunc(const void* object1, const void* object2);

#endif /* CHESSPIECE_H_ */
