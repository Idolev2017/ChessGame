/*
 * ChessAux.c
 *
 *  Created on: 28 баев„ 2017
 *      Author: ido abulafya
 */

#include "ChessAux.h"

GAME_MESSAGE readMaxWords(char** words,const char* str, int maxSize, int* numOfWords){
	*numOfWords = 1;
	char* tmp;
	char* delim = " \t\r\n\v\f";
	char* line = (char*)malloc(sizeof(char)*(strlen(str)+1)); //mallocHandling
	if(line == NULL) {
		printMallocError();
		return GAME_FAILED;
	}
	int index = 1;
	strcpy(line,str);
	tmp = strtok(line,delim);
	if(tmp == NULL){
		free(line);
		return GAME_INVALID_ARGUMENT;
	}
	words[0] = (char*) malloc(strlen(tmp)*sizeof(char)+1); //mallocHandling
	if(words[0] == NULL) {
		free(line);
		printMallocError();
		return GAME_FAILED;
	}
	strcpy(words[0],tmp);
	for(; index < maxSize; ++index){
		tmp = strtok(NULL,delim);
		if(tmp == NULL){
			free(line);
			return GAME_SUCCESS;
		}
		words[index] = (char*) malloc(strlen(tmp)*sizeof(char)+1); //mallocHandling
		if(words[index] == NULL) {
			printMallocError();
			return GAME_FAILED;
		}
		strcpy(words[index],tmp);
		++(*numOfWords);
	}
	tmp = strtok(NULL,delim);
	free(line);
	if(tmp != NULL) return GAME_INVALID_ARGUMENT;
	return GAME_SUCCESS;
}

void freeArray(char** words,int size){
	for(int i = 0; i < size; ++i){
		free(words[i]);
	}
}

void printMallocError(){
	printf("ERROR: malloc has failed");
}

