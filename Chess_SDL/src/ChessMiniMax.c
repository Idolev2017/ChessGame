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
	copy->LastMoves = ChessArrayListCreate(maxDepth);
	int alpha = INT_MIN;
	int beta = INT_MAX;
	Piece* movingPiece = NULL;
	int tmpScoring;
	Location possibleMoves[28];
	Location destLoc;
	Location tmpLoc;
	Location* locs = (Location*) malloc(sizeof(Location)*2);
	if(locs == NULL){
		gameDestroy(copy);
		return NULL;
	}
	bool needPromoting;
	int a = 0;
	int *actualSize = &a;
	bool maxFlag = true;

	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			tmpLoc = createLocation(i,j);
			movingPiece = getPieceOnBoard(copy,tmpLoc);
			if (movingPiece == NULL || (movingPiece->color != copy->currentPlayer)) continue;
			if(getAllMoves(copy,tmpLoc,possibleMoves,actualSize,false) == GAME_FAILED) {
				printf("getALLmoves");
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
				movingPiece = getPieceOnBoard(copy,destLoc);
				needPromoting = (movingPiece->color == WHITE && destLoc.row == 7) || (movingPiece->color == BLACK && destLoc.row == 0);
				if(movingPiece->type == PAWN && needPromoting){
					for(int i = 0; i <= 4; ++i){
						pawnPromoting(movingPiece, false, i);
						tmpScoring = chessRecursiveMiniMax(game,maxDepth-1,!maxFlag,alpha,beta);
						if(alpha < tmpScoring){
							locs[0] = copyLocation(tmpLoc);
							locs[1] = copyLocation(destLoc);
							alpha = tmpScoring;
							*type = i;
						}
					}
					movingPiece->type = PAWN; //back to normal, delete this after we handle undo after pawn promoting.
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
	if(maxDepth == 0) return scoringFunction(game);
	Piece* movingPiece = NULL;
	bool theresLegalMove = false;
	Location possibleMoves[28];
	Location destLoc;
	int tmpScoring;
	int a = 0;
	int *actualSize = &a;
	bool needPromoting;
	Location tmpLoc;
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			if(beta <= alpha) return maxFlag ? alpha : beta;
			tmpLoc = createLocation(i,j);
			movingPiece = getPieceOnBoard(game,tmpLoc);
			if (movingPiece == NULL || (movingPiece->color != game->currentPlayer)) continue;
			else if(getAllMoves(game,tmpLoc,possibleMoves,actualSize,false) == GAME_FAILED) return ERROR;
			else if(*actualSize == 0) continue; //not legal move. equals to actualSize == 0.
			theresLegalMove = true;
			for(int moveIndex = 0; moveIndex < *actualSize; ++moveIndex){
				destLoc = copyLocation(possibleMoves[moveIndex]);
				if(playMove(game,tmpLoc,destLoc,false) != GAME_SUCCESS) {
					printf("ERROR IN SECOND MINI MAX\n");
					return ERROR;
				}
				movingPiece = getPieceOnBoard(game,destLoc);
				needPromoting = (movingPiece->color == WHITE && movingPiece->loc.row == 7) || (movingPiece->color == BLACK && movingPiece->loc.row == 0);
				if(movingPiece->type == PAWN && needPromoting){
					for(int i = 0; i <= 4; ++i){
						pawnPromoting(movingPiece, false, i);
						tmpScoring = chessRecursiveMiniMax(game,maxDepth-1,!maxFlag,alpha,beta);
						if((alpha < tmpScoring && maxFlag) || (tmpScoring < beta && !maxFlag)) {
							alpha = maxFlag ? tmpScoring : alpha;
							beta = maxFlag ? beta : tmpScoring;
						}
					}
				}
				else tmpScoring = chessRecursiveMiniMax(game,maxDepth-1,!maxFlag,alpha,beta);
				if((alpha < tmpScoring && maxFlag) || (tmpScoring < beta && !maxFlag)) {
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
		if(isPieceThreatened(game,currentKing) == PIECE_THREATENED) return (game->currentPlayer == game->userColor) ? 1000 : -1000;
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
			pieceScore = pieceScoreFunction(piece,1 - game->userColor);
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
	return 0;
}

