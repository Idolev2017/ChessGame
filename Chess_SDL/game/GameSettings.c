/*
 * GameSettings.c
 *
 *  Created on: 27 баев„ 2017
 *      Author: ido abulafya
 */
#include "GameSettings.h"

GAME_MESSAGE gameSettingMode(ChessGame* game){
	Setting_Status status = gameUpdateSetting(game);
	if(status == START_setting) return GAME_SUCCESS;
	else if(status == QUIT_setting) {
		printf("Exiting...\n");
		return GAME_QUITED;
	}
	else if(status == SETTING_FAILED)return GAME_FAILED;
	return GAME_SUCCESS;
}

Setting_Status gameUpdateSetting(ChessGame* game){
	int num = 1;
	int* numOfWords = &num;
	char* words[MAX_SETTING_COMMAND+1];
	GAME_MESSAGE msg;
	Setting_Status status;
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	char* line = (char*) malloc(sizeof(char)*(MAX_LEN+1)); //mallocHandling
	if(line == NULL) {
		printMallocError();
		return SETTING_FAILED;
	}
	while(true){
		if (fgets(line, MAX_LEN, stdin) == NULL) {
			free(line);
			freeArray(words, *numOfWords);
			printMallocError();  //Error Handling
			return SETTING_FAILED;
		}
		msg = readMaxWords(words,line, 2, numOfWords);
		if(msg == GAME_FAILED){ //mallocHandling
			freeArray(words, *numOfWords);
			free(line);
			return SETTING_FAILED;
		}
		else if(msg == GAME_INVALID_ARGUMENT){
			printf("invalid command\n");
			continue;
		}
		status = gameChangingSettings(game,words,*numOfWords);
		if(status != NORMAL_SETTINGS) {
			free(line);
			freeArray(words, *numOfWords);
			return status;
		}
	}
}

Setting_Status gameChangingSettings(ChessGame* game,char** words,int numOfWords){
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
			return START_setting;
		}
		else if(strcmp(command,"quit") == 0){
			return QUIT_setting;
		}
		else{
			printf("Invalid command\n");
			return NORMAL_SETTINGS;
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
			bool flag = false;
			bool* loaded = &flag;
			return loadGame(game, words[1],loaded);
		}
		else{
			printf("Invalid command\n");
			return NORMAL_SETTINGS;
		}
	}
	else printf("Invalid command\n");
	return NORMAL_SETTINGS;
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
	game->LastMoves = NULL;
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
		game->gameBoard[1][i] = pieceCreate(PAWN,1,1,i);
		game->gameBoard[6][i] = pieceCreate(PAWN,0,6,i);
	}
	//creating the ROOKS
	game->gameBoard[0][0] = pieceCreate(ROOK,1,0,0);
	game->gameBoard[0][7] = pieceCreate(ROOK,1,0,7);
	game->gameBoard[7][0] = pieceCreate(ROOK,0,7,0);
	game->gameBoard[7][7] = pieceCreate(ROOK,0,7,7);
	//creating the KNIGHTS
	game->gameBoard[0][1] = pieceCreate(KNIGHT,1,0,1);
	game->gameBoard[0][6] = pieceCreate(KNIGHT,1,0,6);
	game->gameBoard[7][1] = pieceCreate(KNIGHT,0,7,1);
	game->gameBoard[7][6] = pieceCreate(KNIGHT,0,7,6);
	//creating the BISHOPS
	game->gameBoard[0][2] = pieceCreate(BISHOP,1,0,2);
	game->gameBoard[0][5] = pieceCreate(BISHOP,1,0,5);
	game->gameBoard[7][2] = pieceCreate(BISHOP,0,7,2);
	game->gameBoard[7][5] = pieceCreate(BISHOP,0,7,5);
	//creating the Royalists
	game->gameBoard[0][4] = pieceCreate(KING,1,0,4);
	game->gameBoard[0][3] = pieceCreate(QUEEN,1,0,3);
	game->gameBoard[7][4] = pieceCreate(KING,0,7,4);
	game->gameBoard[7][3] = pieceCreate(QUEEN,0,7,3);

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

Setting_Status loadGame(ChessGame* game, char* filePath,bool* loaded){
	FILE* file = fopen(filePath, "r");
	if(file == NULL){
		printf("Error: File doesn't exist or cannot be opened\n");
		*loaded = false;
		return NORMAL_SETTINGS;
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
	gameDestroy(game);
	gameCreate(HISTORY_SIZE,false);
	game->currentPlayer = currentPlayer;
	game->gameMode = gameMode;
	game->gameDifficulty = difficulty;
	game->userColor = userColor;
	ChessArrayListDestroy(game->LastMoves);
	game->LastMoves = ChessArrayListCreate(HISTORY_SIZE);
	fscanf(file, "\t<board>\n");
	for(int i = 7; 0 <= i; --i){
		fscanf(file, "\t\t<row_%d>", &temp);
		for(int j = 0; j < 8; ++j){
			pieceDestroy(game->gameBoard[i][j]);
			game->gameBoard[i][j]=letterToPieceGenerator(fgetc(file),i,j);
			Piece* p = game->gameBoard[i][j];
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
		*loaded = false;
		return NORMAL_SETTINGS;
	}
	*loaded = true;
	return NORMAL_SETTINGS;
}

Piece* letterToPieceGenerator(char c, int row, int col){
	if(c == '_')
		return NULL;
	char d = c;
	Color color = WHITE;
	if(c < 'a'){
		d = c + 32;
		color = BLACK;
	}
	switch(d){
	case 'r':
		return pieceCreate(ROOK,color,row,col);
	case 'k':
		return pieceCreate(KING,color,row,col);
	case 'm':
		return pieceCreate(PAWN,color,row,col);
	case 'q':
		return pieceCreate(QUEEN,color,row,col);
	case 'b':
		return pieceCreate(BISHOP,color,row,col);
	case 'n':
		return pieceCreate(KNIGHT,color,row,col);
	default:
		return NULL;
	}
}
