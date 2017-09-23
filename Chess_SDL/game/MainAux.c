/*
 * MainAux.c
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: ido abulafya
 */
#include "MainAux.h"

GAME_MESSAGE chessPlayCom(ChessGame* game,bool consoleMode){
	Location* move;
	int typeValue = PAWN;
	char path[20];
	move = chessMinimaxSuggestMove(game,game->gameDifficulty,&typeValue);
	sprintf(path,"%d",typeValue);
	if(move == NULL) return GAME_FAILED;
	GAME_MESSAGE msg = playMove(game, move[0], move[1], false);
	if(msg == GAME_SUCCESS && consoleMode) printComMove(game,move);
	if(msg != GAME_SUCCESS && msg != GAME_FAILED) printf("ERROR IN chessPlayCom\n"); //toDelete

	//execute pawn promotion
	Piece* movingPiece = getPieceOnBoard(game, move[1]);
	if(needPromoting(movingPiece)){
		movingPiece->type = typeValue; // promotion

		//adding to history
		ChessMove* move = ChessArrayListGetFirst(game->LastMoves);
		if(ChessArrayListRemoveFirst(game->LastMoves) != Chess_ARRAY_LIST_SUCCESS) return GAME_FAILED;
		move->wasPromoted = true;
		move->piece->type = typeValue;
		ChessArrayListAddFirst(game->LastMoves, move);
	}
	free(move);
	return msg;
}

void printComMove(ChessGame* game,Location* move){
	printf("Computer: move %s at ",getPieceString(getPieceOnBoard(game, move[1]), true));
	printLoc(move[0]);
	printf(" to ");
	printLoc(move[1]);
	printf("\n");

}
