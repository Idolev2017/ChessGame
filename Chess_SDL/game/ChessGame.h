/*
 * game.h
 *
 *  Created on: 23 баев„ 2017
 *      Author: Dolev
 */


#ifndef GAME_H_
#define GAME_H_
#include <stdlib.h>
#include "GameSettings.h"



#define max(a,b) (((a) < (b)) ? (b) : (a))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef enum {
	Threatened,
	EatSomeone,
	ThreatenedAndEat,
	NormalStep
}MoveClass;

/**
 * Struct: Step
 * Description:
 * holds detailes about a specific step in the game.
 * dest is the location on the gameboard in which the piece moves to
 * and class is a MoveClass object which can be one of that list:
 * Threatened, EatSomeone, ThreatenedAndEat and NormalStep.
 */
typedef struct {
	Location dest;
	MoveClass class;
} Step;
/**
 * Name: createStep
 * Description:
 * constructs a Step object with the following details:
 * destination is dest and the moveClass is class.
 * returns that Step object.
 */
Step createStep(Location dest, MoveClass class);
/**
 * Name: setCommand
 * Description:
 * executes the command cmd in the ChessGame object game.
 */
GAME_MESSAGE setCommand(ChessGame* game, ChessCommand cmd);
/**
 * Name: playMove
 * Description:
 * executes the following move if and only if it's a legal chess move:
 * move the piece that in location src to the location dest in the ChessGame game.
 * if the userTurn boolean is true it also prints error messages to the console.
 */
GAME_MESSAGE playMove(ChessGame* game, Location src,Location dest, bool userTurn);
/**
 * Name: getAllMoves
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMoves(ChessGame* game, Location loc,Location* possibleMoves, int* actualSize,bool userTurn);
/**
 * Name: getAllMovesPawn
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the PAWN piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMovesPawn(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);
/**
 * Name: getAllMovesBishop
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the BISHOP piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMovesBishop(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);
/**
 * Name: getAllMovesQueen
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the QUEEN piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMovesQueen(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);
/**
 * Name: getAllMovesRook
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the ROOk piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMovesRook(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);
/**
 * Name: getAllMovesKing
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the KING piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMovesKing(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);
/**
 * Name: getAllMovesKnight
 * Description:
 * if it's allowed the function will insert the array called possibleMoves all the possible moves
 * that can be done on the KNIGHT piece sitting in the location loc in the ChessGame game.
 * the number of possible Moves will be held in the actualSize int in the end.
 * if the userTurn boolean is true it also prints error messages to the console.
 * return invalid_move if all the moves are illegal
 * return GAME_SUCCESS if there is at least one legal move.
 * return PIECE_THREATENED if there is at least one move that exposes the king, and the other are illegal.
 */
GAME_MESSAGE getAllMovesKnight(ChessGame* game,Piece* piece, Location* possibleMoves, int* actualSize);
/**
 * Name: addMoveToArray
 * Description:
 * if moving the piece sitting in pieceLoc to destLoc will not make it threatened by the enemy's king
 * then a copy of destLoc will be added to the actualSize'th place in the array possibleMoves.
 */
GAME_MESSAGE addMoveToArray(ChessGame* game,Location pieceLoc,Location destLoc,Location* possibleMoves,int* actualSize);
/**
 * Name: distinguishMovesByPiece
 * Description:
 * classifies all the possible moves of a specific piece on board to four classes:
 * Threatened, EatSomeone, ThreatenedAndEat, NormalStep.
 * return malloced array of legal steps classified to categories.
 */
Step* distinguishMovesByPiece(ChessGame* game, Location* locArray,int size, Location src);
/**
 * Name: printSteps
 * Description:
 * prints the possible moves of a specific piece line by line
 * with special symbols that mark what class a step belongs to.
 */
void printSteps(Step* steps,int size);
/**
 * Name: saveGame
 * Description:
 * saves the current gameboard and the current settings to a file that's
 * in the path filePath.
 * the struct of the saved file is XML.
 * if any error of opening and closing the file or any error of writing to the file
 * occurs then an error message will be printed.
 * it returns if the game saving was successful or not.
 */
bool saveGame(ChessGame* game,char* filePath);
/**
 * Name: undoPrevMove
 * Description:
 * if it's allowed in the current game settings and the history is not empty
 * then the last move that was taken is canceled.
 * if userTurn boolean is true then errors messages wil be printed if needed.
 * returns if the undo succeeded or the history was empty or that the current game settings prohibit undo.
 */
GAME_MESSAGE undoPrevMove(ChessGame* game,bool userTurn);
/**
 * Name: isValidMove
 * Description:
 */
//bool isValidMove(ChessGame* game, int col);
/**
 * Name: getPieceOnBoard
 * Description:
 * if the location is a legal location on the game gameboard then
 * it returns the object that is in the location loc.(also NULL is accepted).
 */
Piece* getPieceOnBoard(ChessGame* game,Location loc);
/**
 * Name: setPieceOnBoard
 * Description:
 * if the location is a legal location on the game gameboard then
 * it locates the piece p in the location loc and afterwords updates the kings pointers if p is one.
 */
void setPieceOnBoard(ChessGame* game,Location loc,Piece* p);
/**
 * Name: needPromoting
 * Description:
 * if Piece piece is located in the enemy's first line (i.e. the farthest from its base)
 * then it returns true, otherwise it returns false.
 */
bool needPromoting(Piece* piece);
/**
 * Name: movePawn
 * Description:
 * checks if moving the PAWN Piece piece from its location to the location dest is legal,
 * if so it executes the move and return a GAME_SUCCESS message.
 * otherwise it returns GAME_INVALID_MOVE.
 */
