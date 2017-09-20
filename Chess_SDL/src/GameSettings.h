/*
 * GameSetting.h
 *
 *  Created on: 27 баев„ 2017
 *      Author: ido abulafya
 */
#ifndef GAMESETTING_H_
#define GAMESETTING_H_

#define MAX_SETTING_COMMAND 2
#define GAME_N_ROWS 8
#define GAME_N_COLUMNS 8
#define MAX_LEN 1024
#define GAME_EMPTY_ENTRY ' '
#define HISTORY_SIZE 6
#define DEFAULT_DIFFICULTY 2
#define DEFAULT_GAME_MODE 1
#define DEFAULT_USER_COLOR 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ChessArrayList.h"
#include "ChessCommand.h"


typedef struct game_t {
	Piece* gameBoard[GAME_N_ROWS][GAME_N_COLUMNS];
	Color currentPlayer;
	ChessArrayList* LastMoves;
	unsigned int gameDifficulty;
	int gameMode;
	Color userColor;
	Piece* whiteKing;
	Piece* blackKing;
} ChessGame;


typedef enum {
	TIE,
	CHECKMATE,
	NORMAL,
	CHECK
} GAME_STATUS;

Setting_Status gameUpdateSetting(ChessGame* game);

GAME_MESSAGE gameSettingMode(ChessGame* game);

Setting_Status gameChangingSettings(ChessGame* game,char** words,int numOfWords);

void simpleSettingsSetter(ChessGame* game, int difficulty,int gameMode,int userColor);

ChessGame* gameCreate(int historySize, bool consoleMode);

GAME_MESSAGE gameInitialization(ChessGame* game,bool toClear,int historySize);

ChessGame* gameCopy(ChessGame* game);

GAME_MESSAGE gameRestart(ChessGame* game);

void destroyInnerGame(ChessGame* game);

void gameDestroy(ChessGame* game);

void gamePrintBoard(ChessGame* game);

Color GetCurrentPlayer(ChessGame* game);

Setting_Status loadGame(ChessGame* game, char* filepath,bool* loaded);

Piece* letterToPieceGenerator(char c, int row, int col);
#endif /* GAMESETTING_H_ */
