#include "SPTicTacToe.h"
#include <assert.h>
#include <stdlib.h>

bool isValidEntry(int row, int col) {
	if (row < 0 || row > SP_N_ROWS-1 || col < 0 || col > SP_N_COLUMNS-1) {
		return false;
	}
	return true;
}

char nextPlayer(char currentPlayer) {
	assert(currentPlayer== SP_PLAYER_1_SYMBOL|| currentPlayer== SP_PLAYER_2_SYMBOL);
	if (currentPlayer == SP_PLAYER_1_SYMBOL) {
		return SP_PLAYER_2_SYMBOL;
	}
	return SP_PLAYER_1_SYMBOL;
}

SPTicTacToe* spTicTacToeCreate() {
	SPTicTacToe* res = (SPTicTacToe*) malloc(sizeof(SPTicTacToe));
	if (res == NULL ) {
		return NULL ;
	}
	for (int i = 0; i < SP_N_ROWS; i++) {
		for (int j = 0; j < SP_N_COLUMNS; j++) {
			res->board[i][j] = SP_EMPTY_ENTRY;
		}
	}
	res->currentPlayer = SP_PLAYER_1_SYMBOL;
	return res;
}

void spTicTacToeDestroy(SPTicTacToe* src) {
	if (!src) {
		return;
	}
	free(src);
}

void spTicTacToeSetMove(SPTicTacToe* src, int row, int col) {
	if (src == NULL || !isValidEntry(row, col)) {
		return;
	}
	if (src->board[row][col] == SP_EMPTY_ENTRY) {
		src->board[row][col] = src->currentPlayer;
		src->currentPlayer = nextPlayer(src->currentPlayer);
	}
}

bool spTicTacToeIsGameOver(SPTicTacToe* src) {
	if (!src) {
		return true;
	}
	for (int i = 0; i < SP_N_ROWS; i++) {
		for (int j = 0; j < SP_N_COLUMNS; j++) {
			if (src->board[i][j] == SP_EMPTY_ENTRY) {
				return false;
			}
		}
	}
	return true;
}

char spTicTacToeCheckWinner(SPTicTacToe* src) {
	if (!src) {
		return '\0';
	}
	if (src->board[0][0] != SP_EMPTY_ENTRY
			&& src->board[0][0] == src->board[1][1]
			&& src->board[1][1] == src->board[2][2]) {
		return src->board[0][0];
	}
	if (src->board[0][2] != SP_EMPTY_ENTRY
			&& src->board[0][2] == src->board[1][1]
			&& src->board[1][1] == src->board[2][0]) {
		return src->board[0][2];
	}
	//horizontal
	for (int i = 0; i < SP_N_ROWS; i++) {
			char prev = src->board[i][0];
			if (prev == SP_EMPTY_ENTRY) {
				continue;
			}
			for (int j = 0; j < SP_N_COLUMNS; j++) {
				if(src->board[i][j]!=prev){
					break;
				}
				if(SP_N_COLUMNS-1==j){
					return prev;
				}
			}
		}
	//vertical
	for (int i = 0; i < SP_N_ROWS; i++) {
		char prev = src->board[0][i];
		if (prev == SP_EMPTY_ENTRY) {
			continue;
		}
		for (int j = 0; j < SP_N_COLUMNS; j++) {
			if(src->board[j][i]!=prev){
				break;
			}
			if(SP_N_COLUMNS-1==j){
				return prev;
			}
		}
	}
	return SP_EMPTY_ENTRY;
}