GAME_MESSAGE movePawn(ChessGame* game,Piece* piece,Location dest, bool userTurn);
/**
 * Name: moveRook
 * Description:
 * checks if moving the ROOK Piece piece from its location to the location dest is legal,
 * if so it executes the move and return a GAME_SUCCESS message.
 * otherwise it returns GAME_INVALID_MOVE.
 */
GAME_MESSAGE moveRook (ChessGame* game, Piece* piece,Location dest);
/**
 * Name: moveBishop
 * Description:
 * checks if moving the BISHOP Piece piece from its location to the location dest is legal,
 * if so it executes the move and return a GAME_SUCCESS message.
 * otherwise it returns GAME_INVALID_MOVE.
 */
GAME_MESSAGE moveBishop(ChessGame* game, Piece* piece,Location dest);
/**
 * Name: moveQueen
 * Description:
 * checks if moving the QUEEN Piece piece from its location to the location dest is legal,
 * if so it executes the move and return a GAME_SUCCESS message.
 * otherwise it returns GAME_INVALID_MOVE.
 */
GAME_MESSAGE moveQueen(ChessGame* game, Piece* piece,Location dest);
/**
 * Name: moveKing
 * Description:
 * checks if moving the KING Piece piece from its location to the location dest is legal,
 * if so it executes the move and return a GAME_SUCCESS message.
 * otherwise it returns GAME_INVALID_MOVE.
 */
GAME_MESSAGE moveKing(ChessGame* game, Piece* piece, Location dest);
/**
 * Name: moveKnight
 * Description:
 * checks if moving the KNIGHT Piece piece from its location to the location dest is legal,
 * if so it executes the move and return a GAME_SUCCESS message.
 * otherwise it returns GAME_INVALID_MOVE.
 */
GAME_MESSAGE moveKnight(ChessGame* game, Piece* piece, Location dest);

GAME_MESSAGE GameCastling(ChessGame* game,ChessCommand cmd);

GAME_MESSAGE canCastling(ChessGame* game, Piece* king,bool rightCastling);
/**
 * Name: pawnPromoting
 * Description:
 * asks the user (if toUser is true) to what piece he wants to upgrade the Pawn Piece piece.
 * if the AI uses that function it will the change the Piece piece type to the type
 * that it got from the function argument.
 */
GAME_MESSAGE pawnPromoting(Piece* piece,bool toUser,PieceType type);
/**
 * Name: killPiece
 * Description:
 * invariant: the location dest is a legal gameboard location.
 * the function destroys the piece, if exists, in the location dest.
 * eventually the gameboard in the location dest will hold NULL pointer.
 */
void killPiece (ChessGame* game,Location dest);
/**
 * Name: simpleMovePiece
 * Description:
 * invariant: the locations src and dest are legal gameboard locations.
 * the function moves the piece which is located in src to the location dest.
 * then put NULL in the location src.
 */
void simpleMovePiece(ChessGame* game,Location src,Location dest);
/**
 * Name: moveAndCapture
 * Description:
 * if moving the piece that is located in location src to location dest causing a legal capture
 * then that move and capture take a place.
 */
GAME_MESSAGE moveAndCapture (ChessGame* game, Location src, Location dest);
/**
 * Name: isPieceThreatened
 * Description:
 * returns PIECE_THREATENED if the Piece piece is threatened by the enemy's pieces in its location.
 * otherwise return GAME_SUCCESS.
 */
GAME_MESSAGE isPieceThreatened(ChessGame* game,Piece* piece);
/**
 * Name: isPieceThreatenedWithMove
 * Description:
 * returns PIECE_THREATENED if the Piece piece will be threatened by the enemy's pieces if it
 * will move to location dest from location src.
 * otherwise return GAME_SUCCESS.
 */
GAME_MESSAGE isPieceThreatenedWithMove(ChessGame* game,Piece* piece,Location src, Location dest);
/**
 * Name: checkingLineThreat
 * Description:
 * returns true if the Piece piece is threatened by the enemy's pieces that in the same line
 * vertically or horizontally.
 * otherwise return false.
 */
bool checkingLineThreat(ChessGame* game,Piece* piece, bool vertically);
/**
 * Name: checkingDiagonalThreat
 * Description:
 * returns true if the Piece piece is threatened by the enemy's pieces that in the same diagonal
 * in positive or negative gradient.
 * otherwise return false.
 */
bool checkingDiagonalThreat(ChessGame* game,Piece* piece, bool gradient);
/**
 * Name: checkingKnightsThreat
 * Description:
 * returns true if the Piece piece is threatened by the enemy's knights,
 * otherwise return false.
 */
bool checkingKnightsThreat(ChessGame* game,Piece* piece);
/**
 * Name: checkingWinner
 * Description:
 * returns CHECK if the current player's king is threatened.
 * returns CHECKMATE if the current player's king is threatened and has no legal move to escape.
 * returns TIE if there is no legal move to the current king but it's also not threatened.
 * returns NORMAL if there is legal move and the current king is also not threatened.
 */
GAME_STATUS checkingWinner(ChessGame* game);
/**
 * Name: printWinner
 * Description:
 * prints to the console if there is a CHECK, CHECKMATE or a TIE.
 */
GAME_STATUS printWinner(ChessGame* game);
/**
 * Name: getCurrentPlayerString
 * Description:
 * returns the current player's string: black or white.
 */
char* getCurrentPlayerString(ChessGame* game);

#endif /* GAME_H_ */
