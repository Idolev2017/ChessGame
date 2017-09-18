#ifndef SPTICTACTOE_H_
#define SPTICTACTOE_H_
#include <stdbool.h>
#define NULL ((void *)0)
#define SP_N_ROWS 3
#define SP_N_COLUMNS 3
#define SP_PLAYER_1_SYMBOL 'X'
#define SP_PLAYER_2_SYMBOL 'O'
#define SP_EMPTY_ENTRY ' '

typedef struct{
	char board[SP_N_ROWS][SP_N_COLUMNS];
	char currentPlayer;
} SPTicTacToe;

SPTicTacToe* spTicTacToeCreate();
void spTicTacToeDestroy(SPTicTacToe* src);
void spTicTacToeSetMove(SPTicTacToe* src, int row, int col);
bool spTicTacToeIsGameOver(SPTicTacToe* src);
char spTicTacToeCheckWinner(SPTicTacToe* src);


#endif
