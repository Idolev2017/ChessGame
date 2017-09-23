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
#define MAX_LINE 1024

typedef enum {
	UNDO_MOVE_COMMAND,
	MOVE_PIECE_COMMAND,
	GET_MOVES_COMMAND,
	SAVE_COMMAND,
	QUIT_COMMAND,
	RESET_COMMAND,
	INVALID_LINE_COMMAND,
	FAILED_COMMAND
} COMMAND_TYPE;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	COMMAND_TYPE type;
	Location src;
	Location dest;
	char* filePath;
} ChessCommand;


ChessCommand ChessCommandParser(const char* str);

#endif /* CHESSCOMMAND_H_ */
