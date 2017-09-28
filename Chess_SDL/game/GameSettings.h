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

/**
 * Struct: ChessGame
 * Description:
 * holds detailes about a chess game.
 * two-dimensioned array gameBoard which contains all the pieces.
 * currentPlayer is a dynamic Color ocject that symbols which of the player's turn is it.
 * LastMoves is a ChessArraylist object which contains the last moves who were took in the game.
 * gameMode is an integer in the range 1-2.
 * gameDifficulty is an integer in the range 1-4, only relevant if gameMode=1.
 * userColor is Color object the symbols what is the color of the user, only relevant if gameMode=1.
 * whiteKing and blackKing are pointers to the white king piece and to the black piece respectively.
 */
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
/**
 * Name: gameUpdateSetting
 * Description:
 * A functions that recieves an input from the user,
 * if the input is a legal settings command then the settings will be updated after.
 * returns a SETTINGS_STATUS that gives details what happened in the function call
 * and can be on of: START_SETTINGS_MODE, QUIT_SETTINGS_MODE, NORMAL_SETTINGS_MODE and SETTINGS_MODE_FAILED.
 */
SETTINGS_STATUS gameUpdateSetting(ChessGame* game);
/**
 * Name: gameSettingMode
 * Description:
 * A shell function to the previous function gameUpdateSetting
 * that determines if the game continues or has to be stopped due to gameUpdateSetting
 * return value.
 */
GAME_MESSAGE gameSettingMode(ChessGame* game);
/**
 * Name: gameChangingSettings
 * Description:
 * A function that manages all the user inputs in setting mode.
 * possible legal input from the user can be: game_mode set, difficulty set, user_color set
 * load game, default, print_setting, start and quit.
 * returns in what settings mode the game is and can be one of:
 *	START_SETTINGS_MODE, QUIT_SETTINGS_MODE, NORMAL_SETTINGS_MODE and SETTINGS_MODE_FAILED
 */
SETTINGS_STATUS gameChangingSettings(ChessGame* game,char** words,int numOfWords);
/**
 * Name: simpleSettingsSetter
 * Description:
 * if the game != NULL then it sets the game settings to the arguments that were given.
 * otherwise it does nothing.
 */
void simpleSettingsSetter(ChessGame* game, int difficulty,int gameMode,int userColor);
/**
 * Name: gameCreate
 * Description:
 * Creates a ChessGame object, initializes it and its fields, allocated a memory to it.
 * and if the game is in console Mode
 * then it will also call to gameSettingMode function in order to
 * determine the game settings.
 * returns a pointer to the new ChessGame object that was created.
 */
ChessGame* gameCreate(int historySize, bool consoleMode);
/**
 * Name: gameInitialization
 * Description:
 * initializes the game and its fields: gameBoard, lastMoves array in size
 * historySize,currentPlayer = WHITE.
 * gameMode, gameDifficulty and userColor get the default pre-defined values.
 * returns a GAME_MESSAGE about the success of the initialization.
 */
GAME_MESSAGE gameInitialization(ChessGame* game,bool toClear,int historySize);
/**
 * Name: gameCopy
 * Description:
 * copies all the ChessGame game fields to a new ChessGame object
 * and returns it.
 */
ChessGame* gameCopy(ChessGame* game);
/**
 * Name: gameRestart
 * Description:
 * Initializes an exiting ChessGame object and its fields.
 * it also calls to gameSettingMode function in order to
 * determine the new game settings.
 * returns a GAME_MESSAGE about the success of the initialization.
 */
GAME_MESSAGE gameRestart(ChessGame* game);
/**
 * Name: destroyInnerGame
 * Description:
 * Destroys all the gameBoard pieces and also the lastMoves ChessArrayList.
 * initializes all the gameBoard cells, whiteKing, BlackKing and lastMoves to NULL.
 */
void destroyInnerGame(ChessGame* game);
/**
 * Name: gameDestroy
 * Description:
 * if game != NULL it calls destroyInnerGame and also frees game instance allocated memory.
 */
void gameDestroy(ChessGame* game);
/**
 * Name: gamePrintBoard
 * Description:
 * prints the current gameBoard to the console.
 */
void gamePrintBoard(ChessGame* game);
/**
 * Name: GetCurrentPlayer
 * Description:
 * returns which player's turn is it, black or white.
 */
Color GetCurrentPlayer(ChessGame* game);
/**
 * Name: loadGame
 * Description:
 * if filePath leads to an exiting ChessGame who was saved in pre-agreed
 * format then it parses it and set it to the ChessGame game object.
 * otherwise it prints appropriate error messages.
 */
bool loadGame(ChessGame* game, char* filepath);
/**
 * Name: letterToPieceGenerator
 * Description:
 * gets a char object and integer row and col and returns the
 * appropriate Piece which matches the char c.
 */
Piece* letterToPieceGenerator(char c, int row, int col);
#endif /* GAMESETTING_H_ */
