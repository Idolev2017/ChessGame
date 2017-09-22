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
	bool needPromoting;
	bool maxFlag = true;
	int* actualSize = NULL;
	Location* locs = NULL;
	actualSize = (int*) malloc(sizeof(int));
	locs = (Location*) malloc(sizeof(Location)*2);
	if(locs == NULL || actualSize == NULL){
		free(locs);
		free(actualSize);
		gameDestroy(copy);
		return NULL;
	}

	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			tmpLoc = createLocation(i,j);
			movingPiece = getPieceOnBoard(copy,tmpLoc);
			if (movingPiece == NULL || (movingPiece->color != copy->currentPlayer)) continue;
			if(getAllMoves(copy,tmpLoc,possibleMoves,actualSize,false) == GAME_FAILED) {
				free(actualSize);
				free(locs);
				gameDestroy(copy);
				return NULL;
			}
			else if(*actualSize == 0) continue;
			for(int moveIndex = 0; moveIndex < *actualSize; ++moveIndex){
				destLoc = copyLocation(possibleMoves[moveIndex]);
				if(playMove(copy,tmpLoc,destLoc,false) != GAME_SUCCESS) {
					printf("ERROR IN FIRST MINI MAX\n");
					free(actualSize);
					free(locs);
					gameDestroy(copy);
					return NULL;
				}
				movingPiece = getPieceOnBoard(copy,destLoc); //the piece after the move
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
					free(actualSize);
					gameDestroy(copy);
					return NULL;
				}
			}
		}
	}
	printf("alpha is: %d\n",alpha);
	printf("beta is: %d\n",beta);
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
	int *actualSize = (int*) malloc(sizeof(int));
	if(actualSize == NULL) return ERROR;
	bool needPromoting;
	Location tmpLoc;
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
				if(playMove(game,tmpLoc,destLoc,false) != GAME_SUCCESS) {
					printf("ERROR IN SECOND MINI MAX\n");
					free(actualSize);
					return ERROR;
				}
				movingPiece = getPieceOnBoard(game,destLoc);
				needPromoting = (movingPiece->color == WHITE && movingPiece->loc.row == 7) || (movingPiece->color == BLACK && movingPiece->loc.row == 0);
				if(movingPiece->type == PAWN && needPromoting){
					for(int i = 0; i <= 4; ++i){
						pawnPromoting(movingPiece, false, i);
						tmpScoring = chessRecursiveMiniMax(game,maxDepth-1,!maxFlag,alpha,beta);
						if(((alpha < tmpScoring) && maxFlag) || ((tmpScoring < beta) && !maxFlag)) {
							alpha = maxFlag ? tmpScoring : alpha;
							beta = maxFlag ? beta : tmpScoring;
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
					free(actualSize);
					return ERROR;
				}
				movingPiece = getPieceOnBoard(game,tmpLoc);
			}
		}
	}
	free(actualSize);
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

