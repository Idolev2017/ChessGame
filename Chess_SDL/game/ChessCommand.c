/*
 *  * ChessCommand.c
 *
 *  Created on: 24 баев„ 2017
 *      Author: ido abulafya
 */
#include "ChessCommand.h"


ChessCommand ChessCommandParser(const char* str){
	ChessCommand command;
	command.type = INVALID_LINE_COMMAND;
	command.filePath = NULL;
	int num = 1;
	int* numOfwords = &num;
	char* words[MAX_PLAY_COMMAND+1];
	GAME_MESSAGE msg = readMaxWords(words, str, 4, numOfwords);
	if(msg == GAME_FAILED){  //mallocHandling
		freeArray(words, *numOfwords);
		command.type = FAILED_COMMAND;
		return command;
	}
	if(msg == GAME_INVALID_ARGUMENT){
		freeArray(words, *numOfwords);
		return command;
	}
	if (strcmp(words[0],"move") == 0 && *numOfwords == 4 && strcmp(words[2],"to") == 0){
		if(isRepresentLocation(words[1]) && isRepresentLocation(words[3])) {
			command.src = parseLocation(words[1]);
			command.dest = parseLocation(words[3]);
			command.type = MOVE_PIECE_COMMAND;
		}
	}
	else if (strcmp(words[0],"get_moves") == 0 && *numOfwords == 2){
		if(isRepresentLocation(words[1])){ ;
		command.src =  parseLocation(words[1]);
		command.type = GET_MOVES_COMMAND;
		}
	}
	else if(strcmp(words[0],"undo") == 0 && *numOfwords == 1){
		command.type = UNDO_MOVE_COMMAND;
	}
	else if(strcmp(words[0],"save") == 0  && *numOfwords == 2){
		command.filePath = words[1];
		command.type = SAVE_COMMAND;
	}
	else if(strcmp(words[0],"reset") == 0 && *numOfwords == 1)
		command.type = RESET_COMMAND;
	else if(strcmp(words[0],"quit") == 0 && *numOfwords == 1)
		command.type = QUIT_COMMAND;
	else
		command.type = INVALID_LINE_COMMAND;
	freeArray(words, *numOfwords);
	return command;
}

ChessCommand createChessCommand(COMMAND_TYPE type, Location src, Location dest, char* filePath){
	ChessCommand cmd;
	cmd.type = type;
	cmd.src = src;
	cmd.dest = dest;
	cmd.filePath = filePath;
	return cmd;
}

