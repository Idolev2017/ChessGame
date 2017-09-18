/*
 * game.h
 *
 *  Created on: 23 баев„ 2017
 *      Author: Dolev
 */


#ifndef GAME_H_
#define GAME_H_
#include "GameSettings.h"
#include <stdlib.h>



#define max(a,b) (((a) < (b)) ? (b) : (a))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define abs(a) ( ( (a) > 0 ) ? (a) : (-(a)) )

typedef enum {
	Threatened,
	EatSomeone,
	ThreatenedAndEat,
	NormalStep
}MoveClass;

typedef struct {
	Location dest;
	MoveClass class;
} Step;
Step createStep(Location dest, MoveClass class);

GAME_MESSAGE SetCommand(ChessGame* game, ChessCommand cmd);

GAME_MESSAGE playMove(ChessGame* game, Location src,Location dest, bool toPrint);
//return invalid_move if all the moves are illegal
//return GAME_SUCCESS if there is at least one legal move.
//return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
GAME_MESSAGE getAllMoves(ChessGame* game, Location loc,Location* possibleMoves, int* actualSize,bool toPrint);

GAME_MESSAGE getAllMovesPawn(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);

GAME_MESSAGE getAllMovesBishop(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);

GAME_MESSAGE getAllMovesQueen(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);

GAME_MESSAGE getAllMovesRook(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);

GAME_MESSAGE getAllMovesKing(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);

GAME_MESSAGE getAllMovesKnight(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);

GAME_MESSAGE addingMove(ChessGame* game,Location pieceLoc,Location destLoc,Location* possibleMoves,int* actualSize);
//return malloced array
Step* distinguishMovesByPiece(ChessGame* game, Location* locArray,int size, Location src);

void printSteps(Step* steps,int size);

GAME_MESSAGE saveGame(ChessGame* game,char* filePath);

GAME_MESSAGE undoPrevMove(ChessGame* game,bool toPrint);

bool IsValidMove(ChessGame* game, int col);

Piece* getPieceOnBoard(ChessGame* game,Location loc);

void setPieceOnBoard(ChessGame* game,Location loc,Piece* p);

GAME_MESSAGE movePawn(ChessGame* game,Piece* piece,Location dest, bool toPrint);

GAME_MESSAGE moveRook (ChessGame* game, Piece* piece,Location dest);

GAME_MESSAGE moveBishop(ChessGame* game, Piece* piece,Location dest);

GAME_MESSAGE moveQueen(ChessGame* game, Piece* piece,Location dest);

GAME_MESSAGE moveKing(ChessGame* game, Piece* piece, Location dest);

GAME_MESSAGE moveKnight(ChessGame* game, Piece* piece, Location dest);

GAME_MESSAGE pawnPromoting(Piece* piece,bool toUser,PieceType type);

void killPiece (ChessGame* game,Location dest);

void simpleMovePiece(ChessGame* game,Location src,Location dest);

GAME_MESSAGE moveAndCapture (ChessGame* game, Location src, Location dest);

GAME_MESSAGE isPieceThreatened(ChessGame* game,Piece* piece);

GAME_MESSAGE isPieceThreatenedWithMove(ChessGame* game,Piece* piece,Location src, Location dest);

bool checkingLineThreat(ChessGame* game,Piece* piece, bool vertically);

bool checkingDiagonalThreat(ChessGame* game,Piece* piece, bool gradient);

bool checkingKnightsThreat(ChessGame* game,Piece* piece);

GAME_STATUS checkingWinner(ChessGame* game);

GAME_STATUS printWinner(ChessGame* game);

char* getCurrentPlayerString(ChessGame* game);

#endif /* GAME_H_ */
