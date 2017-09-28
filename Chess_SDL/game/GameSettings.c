/*
 * GameSettings.c
 *
 *  Created on: 27 баев„ 2017
 *      Author: ido abulafya
 */
#include "GameSettings.h"

GAME_MESSAGE gameSettingMode(ChessGame* game){
	SETTINGS_STATUS status = gameUpdateSetting(game);
	if(status == START_SETTINGS_MODE) return GAME_SUCCESS;
	else if(status == QUIT_SETTINGS_MODE) {
		printf("Exiting...\n");
		return GAME_QUITED;
	}
	else if(status == SETTINGS_MODE_FAILED)return GAME_FAILED;
	return GAME_SUCCESS;
}

SETTINGS_STATUS gameUpdateSetting(ChessGame* game){
	int numOfWords = 1;
	char* words[MAX_SETTING_COMMAND+1];
	for(int i = 0; i < MAX_SETTING_COMMAND+1; ++i){ //initialize
		words[i] = NULL;
	}

	GAME_MESSAGE msg;
	SETTINGS_STATUS status;
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	char* line = (char*) malloc(sizeof(char)*(MAX_LEN+1)); //mallocHandling
	if(line == NULL) {
		printMallocError();
		return SETTINGS_MODE_FAILED;
	}
	while(true){
		freeArray(words, MAX_SETTING_COMMAND+1);
		if (fgets(line, MAX_LEN, stdin) == NULL) break;

		msg = readMaxWords(words,line, 2, &numOfWords);
		if(msg == GAME_FAILED) break;

		else if(msg == GAME_INVALID_ARGUMENT){
			printf("invalid command\n");
			continue;
		}
		status = gameChangingSettings(game,words,numOfWords);
		if(status != NORMAL_SETTINGS_MODE) {
			free(line);
			freeArray(words, numOfWords);
			return status;
		}
	}
	free(line);
	freeArray(words, MAX_SETTING_COMMAND+1);
	return SETTINGS_MODE_FAILED;
}

SETTINGS_STATUS gameChangingSettings(ChessGame* game,char** words,int numOfWords){
	char* command = words[0];
	if(numOfWords == 1){
		if(strcmp(command,"print_setting") == 0){
			printf("SETTINGS:\n");
			printf("GAME_MODE: %d\n",game->gameMode);
			if(game->gameMode == 1){
				printf("DIFFICULTY_LVL: %d\n",game->gameDifficulty);
				char* color = (game->userColor == 0) ? "BLACK" : "WHITE";
				printf("USER_CLR: %s\n",color);
			}
		}
		else if(strcmp(command,"default") == 0){
			game->gameDifficulty = DEFAULT_DIFFICULTY;
			game->gameMode = DEFAULT_GAME_MODE;
			game->userColor = DEFAULT_USER_COLOR;
		}
		else if(strcmp(command,"start") == 0){
			return START_SETTINGS_MODE;
		}
		else if(strcmp(command,"quit") == 0){
			return QUIT_SETTINGS_MODE;
		}
		else{
			printf("Invalid command\n");
			return NORMAL_SETTINGS_MODE;
		}
	}
	else if(numOfWords == 2){
		if(strcmp(command,"difficulty") == 0){
			if(strlen(words[1]) != 1) printf("Wrong difficulty level. The value should be between 1 to 5\n");
			else if('1' <= words[1][0] && words[1][0] <= '4'){
				game->gameDifficulty = words[1][0] - '0';
			}
			else if(words[1][0] == '5') printf("Expert level not supported, please choose a value between 1 to 4:\n");
			else printf("Wrong difficulty level. The value should be between 1 to 5\n");
		}
		else if(strcmp(command,"user_color") == 0){
			if (strcmp(words[1],"0") == 0) game->userColor = 0;
			else if (strcmp(words[1],"1") == 0) game->userColor = 1;
		}

		else if(strcmp(command,"game_mode") == 0){
			if (strcmp(words[1],"1") == 0) {
				game->gameMode = 1;
				printf("Game mode is set to 1 player\n");
			}
			else if (strcmp(words[1],"2") == 0) {
				game->gameMode = 2;
				printf("Game mode is set to 2 players\n");
			}
			else printf("Wrong game mode\n");
		}
		else if(strcmp(command,"load") == 0){
			loadGame(game, words[1]);
			return NORMAL_SETTINGS_MODE;
		}
		else{
			printf("Invalid command\n");
			return NORMAL_SETTINGS_MODE;
		}
	}
	else printf("Invalid command\n");
	return NORMAL_SETTINGS_MODE;
}

