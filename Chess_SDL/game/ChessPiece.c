#include "ChessPiece.h"


Piece* pieceCreate(PieceType type,Color color,int row,int col,int numOfMoves){
	Piece* piece = (Piece*) malloc(sizeof(Piece));
	if(piece == NULL) {
		printMallocError();
		return NULL; //mallocHandling
	}
	piece->type = type;
	piece->color = color;
	piece->loc = createLocation(row, col);
	piece->numOfMoves = numOfMoves;
	return piece;
}

Piece* copyPiece(Piece* piece){
	if(piece == NULL) return NULL;
	Piece* copy = pieceCreate(piece->type,piece->color,piece->loc.row,piece->loc.col,piece->numOfMoves);
	return copy;
}

void pieceDestroy(Piece* piece){
	if(piece == NULL) return;
	free(piece);
}

char* getPieceString(Piece* piece, bool fullName){
	if (piece == NULL){
		return "_";
	}
	char* name;
	switch(piece->type){
	case PAWN:
		if(fullName) name ="pawn";
		else name = piece->color == WHITE ? "m" : "M";
		break;
	case BISHOP:
		if(fullName) name ="bishop";
		else name = piece->color == WHITE ? "b" : "B";
		break;
	case ROOK:
		if(fullName) name ="rook";
		else name = piece->color == WHITE ? "r" : "R";
		break;
	case KING:
		if(fullName) name ="king";
		else name = piece->color == WHITE ? "k" : "K";
		break;
	case QUEEN:
		if(fullName) name ="queen";
		else name = piece->color == WHITE ? "q" : "Q";
		break;
	case KNIGHT:
		if(fullName) name ="knight";
		else name = piece->color == WHITE ? "n" : "N";
		break;
	}
	return name;
}
