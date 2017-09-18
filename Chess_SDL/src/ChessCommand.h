/*
 * ChessCommand.h
 *
 *  Created on: 24 баев„ 2017
 *      Author: ido abulafya
 */

#ifndef CHESSCOMMAND_H_
#define CHESSCOMMAND_H_
#define MAX_PLAY_COMMAND 4
#include "ChessMove.h"
#include "ChessAux.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef enum {
	UNDO_MOVE,
	MOVE_PIECE,
	GET_MOVES,
	SAVE,
	QUIT,
	RESET,
	INVALID_LINE,
	FAILED
} COMMAND_TYPE;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	COMMAND_TYPE type;
	Location src;
	Location dest;
	char* filePath;
} ChessCommand;


ChessCommand ChessCommandParser(const char* str);

ChessCommand createChessCommand(COMMAND_TYPE type, Location src, Location dest, char* filePath);


#endif /* CHESSCOMMAND_H_ */
