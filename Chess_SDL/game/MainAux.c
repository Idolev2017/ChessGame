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

	move = chessMinimaxSuggestMove(game,game->gameDifficulty,&typeValue);
	if(move == NULL) return GAME_FAILED;

	GAME_MESSAGE msg = playMove(game, move[0], move[1], false);

	if(msg == GAME_SUCCESS && consoleMode)
		printComMove(game,move);

	//castling by computer.
	else if(msg == GAME_CASTLING && consoleMode){
		Location rookLoc = move[0].col < move[1].col ? createLocation(move[0].row, RIGHT_ROOK_COL) :
				createLocation(move[0].row, LEFT_ROOK_COL);
		printf("Computer: castle King at <%d,%c> and Rook at <%d,%c>\n",
				move[0].row + 1, move[0].col + 'A', rookLoc.row + 1,rookLoc.col + 'A');
		msg = GAME_SUCCESS;
	}

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
	GAME_STATUS status = printWinner(game);
	if(status == CHECKMATE || status == TIE) msg = GAME_QUITED;
	return msg;
}

void printComMove(ChessGame* game,Location* move){
	printf("Computer: move %s at ",getPieceString(getPieceOnBoard(game, move[1]), true));
	printLoc(move[0]);
	printf(" to ");
	printLoc(move[1]);
	printf("\n");

}

