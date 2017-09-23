/*
 * ChessMiniMax.c
 *
 *  Created on: 1 בספט׳ 2017
 *      Author: Dolev
 */

#include "ChessMiniMax.h"

Location* chessMinimaxSuggestMove(ChessGame* game, unsigned int maxDepth, PieceType* type){
	ChessGame* copy = gameCopy(game);
	if(copy == NULL) return NULL;
	ChessArrayListDestroy(copy->LastMoves);
	copy->LastMoves = ChessArrayListCreate(2*maxDepth);
	int alpha = INT_MIN;
	int beta = INT_MAX;
	Piece* movingPiece = NULL;
	int tmpScoring;
	Location possibleMoves[28];
	Location destLoc;
	Location tmpLoc;
	bool maxFlag = true;
	int num = 0;
	int* actualSize = &num;
	Location* locs = NULL;
	locs = (Location*) malloc(sizeof(Location)*2);
	if(locs == NULL || actualSize == NULL){
		free(locs);
		gameDestroy(copy);
		return NULL;
	}

	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			tmpLoc = createLocation(i,j);
			movingPiece = getPieceOnBoard(copy,tmpLoc);
			if (movingPiece == NULL || (movingPiece->color != copy->currentPlayer)) continue;
			if(getAllMoves(copy,tmpLoc,possibleMoves,actualSize,false) == GAME_FAILED) {
				free(locs);
				gameDestroy(copy);
				return NULL;
			}
			else if(*actualSize == 0) continue;
			for(int moveIndex = 0; moveIndex < *actualSize; ++moveIndex){
				destLoc = copyLocation(possibleMoves[moveIndex]);
				if(playMove(copy,tmpLoc,destLoc,false) != GAME_SUCCESS) {
					printf("ERROR IN FIRST MINI MAX\n");
					free(locs);
					gameDestroy(copy);
					return NULL;
				}
				movingPiece = getPieceOnBoard(copy,destLoc); //the piece after the move
				if(needPromoting(getPieceOnBoard(copy,destLoc))){
					for(int i = 0; i <= 4; ++i){
						movingPiece = getPieceOnBoard(copy,destLoc);
						pawnPromoting(movingPiece, false, i);

						ChessMove* move = ChessArrayListGetFirst(copy->LastMoves);
						ChessArrayListRemoveFirst(copy->LastMoves);
						move->wasPromoted = true;
						move->piece->type = i;
						ChessArrayListAddFirst(copy->LastMoves, move);

						tmpScoring = chessRecursiveMiniMax(copy,maxDepth-1,!maxFlag,alpha,beta);
						if(alpha < tmpScoring){
							locs[0] = copyLocation(tmpLoc);
							locs[1] = copyLocation(destLoc);
							alpha = tmpScoring;
							*type = i;
						}
						movingPiece = getPieceOnBoard(copy,destLoc);
						if(tmpScoring == ERROR || undoPrevMove(copy,false) != GAME_SUCCESS){
							printf("tmpScoring is ERROR : %d\n", tmpScoring == ERROR);
							free(locs);
							gameDestroy(copy);
							return NULL;
						}
					}
				}
				else {
					tmpScoring = chessRecursiveMiniMax(copy,maxDepth-1,!maxFlag,alpha,beta);
					if(alpha < tmpScoring){
						locs[0] = copyLocation(tmpLoc);
						locs[1] = copyLocation(destLoc);
						alpha = tmpScoring;
						*type = PAWN;
					}
				}
				if(tmpScoring == ERROR || undoPrevMove(copy,false) != GAME_SUCCESS){
					printf("tmpScoring is ERROR : %d\n", tmpScoring == ERROR);
					free(locs);
					gameDestroy(copy);
					return NULL;
				}
			}
		}
	}
	gameDestroy(copy);
	return locs;
}