void simpleSettingsSetter(ChessGame* game, int difficulty,int gameMode,int userColor){
	if (game == NULL) return;
	game->gameDifficulty = difficulty;
	game->gameMode = gameMode;
	game->userColor = userColor;
}

ChessGame* gameCreate(int historySize, bool consoleMode){
	ChessGame* game = (ChessGame*)malloc(sizeof(ChessGame)); //mallocHandling
	if(game == NULL) {
		printMallocError();
		return NULL;
	}

	if(gameInitialization(game,false,historySize) != GAME_SUCCESS) {
		free(game);
		return NULL;
	}
	if(consoleMode){
		if(gameSettingMode(game) != GAME_SUCCESS) {
			gameDestroy(game);
			return NULL;
		}
	}
	return game;
}

GAME_MESSAGE gameInitialization(ChessGame* game,bool toClear,int historySize){
	if(historySize < 0 || game == NULL) return GAME_INVALID_ARGUMENT;
	game->currentPlayer = WHITE;
	game->gameDifficulty = DEFAULT_DIFFICULTY;
	game->gameMode = DEFAULT_GAME_MODE;
	game->userColor = DEFAULT_USER_COLOR;
	if(toClear){
		destroyInnerGame(game);
	}
	game->LastMoves = ChessArrayListCreate(historySize); //mallocHandling
	if(game->LastMoves == NULL){
		printMallocError();
		return GAME_FAILED;
	}
	for(int i=0; i<8;i++)
	{
		game->gameBoard[1][i] = pieceCreate(PAWN,1,1,i,0);
		game->gameBoard[6][i] = pieceCreate(PAWN,0,6,i,0);
	}
	//creating the ROOKS
	game->gameBoard[0][0] = pieceCreate(ROOK,1,0,0,0);
	game->gameBoard[0][7] = pieceCreate(ROOK,1,0,7,0);
	game->gameBoard[7][0] = pieceCreate(ROOK,0,7,0,0);
	game->gameBoard[7][7] = pieceCreate(ROOK,0,7,7,0);
	//creating the KNIGHTS
	game->gameBoard[0][1] = pieceCreate(KNIGHT,1,0,1,0);
	game->gameBoard[0][6] = pieceCreate(KNIGHT,1,0,6,0);
	game->gameBoard[7][1] = pieceCreate(KNIGHT,0,7,1,0);
	game->gameBoard[7][6] = pieceCreate(KNIGHT,0,7,6,0);
	//creating the BISHOPS
	game->gameBoard[0][2] = pieceCreate(BISHOP,1,0,2,0);
	game->gameBoard[0][5] = pieceCreate(BISHOP,1,0,5,0);
	game->gameBoard[7][2] = pieceCreate(BISHOP,0,7,2,0);
	game->gameBoard[7][5] = pieceCreate(BISHOP,0,7,5,0);
	//creating the Royalists
	game->gameBoard[0][4] = pieceCreate(KING,1,0,4,0);
	game->gameBoard[0][3] = pieceCreate(QUEEN,1,0,3,0);
	game->gameBoard[7][4] = pieceCreate(KING,0,7,4,0);
	game->gameBoard[7][3] = pieceCreate(QUEEN,0,7,3,0);

	game->whiteKing = game->gameBoard[0][4];
	game->blackKing = game->gameBoard[7][4];

	//initialize to NULL
	for(int i = 2; i <= 5; ++i){
		for(int j = 0; j < 8; ++j){
			game->gameBoard[i][j] = NULL;
		}
	}
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 8; ++j){
			if(game->gameBoard[i][j] == NULL || game->gameBoard[7-i][j] == NULL){ //mallocHandling
				destroyInnerGame(game);
				printMallocError();
				return GAME_FAILED;
			}
		}
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE gameRestart(ChessGame* game){
	GAME_MESSAGE msg = gameInitialization(game, true, HISTORY_SIZE);
	if(msg != GAME_SUCCESS) return msg;
	return gameSettingMode(game);
}

