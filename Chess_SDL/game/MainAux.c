/*
 * MainAux.c
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: ido abulafya
 */
#include "MainAux.h"

GAME_MESSAGE chessPlayCom(ChessGame* game,bool consoleMode){
	Location* move;
	PieceType typeValue = PAWN;
	PieceType* type = &typeValue;
	move = chessMinimaxSuggestMove(game,game->gameDifficulty,type);
	if(move == NULL) return GAME_FAILED;
	GAME_MESSAGE msg = playMove(game, move[0], move[1], false);
	if(msg == GAME_SUCCESS && consoleMode) printComMove(game,move);
	if(msg != GAME_SUCCESS && msg != GAME_FAILED) printf("ERROR IN chessPlayCom\n"); //toDelete

	//execute pawn promotion
	Piece* movingPiece = getPieceOnBoard(game, move[1]);
	if(((movingPiece->color == WHITE && move[1].row == 7) || (movingPiece->color == BLACK && move[1].row == 0)) && movingPiece->type == PAWN)
		movingPiece->type = *type;
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