int chessRecursiveMiniMax(ChessGame* game,unsigned int maxDepth,bool maxFlag, int alpha, int beta){
	if(maxDepth == 0) {
		if(checkingWinner(game) == CHECKMATE) return (game->currentPlayer == game->userColor) ? 1000 : -1000;
		return scoringFunction(game);
	}
	Piece* movingPiece = NULL;
	bool theresLegalMove = false;
	Location possibleMoves[28];
	Location destLoc;
	int tmpScoring;
	int num = 0;
	int* actualSize = &num;
	Location tmpLoc;
	GAME_MESSAGE msg;
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			if(beta <= alpha) return maxFlag ? alpha : beta;
			tmpLoc = createLocation(i,j);
			movingPiece = getPieceOnBoard(game,tmpLoc);
			if (movingPiece == NULL || (movingPiece->color != game->currentPlayer)) continue;
			else if(getAllMoves(game,tmpLoc,possibleMoves,actualSize,false) == GAME_FAILED) {
				free(actualSize);
				return ERROR;
			}
			else if(*actualSize == 0) continue; //no legal moves. continue to next piece.
			theresLegalMove = true;
			for(int moveIndex = 0; moveIndex < *actualSize; ++moveIndex){
				destLoc = copyLocation(possibleMoves[moveIndex]);
				msg = playMove(game,tmpLoc,destLoc,false);
				if(msg != GAME_SUCCESS) {
					playMove(game,tmpLoc,destLoc,true);
					if(msg == GAME_INVALID_MOVE) printf("GAME_INVALID_MOVE\n");
					if(msg == GAME_FAILED) printf("GAME_FAILED\n");
					if(msg == GAME_INVALID_POSITION) printf("GAME_INVALID_POSITION\n");
					if(msg == GAME_INVALID_PIECE) printf("GAME_INVALID_PIECE\n");
					printLoc(tmpLoc);
					printLoc(destLoc);
					printf("ERROR IN SECOND MINI MAX\n");
					return ERROR;
				}
				if(needPromoting(getPieceOnBoard(game,destLoc))){
					for(int i = 0; i <= 4; ++i){
						movingPiece = getPieceOnBoard(game,destLoc);
						pawnPromoting(movingPiece, false, i); //i represent the type.

						ChessMove* move = ChessArrayListGetFirst(game->LastMoves);
						ChessArrayListRemoveFirst(game->LastMoves);
						move->wasPromoted = true;
						move->piece->type = i;
						ChessArrayListAddFirst(game->LastMoves, move);

						tmpScoring = chessRecursiveMiniMax(game,maxDepth-1,!maxFlag,alpha,beta);
						if(((alpha < tmpScoring) && maxFlag) || ((tmpScoring < beta) && !maxFlag)) {
							alpha = maxFlag ? tmpScoring : alpha;
							beta = maxFlag ? beta : tmpScoring;
						}
						if(tmpScoring == ERROR || undoPrevMove(game,false) != GAME_SUCCESS) {
							printf("ERROR IN SECOND MINI MAX2\n");
							return ERROR;
						}
					}
				}
				else tmpScoring = chessRecursiveMiniMax(game,maxDepth-1,!maxFlag,alpha,beta);
				if(((alpha < tmpScoring) && maxFlag) || ((tmpScoring < beta) && !maxFlag)) {
					alpha = maxFlag ? tmpScoring : alpha;
					beta = maxFlag ? beta : tmpScoring;
				}
				if(tmpScoring == ERROR || undoPrevMove(game,false) != GAME_SUCCESS) {
					printf("ERROR IN SECOND MINI MAX2\n");
					return ERROR;
				}
				movingPiece = getPieceOnBoard(game,tmpLoc);
			}
		}
	}
	if(!theresLegalMove){
		Piece* currentKing = game->currentPlayer == WHITE ? game->whiteKing : game->blackKing;
		if(isPieceThreatened(game,currentKing) == PIECE_THREATENED) return (game->currentPlayer == game->userColor) ? 1000 : -1000; //CHECKMATE
		else return scoringFunction(game);
	}
	return maxFlag ? alpha : beta;
}

int scoringFunction(ChessGame* game){
	Piece* piece = NULL;
	int score = 0;
	int pieceScore;
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			piece = getPieceOnBoard(game,createLocation(i,j));
			if (piece == NULL) continue;
			pieceScore = pieceScoreFunction(piece,game->userColor == WHITE ? BLACK : WHITE);
			score += pieceScore;
		}
	}
	return score;
}

int pieceScoreFunction(Piece* piece,Color positiveColor){
	if(piece == NULL) return ERROR;
	int positive = (piece->color == positiveColor);
	switch(piece->type){
	case PAWN:
		return positive ? 1 : -1;
	case BISHOP:
		return positive ? 3 : -3;
	case KNIGHT:
		return positive ? 3 : -3;
	case ROOK:
		return positive ? 5 : -5;
	case QUEEN:
		return positive ? 9 : -9;
	case KING:
		return positive ? 100 : -100;
	}
	return ERROR;
}