ChessGame* gameCopy(ChessGame* game) {
	if(game == NULL) return NULL;
	ChessGame* cpy = (ChessGame*) malloc(sizeof(ChessGame));
	if(cpy == NULL) {
		printMallocError();
		return NULL;
	}
	Piece* tmpPiece = NULL;
	if (gameInitialization(cpy, false,game->LastMoves->maxSize) != GAME_SUCCESS){
		free(cpy);
		return NULL;
	}
	cpy->gameMode = game->gameMode;
	cpy->gameDifficulty = game->gameDifficulty;
	cpy->userColor = game->userColor;
	cpy->currentPlayer = game->currentPlayer;
	destroyInnerGame(cpy);
	cpy->LastMoves = ChessArrayListCopy(game->LastMoves); //mallocHandling
	if(cpy->LastMoves == NULL){
		free(cpy);
		return NULL;
	}
	for(int j = 0; j < GAME_N_ROWS; ++j){
		for(int i = 0; i < GAME_N_COLUMNS; ++i){
			cpy->gameBoard[i][j] = copyPiece(game->gameBoard[i][j]);
			if(cpy->gameBoard[i][j] == NULL && game->gameBoard[i][j] != NULL){ //mallocHandling
				gameDestroy(cpy);
				return NULL;
			}
			tmpPiece = cpy->gameBoard[i][j];
			if(tmpPiece != NULL && tmpPiece->type == KING){
				if(tmpPiece->color == WHITE) cpy->whiteKing = cpy->gameBoard[i][j];
				else cpy->blackKing = cpy->gameBoard[i][j];
			}
		}
	}
	return cpy;
}

void destroyInnerGame(ChessGame* game) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			pieceDestroy(game->gameBoard[i][j]);
			game->gameBoard[i][j] = NULL;
		}
	}
	game->whiteKing = NULL;
	game->blackKing = NULL;
	ChessArrayListDestroy(game->LastMoves);
	game->LastMoves = NULL;
}

void gameDestroy(ChessGame* game){
	if (game != NULL){
		destroyInnerGame(game);
		free(game);
	}
}

void gamePrintBoard(ChessGame* game){
	for(int i = 7; 0 <= i;--i){
		printf("%d| ", i + 1);
		for(int j = 0; j < 8; ++j){
			printf("%s", getPieceString(game->gameBoard[i][j],false));
			printf(" ");
		}
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");
	return;

}

Color GetCurrentPlayer(ChessGame* game){
	return game->currentPlayer;
}

bool loadGame(ChessGame* game, char* filePath){
	FILE* file = fopen(filePath, "r");
	int returnedValue = 0;
	Piece* tempP = NULL;
	Piece* p = NULL;
	if(file == NULL){
		printf("Error: File doesn't exist or cannot be opened\n");
		return false;
	}
	int currentPlayer, gameMode, difficulty, userColor;
	int temp;
	fscanf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fscanf(file, "<game>\n\t<current_turn>%d</current_turn>\n", &currentPlayer);
	fscanf(file, "\t<game_mode>%d</game_ mode>\n", &gameMode);
	if(gameMode == 1) {
		fscanf(file, "\t<difficulty>%d</difficulty>\n", &difficulty);
		fscanf(file, "\t<user_color>%d</user_color>\n", &userColor);
	}
	simpleSettingsSetter(game, difficulty, gameMode, userColor);
	game->currentPlayer = currentPlayer;

	ChessArrayListDestroy(game->LastMoves);
	game->LastMoves = ChessArrayListCreate(HISTORY_SIZE);

	fscanf(file, "\t<board>\n");
	for(int i = 7; 0 <= i; --i){
		fscanf(file, "\t\t<row_%d>", &temp);
		for(int j = 0; j < 8; ++j){
			pieceDestroy(game->gameBoard[i][j]);
			returnedValue = fgetc(file);
			if(returnedValue == '_'){
				game->gameBoard[i][j] = NULL;
			}
			else{
				tempP = letterToPieceGenerator(returnedValue,i,j);
				if(tempP == NULL)
					return false;
				game->gameBoard[i][j] = tempP;
			}
			p = game->gameBoard[i][j];
			//pointers to the Kings
			if(p != NULL && p->type == KING){
				if(p->color == BLACK)
					game->blackKing = p;
				else
					game->whiteKing = p;
			}
		}
		fscanf(file, "</row_%d>\n", &temp);
	}
	fscanf(file, "\t</board>\n</game>");
	//closing the FILE
	if(fclose(file) != 0)
	{
		printf("Error: File cannot be closed\n");
		return false;
	}
	return true;
}

Piece* letterToPieceGenerator(char c, int row, int col){
	char d = c;
	Color color = WHITE;
	if(c < 'a'){
		d = c + 32;
		color = BLACK;
	}
	switch(d){
	case 'r':
		return pieceCreate(ROOK,color,row,col,0);
	case 'k':
		return pieceCreate(KING,color,row,col,0);
	case 'm':
		return pieceCreate(PAWN,color,row,col,0);
	case 'q':
		return pieceCreate(QUEEN,color,row,col,0);
	case 'b':
		return pieceCreate(BISHOP,color,row,col,0);
	case 'n':
		return pieceCreate(KNIGHT,color,row,col,0);
	default:
		return NULL;
	}
}
