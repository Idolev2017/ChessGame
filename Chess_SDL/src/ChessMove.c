#include "ChessMove.h"

ChessMove* createChessMove(Piece* p, Location prevLoc, Location newLoc, bool wasPromoted, Piece* capturedPiece){
	ChessMove* move = (ChessMove*)malloc(sizeof(ChessMove));
	if(move == NULL) {
		printMallocError();
		return NULL;  //mallocHandling
	}
	move->piece = copyPiece(p);
	move->wasPromoted = wasPromoted;
	move->prevLoc = copyLocation(prevLoc);
	move->newLoc = copyLocation(newLoc);
	move->capturedPiece = copyPiece(capturedPiece);
	if(move->piece == NULL || (move->capturedPiece == NULL && capturedPiece != NULL)) { //mallocHandling
		destroyChessMove(move);
		return NULL;
	}
	return move;
}

ChessMove* copyChessMove(ChessMove* move){
	if (move == NULL) return NULL;
	ChessMove* copy = createChessMove(move->piece, move->prevLoc, move->newLoc, move->wasPromoted, move->capturedPiece);
	return copy;
}

void destroyChessMove(ChessMove* move){
	if(move == NULL) return;
	pieceDestroy(move->piece);
	pieceDestroy(move->capturedPiece);
	free(move);
}
