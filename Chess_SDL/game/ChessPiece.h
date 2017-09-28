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
/**
 * Struct: Location
 * Description:
 * holds detailes about a gameboard location.
 * row and col are integers in the range 0-7.
 */
typedef struct {
	int row;
	int col;
} Location;
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
 * Name: createLocation
 * Description:
 * constructs a Location object,
 * initialize its fields to the arguments who were given.
 * returns the new Location.
 */
Location createLocation(int row, int col);
/**
 * Name: copyLocation
 * Description:
 * copies the Location loc with all of its fields and returns it.
 */
Location copyLocation(Location loc);
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
/**
 * Name: parseLocation
 * Description:
 * if it recives a string in the template "<number,upperCaseLetter>"
 * then it parses it to a Location object as follows:
 * number in range 1-8 will be reduced by 1, upperCaseLetter in range A-H
 * will be replaced with a matching number from 0-7.
 * returns the new Location.
 */
Location parseLocation(char* str);
/**
 * Name: isLegalLoc
 * Description:
 * returns true if loc.row and loc.col are in range 0-7 inclusive.
 * otherwise it returns false.
 */
bool isLegalLoc(Location loc);
/**
 * Name: equalLocations
 * Description:
 * returns true if loc1 and loc2 have the same row number and col number.
 * otherwise it returns false.
 */
bool equalLocations(Location loc1, Location loc2);
/**
 * Name: printLoc
 * Description:
 * prints the location loc as a gameboard location as follows:
 * loc.row promoted by 1, loc.col in range 0-7 will be replaced with a matching
 * letter from A-H.
 * The printing will be in the following format "<row,col>".
 */
void printLoc(Location loc);
/**
 * Name: isRepresentLocation
 * Description:
 * returns true if the string str is in the following format:
 * "<something1,something2>".
 * otherwise it returns false.
 */
bool isRepresentLocation(char* str);
/**
 * Name: compareFunc
 * Description:
 * if (loc1->row == loc2->row) the it returns  (loc1->col - loc2->col),
 * otherwise it returns (loc1->row - loc2->row).
 */
int compareFunc(const void* object1, const void* object2);

#endif /* CHESSPIECE_H_ */
