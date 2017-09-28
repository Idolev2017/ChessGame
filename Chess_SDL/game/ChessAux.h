/*
 * ChessAux.h
 *
 *  Created on: 28 баев„ 2017
 *      Author: ido abulafya
 */

#ifndef CHESSAUX_H_
#define CHESSAUX_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef enum game_message_t {
	GAME_INVALID_MOVE,
	GAME_INVALID_PIECE,
	GAME_INVALID_POSITION,
	GAME_INVALID_ARGUMENT,
	GAME_NO_HISTORY,
	GAME_SUCCESS,
	GAME_NORMAL,
	GAME_QUITED,
	GAME_FAILED,
	PIECE_THREATENED,
	GAME_CASTLING
} GAME_MESSAGE;

typedef enum {
	START_SETTINGS_MODE,
	QUIT_SETTINGS_MODE,
	NORMAL_SETTINGS_MODE,
	SETTINGS_MODE_FAILED
}SETTINGS_STATUS;

/**
 * Name: readMaxWords
 * Description:
 * gets the user input, checks if it's a legal command and if so it devides the user input to an array called words.
 * maxSize is maximum number of words that can be in a legal command.
 * numOfWords will hold the number of readen words from the user input.
 * afterwords, is returns the appropriate GAME_MESSAGE
 */
GAME_MESSAGE readMaxWords(char** words,const char* str, int maxSize, int* numOfWords);
/**
 * Name: freeArray
 * Description:
 * frees all the array's words, in size size, objects.
 */
void freeArray(char** words,int size);
/**
 * print the massage that malloc has failed.
 */
void printMallocError();

#endif /* CHESSAUX_H_ */
