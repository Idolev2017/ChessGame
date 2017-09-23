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
	PIECE_THREATENED
} GAME_MESSAGE;

typedef enum {
	START_SETTINGS_MODE,
	QUIT_SETTINGS_MODE,
	NORMAL_SETTINGS_MODE,
	SETTINGS_MODE_FAILED
}SETTINGS_STATUS;


GAME_MESSAGE readMaxWords(char** words,const char* str, int maxSize, int* numOfWords);

void freeArray(char** words,int size);

void printMallocError();

#endif /* CHESSAUX_H_ */
