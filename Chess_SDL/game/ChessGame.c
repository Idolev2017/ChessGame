#include "ChessGame.h"

Step createStep(Location dest, MoveClass class){
	Step step;
	step.dest = dest;
	step.class = class;
	return step;
}

GAME_MESSAGE setCommand(ChessGame* game, ChessCommand cmd){
	GAME_MESSAGE msg;
	Location possibleMoves[MAX_MOVES];
	int a = 0;
	int* actualSize = &a;
	switch(cmd.type){
	case UNDO_MOVE_COMMAND:
		msg = undoPrevMove(game,true);
		if(msg != GAME_SUCCESS) break;
		msg = undoPrevMove(game,true);
		break;

	case MOVE_PIECE_COMMAND:
		msg = playMove(game,cmd.src,cmd.dest,true);
		break;

	case GET_MOVES_COMMAND:
		msg = getAllMoves(game, cmd.src, possibleMoves, actualSize,true);
		Step* steps = distinguishMovesByPiece(game, possibleMoves,*actualSize, cmd.src);
		if(steps == NULL) msg = GAME_FAILED;
		else{
			printSteps(steps, *actualSize);
			free(steps);
		}
		break;

	case SAVE_COMMAND:
		saveGame(game,cmd.filePath);
		msg = GAME_SUCCESS;
		free(cmd.filePath);
		break;

	case QUIT_COMMAND:
		printf("Exiting...\n");
		msg = GAME_QUITED;
		break;

	case RESET_COMMAND:
		printf("Restarting...\n");
		return gameRestart(game);

	case INVALID_LINE_COMMAND:
		printf("INVALID_LINE\n");
		msg = GAME_SUCCESS;
		break;

	default:
		break;
	}
	if(msg == GAME_SUCCESS){
		if(cmd.type == SAVE_COMMAND || cmd.type == GET_MOVES_COMMAND) return GAME_NORMAL;
		else return GAME_SUCCESS;
	}
	return msg;
}

GAME_MESSAGE undoPrevMove(ChessGame* game,bool toPrint){
	if(game == NULL) return GAME_FAILED;
	if(game->gameMode == 2 && toPrint){
		printf("Undo command not available in 2 players mode\n");
		return GAME_INVALID_ARGUMENT;
	}
	if(ChessArrayListIsEmpty(game->LastMoves)) {
		if(toPrint){
			printf("Empty history, move cannot be undone\n");
		}
		return GAME_NO_HISTORY;
	}
	ChessMove* lastMove = ChessArrayListGetFirst(game->LastMoves);
	Chess_ARRAY_LIST_MESSAGE msg = ChessArrayListRemoveFirst(game->LastMoves);
	if(lastMove == NULL || msg != Chess_ARRAY_LIST_SUCCESS) { //Unknown Error
		chessMoveDestroy(lastMove);
		return GAME_FAILED;
	}
	if(toPrint){
		char* player = (game->currentPlayer == BLACK) ?  "white" : "black";
		printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",player,lastMove->newLoc.row+1,lastMove->newLoc.col + 'A',lastMove->prevLoc.row+1,lastMove->prevLoc.col + 'A');
	}

	simpleMovePiece(game, lastMove->newLoc, lastMove->prevLoc);
	setPieceOnBoard(game,lastMove->newLoc,copyPiece(lastMove->capturedPiece));
	if(lastMove->wasPromoted) getPieceOnBoard(game, lastMove->prevLoc)->type = PAWN;
	game->currentPlayer = 1 - game->currentPlayer;
	chessMoveDestroy(lastMove);
	return GAME_SUCCESS;
}

GAME_MESSAGE playMove(ChessGame* game, Location src, Location dest, bool userTurn){
	if(!isLegalLoc(src) || !isLegalLoc(dest)){
		if(userTurn) printf("Invalid position on the board\n");
		return GAME_INVALID_POSITION;
	}
	if(equalLocations(src, dest)){
		if(userTurn) printf("Illegal move\n");
		return GAME_INVALID_MOVE;
	}
	GAME_MESSAGE msg;
	ChessMove* move;
	bool promotionSucceed = false;
	Piece* movingPiece = getPieceOnBoard(game, src);
	Piece* destPiece = copyPiece(getPieceOnBoard(game, dest));
	if(movingPiece == NULL || (movingPiece->color != game->currentPlayer)){
		if(userTurn) printf("The specified position does not contain your piece\n");
		return GAME_INVALID_PIECE;
	}

	switch(movingPiece->type){
	case PAWN:
		msg = movePawn(game,movingPiece,dest,userTurn);
		if(movingPiece->type != PAWN) promotionSucceed = true;
		break;
	case BISHOP:
		msg = moveBishop(game, movingPiece, dest);
		break;
	case ROOK:
		msg = moveRook(game, movingPiece, dest);
		break;
	case KING:
		msg = moveKing(game,movingPiece,dest);
		break;
	case QUEEN:
		msg = moveQueen(game,movingPiece,dest);
		break;
	case KNIGHT:
		msg = moveKnight(game, movingPiece, dest);
		break;
	}
	if((msg == GAME_INVALID_MOVE || msg == PIECE_THREATENED) && userTurn){
		printf("Illegal move\n");
	}
	//adding the move to history
	else if(msg == GAME_SUCCESS){
		if((move = chessMoveCreate(movingPiece, src, dest, promotionSucceed, destPiece)) == NULL) return GAME_FAILED;
		if(ChessArrayListAddFirst(game->LastMoves,move) != Chess_ARRAY_LIST_SUCCESS) {
			pieceDestroy(destPiece);
			printf("ERROR: cannot add to array list\n");
			return GAME_FAILED; //Unknown Error
		}
		game->currentPlayer = 1 - game->currentPlayer; //changing the current player.
	}
	pieceDestroy(destPiece);
	return msg;
}

GAME_MESSAGE getAllMoves(ChessGame* game, Location loc,Location* possibleMoves, int* actualSize,bool userTurn){
	*actualSize = 0;
	if(!isLegalLoc(loc)){
		if(userTurn) printf("Invalid position on the board\n");
		return GAME_INVALID_ARGUMENT;
	}
	Piece* piece = getPieceOnBoard(game,loc);
	if(piece == NULL || (piece->color != game->currentPlayer)){
		if(userTurn) printf("The specified position does not contain your piece\n");
		return GAME_INVALID_ARGUMENT;
	}
	if(userTurn && (game->gameMode != 1|| (game->gameDifficulty != 1 && game->gameDifficulty != 2))){
		printf("Invalid command\n");
		return GAME_INVALID_ARGUMENT;
	}
	GAME_MESSAGE msg;
	switch(piece->type){
	case PAWN:
		msg = getAllMovesPawn(game,piece,possibleMoves,actualSize);
		break;
	case BISHOP:
		msg = getAllMovesBishop(game, piece,possibleMoves,actualSize);
		break;
	case ROOK:
		msg = getAllMovesRook(game, piece,possibleMoves,actualSize);
		break;
	case KING:
		msg = getAllMovesKing(game,piece,possibleMoves,actualSize);
		break;
	case QUEEN:
		msg = getAllMovesQueen(game,piece,possibleMoves,actualSize);
		break;
	case KNIGHT:
		msg = getAllMovesKnight(game, piece,possibleMoves,actualSize);
		break;
	}
	if(msg == GAME_FAILED) return msg;
	qsort(possibleMoves,*actualSize,sizeof(Location),*compareFunc);
	return msg;

}

GAME_MESSAGE getAllMovesPawn(ChessGame* game,Piece* piece,Location* possibleMoves, int* actualSize){
	Location pieceLoc = copyLocation(piece->loc);
	int addingRow = (piece->color == WHITE) ? 1 : -1;
	int addingDoubleJump = (piece->color == WHITE) ? 2 : -2;
	Location capturingLocLeft = createLocation(pieceLoc.row + addingRow,pieceLoc.col - 1);
	Location capturingLocRight = createLocation(pieceLoc.row + addingRow,pieceLoc.col + 1);
	Location regularJump = createLocation(pieceLoc.row + addingRow,pieceLoc.col);
	Location DoubleJump = createLocation(pieceLoc.row + addingDoubleJump,pieceLoc.col);

	if(isLegalLoc(capturingLocLeft) && getPieceOnBoard(game, capturingLocLeft) != NULL && getPieceOnBoard(game, capturingLocLeft)->color != piece->color){
		if(addMoveToArray(game,pieceLoc,capturingLocLeft,possibleMoves,actualSize) == GAME_FAILED) return GAME_FAILED;
	}
	if(isLegalLoc(capturingLocRight) && getPieceOnBoard(game, capturingLocRight) != NULL && getPieceOnBoard(game, capturingLocRight)->color != piece->color){
		if(addMoveToArray(game,pieceLoc,capturingLocRight,possibleMoves,actualSize) == GAME_FAILED) return GAME_FAILED;
	}
	if(isLegalLoc(regularJump) && getPieceOnBoard(game, regularJump) == NULL){
		if(addMoveToArray(game,pieceLoc,regularJump,possibleMoves,actualSize) == GAME_FAILED) return GAME_FAILED;
		if(isLegalLoc(DoubleJump) && getPieceOnBoard(game, DoubleJump) == NULL && ((piece->loc.row == 1 && piece->color == WHITE) || (piece->loc.row == 6 && piece->color == BLACK))){
			if(addMoveToArray(game,pieceLoc,DoubleJump,possibleMoves,actualSize) == GAME_FAILED) return GAME_FAILED;
		}
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE getAllMovesBishop(ChessGame* game,Piece* piece,Location* possibleMoves, int* actualSize){
	Location pieceLoc = copyLocation(piece->loc);
	bool rightUpEnd = false;
	bool leftUpEnd = false;
	bool rightDownEnd = false;
	bool leftDownEnd = false;
	Location rightUpLoc = copyLocation(pieceLoc);
	Location leftUpLoc = copyLocation(pieceLoc);
	Location rightDownLoc = copyLocation(pieceLoc);
	Location leftDownLoc = copyLocation(pieceLoc);
	GAME_MESSAGE msg;
	while(!leftDownEnd || !rightUpEnd || !leftUpEnd || !rightDownEnd){
		rightUpLoc.row += 1;
		rightUpLoc.col += 1;
		leftUpLoc.row += 1;
		leftUpLoc.col -= 1;
		rightDownLoc.row -= 1;
		rightDownLoc.col += 1;
		leftDownLoc.row -= 1;
		leftDownLoc.col -= 1;
		if(isLegalLoc(rightUpLoc) && !rightUpEnd) {
			if((msg = addMoveToArray(game,pieceLoc,rightUpLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			rightUpEnd = (getPieceOnBoard(game, rightUpLoc) == NULL) ? false : true;
		}
		else rightUpEnd = true;

		if(isLegalLoc(leftUpLoc) && !leftUpEnd) {
			if((msg = addMoveToArray(game,pieceLoc,leftUpLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			leftUpEnd = (getPieceOnBoard(game, leftUpLoc) == NULL) ? false : true;
		}
		else leftUpEnd = true;

		if(isLegalLoc(rightDownLoc) && !rightDownEnd) {
			if((msg = addMoveToArray(game,pieceLoc,rightDownLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			rightDownEnd = (getPieceOnBoard(game, rightDownLoc) == NULL) ? false : true;
		}
		else rightDownEnd = true;

		if(isLegalLoc(leftDownLoc) && !leftDownEnd) {
			if((msg = addMoveToArray(game,pieceLoc,leftDownLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			leftDownEnd = (getPieceOnBoard(game, leftDownLoc) == NULL) ? false : true;
		}
		else leftDownEnd = true;
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE getAllMovesQueen(ChessGame* game,Piece* piece,Location* possibleMoves, int* actualSize){
	if(getAllMovesBishop(game, piece, possibleMoves, actualSize) == GAME_FAILED) return GAME_FAILED;
	if(getAllMovesRook(game, piece, possibleMoves, actualSize) == GAME_FAILED) return GAME_FAILED;
	return GAME_SUCCESS;
}

GAME_MESSAGE getAllMovesRook(ChessGame* game,Piece* piece,Location* possibleMoves, int* actualSize){
	Location pieceLoc = copyLocation(piece->loc);
	bool rightEnd = false;
	bool leftEnd = false;
	bool downEnd = false;
	bool upEnd = false;
	Location rightLoc = copyLocation(pieceLoc);
	Location leftLoc = copyLocation(pieceLoc);
	Location downLoc = copyLocation(pieceLoc);
	Location upLoc = copyLocation(pieceLoc);
	GAME_MESSAGE msg;
	while(!rightEnd || !leftEnd || !downEnd || !upEnd){
		rightLoc.col += 1;
		leftLoc.col -= 1;
		downLoc.row -= 1;
		upLoc.row += 1;
		if(isLegalLoc(rightLoc) && !rightEnd) {
			if((msg = addMoveToArray(game,pieceLoc,rightLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			rightEnd = (getPieceOnBoard(game, rightLoc) == NULL) ? false : true;
		}
		else rightEnd = true;

		if(isLegalLoc(leftLoc) && !leftEnd) {
			if((msg = addMoveToArray(game,pieceLoc,leftLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			leftEnd = (getPieceOnBoard(game, leftLoc) == NULL) ? false : true;
		}
		else leftEnd = true;

		if(isLegalLoc(downLoc) && !downEnd) {
			if((msg = addMoveToArray(game,pieceLoc,downLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			downEnd = (getPieceOnBoard(game, downLoc) == NULL) ? false : true;

		}
		else downEnd = true;

		if(isLegalLoc(upLoc) && !upEnd) {
			if((msg = addMoveToArray(game,pieceLoc,upLoc,possibleMoves,actualSize)) == GAME_FAILED) return GAME_FAILED;
			upEnd = (getPieceOnBoard(game, upLoc) == NULL) ? false : true;
		}
		else upEnd = true;
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE getAllMovesKing(ChessGame* game,Piece* piece,Location* possibleMoves, int* actualSize){
	Location tmpLoc;
	Location pieceLoc = copyLocation(piece->loc);
	Piece* tmpPiece = NULL;
	for(int i = -1; i <= 1; ++i){
		for(int j = -1; j <= 1; ++j){
			if(i == 0 && j == 0) continue;
			tmpLoc = createLocation(pieceLoc.row + i, pieceLoc.col + j);
			tmpPiece = getPieceOnBoard(game, tmpLoc);
			if(isLegalLoc(tmpLoc) && (tmpPiece == NULL || tmpPiece->color != piece->color)) {
				if(addMoveToArray(game,pieceLoc,tmpLoc,possibleMoves,actualSize) == GAME_FAILED) return GAME_FAILED;
			}
		}
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE getAllMovesKnight(ChessGame* game,Piece* piece,Location* possibleMoves, int* actualSize){
	Location tmpLoc;
	Location pieceLoc = copyLocation(piece->loc);
	Piece* tmpPiece = NULL;
	for(int i = -2; i <= 2; ++i){
		if(i == 0) continue;
		int j = (abs(i) == 1) ? -2 : -1;
		for(int loopIndex = 0; loopIndex <= 1; ++loopIndex){
			tmpLoc = createLocation(pieceLoc.row + i, pieceLoc.col + j);
			tmpPiece = getPieceOnBoard(game,tmpLoc);
			if(isLegalLoc(tmpLoc) && (tmpPiece == NULL || tmpPiece->color != piece->color)) {
				if(addMoveToArray(game,pieceLoc,tmpLoc,possibleMoves,actualSize) == GAME_FAILED) return GAME_FAILED;
			}
			j = -j;
		}
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE addMoveToArray(ChessGame* game,Location pieceLoc,Location destLoc,Location* possibleMoves,int* actualSize){
	Piece* currentKing = game->currentPlayer == WHITE ? game->whiteKing : game->blackKing;
	GAME_MESSAGE msg = isPieceThreatenedWithMove(game,currentKing, pieceLoc, destLoc);
	if(msg == GAME_SUCCESS){
		possibleMoves[*actualSize] = copyLocation(destLoc);
		*actualSize += 1;
		return GAME_SUCCESS;
	}
	return msg;
}

Step* distinguishMovesByPiece(ChessGame* game, Location* locArray,int size, Location src){
	if(size == 0) return NULL;
	Step* steps = (Step*) malloc(sizeof(Step)*size);
	if(steps == NULL){
		printMallocError();
		return NULL; //mallocHandling
	}
	Piece* capturedPiece;
	Piece* playedPiece = getPieceOnBoard(game, src);

	for(int i = 0; i < size; ++i){
		steps[i] = createStep(locArray[i], NormalStep);
		capturedPiece = getPieceOnBoard(game, steps[i].dest);
		if(capturedPiece != NULL && (playedPiece->color != capturedPiece->color)) steps[i].class = EatSomeone;
		simpleMovePiece(game,src,steps[i].dest);
		GAME_MESSAGE msg = isPieceThreatened(game,playedPiece);
		if(msg == PIECE_THREATENED) {
			steps[i].class = (steps[i].class == EatSomeone) ? ThreatenedAndEat : Threatened;
		}
		simpleMovePiece(game, steps[i].dest, src);
		setPieceOnBoard(game,steps[i].dest,capturedPiece);
	}
	return steps;
}

void printSteps(Step* steps,int size){
	for(int i = 0; i < size; ++i){
		printLoc(steps[i].dest);
		switch(steps[i].class){
		case Threatened:
			printf("*\n");
			break;
		case EatSomeone:
			printf("^\n");
			break;
		case ThreatenedAndEat:
			printf("*^\n");
			break;
		case NormalStep:
			printf("\n");
			break;
		}
	}
}

bool saveGame(ChessGame* game,char* filePath){
	//opening the FILE
	FILE* file;
	file = fopen(filePath, "w");
	if(file == NULL || filePath == NULL){
		printf("File cannot be created or modified\n");
		return false;
	}
	//prints to the XML file
	fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(file, "<game>\n");
	fprintf(file, "\t<current_turn>%d</current_turn>\n", game->currentPlayer);
	fprintf(file, "\t<game_mode>%d</game_mode>\n", game->gameMode);
	if(game->gameMode == 1){
		fprintf(file, "\t<difficulty>%d</difficulty>\n", game->gameDifficulty);
		fprintf(file, "\t<user_color>%d</user_color>\n", game->userColor);
	}
	fprintf(file, "\t<board>\n");
	for(int i=7; i>=0; i--){
		fprintf(file, "\t\t<row_%d>",(i+1));
		for(int j=0; j<8; j++){
			fprintf(file, "%s", getPieceString(game->gameBoard[i][j] ,false));
		}
		fprintf(file, "</row_%d>\n", (i+1));
	}
	fprintf(file, "\t</board>\n");
	fprintf(file, "</game>\n");
	//closing the FILE
	if(fclose(file) != 0){
		printf("File cannot be created or modified\n");
		return false;
	}
	return true;
}

Piece* getPieceOnBoard(ChessGame* game,Location loc){
	if(!isLegalLoc(loc) || game == NULL) return NULL;
	return game->gameBoard[loc.row][loc.col];
}

void setPieceOnBoard(ChessGame* game,Location loc,Piece* p){
	if(!isLegalLoc(loc) || game == NULL) return;
	game->gameBoard[loc.row][loc.col] = p;
	if(p != NULL){
		p->loc = copyLocation(loc);
		//update kings;
		if(p->type == KING){
			if(p->color == WHITE) game->whiteKing  = p;
			else game->blackKing = p;
		}
	}
}

bool needPromoting(Piece* piece){
	if(piece == NULL) return false;
	return ((piece->color == WHITE && piece->loc.row == 7) || (piece->color == BLACK && piece->loc.row == 0)) && piece->type == PAWN;
}

GAME_MESSAGE movePawn(ChessGame* game,Piece* piece,Location dest, bool userTurn){
	int diffRow = dest.row - piece->loc.row;
	int diffCol = dest.col - piece->loc.col;
	bool emptyDest = (getPieceOnBoard(game,dest) == NULL);
	bool whiteJumpForward = piece->color == WHITE && diffRow == 1;
	bool blackJumpForward = piece->color == BLACK && diffRow == -1;
	bool whiteDoubleJump = piece->color == WHITE && diffRow == 2 && piece->loc.row == 1 && isLegalLoc(dest);
	bool blackDoubleJump = piece->color == BLACK && diffRow == -2 && piece->loc.row == 6 && isLegalLoc(dest);
	bool whiteCanSkip = whiteDoubleJump && getPieceOnBoard(game, createLocation(piece->loc.row+1,piece->loc.col)) == NULL;
	bool blackCanSkip = blackDoubleJump && getPieceOnBoard(game, createLocation(piece->loc.row-1,piece->loc.col)) == NULL;
	bool whiteCanEat = whiteJumpForward && abs(diffCol) == 1 && !emptyDest;
	bool blackCanEat = blackJumpForward && abs(diffCol) == 1 &&  !emptyDest;

	GAME_MESSAGE msg;

	//move with or without capturing
	if(((diffCol == 0 && emptyDest) && (whiteCanSkip || whiteJumpForward|| blackCanSkip || blackJumpForward)) || (abs(diffCol) == 1 && (whiteCanEat || blackCanEat))){
		msg = moveAndCapture(game, piece->loc, dest);
		if (msg != GAME_SUCCESS) {
			return msg;
		}
		if(((piece->color == WHITE && dest.row == 7) || (piece->color == BLACK && dest.row == 0)) && userTurn)
			return pawnPromoting(piece, true,PAWN);
		return GAME_SUCCESS;
	}
	return GAME_INVALID_MOVE;

}
// Type is relevent only if toUser == false.
GAME_MESSAGE pawnPromoting(Piece* piece,bool toUser,PieceType type){
	if (toUser){
		printf("Pawn promotion- please replace the pawn by queen, rook, knight, bishop or pawn:\n");
		char* line = (char*) malloc(MAX_LEN*sizeof(char));
		bool needContinue = true;
		while (needContinue){
			if(fgets(line,MAX_LEN,stdin) == NULL){
				//ERROR HANDLING
			}
			char* delim = " \t\r\n\v\f";
			char* tmp = strtok(line,delim);
			if(strtok(NULL,delim) != NULL){
				printf("Invalid Type\n");
				continue;
			}
			needContinue = false;
			if(strcmp(tmp, "queen") == 0) piece->type = QUEEN;
			else if(strcmp(tmp, "rook") == 0) piece->type = ROOK;
			else if(strcmp(tmp, "knight") == 0) piece->type = KNIGHT;
			else if(strcmp(tmp, "bishop") == 0) piece->type = BISHOP;
			else if(strcmp(tmp, "pawn") == 0) piece->type = PAWN;
			else{
				needContinue = true;
				printf("Invalid Type\n");
			}
		}
		free(line);
	}
	else {
		piece->type = type;
	}
	return GAME_SUCCESS;
}

GAME_MESSAGE moveRook(ChessGame* game, Piece* piece,Location dest){
	Location tmpLoc;
	Location pieceLoc = copyLocation(piece->loc);
	bool equalRows = (dest.row == pieceLoc.row);
	bool equalCols = (dest.col == pieceLoc.col);
	if(!(equalRows ^ equalCols)) return GAME_INVALID_MOVE;

	int max = equalRows ? max(dest.col,pieceLoc.col) : max(dest.row,pieceLoc.row);
	int min = equalRows ? min(dest.col,pieceLoc.col) : min(dest.row,pieceLoc.row);
	for(int i = min + 1; i < max; ++i){
		tmpLoc.col = equalRows ? i : dest.col;
		tmpLoc.row = equalRows ? dest.row : i;
		if(getPieceOnBoard(game, tmpLoc) != NULL) return GAME_INVALID_MOVE;
	}
	//capturing
	return moveAndCapture(game, pieceLoc, dest);
}

GAME_MESSAGE moveBishop(ChessGame* game, Piece* piece,Location dest){
	Location tmpLoc;
	Location pieceLoc = copyLocation(piece->loc);
	if(pieceLoc.col == dest.col) return GAME_INVALID_MOVE;
	int gradient = (pieceLoc.row - dest.row) / (pieceLoc.col - dest.col);
	if(abs(pieceLoc.row - dest.row) != abs(pieceLoc.col - dest.col)) return GAME_INVALID_MOVE;
	int maxCol = max(pieceLoc.col, dest.col);
	tmpLoc = (dest.col < pieceLoc.col) ? copyLocation(dest) : copyLocation(pieceLoc); //we are moving from left to right.
	tmpLoc.col += 1;
	tmpLoc.row += gradient;
	while(tmpLoc.col != maxCol){
		if(getPieceOnBoard(game, tmpLoc) != NULL) return GAME_INVALID_MOVE;
		tmpLoc.col += 1;
		tmpLoc.row += gradient;
	}
	//move with or without capturing
	return moveAndCapture(game, pieceLoc, dest);
}

GAME_MESSAGE moveQueen(ChessGame* game, Piece* piece,Location dest){
	GAME_MESSAGE msg;
	msg = moveRook(game, piece, dest);
	if(msg == GAME_FAILED || msg == GAME_SUCCESS) return msg;
	msg = moveBishop(game, piece, dest);
	if(msg == GAME_FAILED || msg == GAME_SUCCESS) return msg;
	return GAME_INVALID_MOVE; //no needed but anyway.
}

GAME_MESSAGE moveKing(ChessGame* game, Piece* piece, Location dest){
	if (abs(piece->loc.row - dest.row) <= 1 &&  abs(piece->loc.col - dest.col) <= 1){
		return moveAndCapture(game, piece->loc, dest);
	}
	return GAME_INVALID_MOVE;
}

GAME_MESSAGE moveKnight(ChessGame* game, Piece* piece, Location dest){
	Location pieceLoc = copyLocation(piece->loc);
	if((abs(dest.col - pieceLoc.col) == 2 && abs(dest.row - pieceLoc.row) == 1) || (abs(dest.row - pieceLoc.row) == 2 && abs(dest.col - pieceLoc.col) == 1)){
		return moveAndCapture(game, pieceLoc, dest);
	}
	return GAME_INVALID_MOVE;
}

//invariant - the locations are legal. no need to check them.
void killPiece (ChessGame* game,Location dest){
	Piece* piece = getPieceOnBoard(game, dest);
	if(piece == NULL) return;
	pieceDestroy(piece);
	setPieceOnBoard(game,dest,NULL);
}

//invariant - the locations are legal. no need to check them.
void simpleMovePiece(ChessGame* game,Location src,Location dest){
	setPieceOnBoard(game,dest,getPieceOnBoard(game,src));
	setPieceOnBoard(game,src,NULL);
}

GAME_MESSAGE moveAndCapture(ChessGame* game, Location src, Location dest){
	Piece* currentKing = game->currentPlayer == WHITE ? game->whiteKing : game->blackKing;
	GAME_MESSAGE msg = isPieceThreatenedWithMove(game,currentKing, src, dest);
	if(msg != GAME_SUCCESS) return msg;
	killPiece(game, dest);
	simpleMovePiece(game,src,dest);
	return msg;

}

GAME_MESSAGE isPieceThreatened(ChessGame* game,Piece* piece){
	bool lineThreat = checkingLineThreat(game,piece,true) || checkingLineThreat(game,piece,false);
	bool diagonalThreat = checkingDiagonalThreat(game,piece,true) || checkingDiagonalThreat(game,piece,false);
	bool knightsThreat = checkingKnightsThreat(game,piece);
	if (lineThreat || diagonalThreat || knightsThreat) return PIECE_THREATENED;
	return GAME_SUCCESS;

}
//invariant - move direction is legal, there is a piece in src.
GAME_MESSAGE isPieceThreatenedWithMove(ChessGame* game,Piece* piece,Location src, Location dest){
	Piece* capturedPiece = getPieceOnBoard(game, dest);
	Piece* movingPiece = getPieceOnBoard(game, src);
	if(capturedPiece != NULL && (movingPiece->color == capturedPiece->color)) return GAME_INVALID_MOVE;

	capturedPiece = copyPiece(getPieceOnBoard(game, dest));
	killPiece(game, dest);
	simpleMovePiece(game,src,dest);

	GAME_MESSAGE msg = isPieceThreatened(game,piece);

	simpleMovePiece(game, dest, src);
	setPieceOnBoard(game,dest,capturedPiece);
	if(msg == PIECE_THREATENED) return GAME_INVALID_MOVE;
	return msg;
}

bool checkingLineThreat(ChessGame* game,Piece* piece, bool vertically){
	Location pieceLoc = copyLocation(piece->loc);
	Color pieceColor = piece->color;
	Piece* enemyPiece = NULL;
	Location tmpLoc = vertically ? createLocation(pieceLoc.row+1, pieceLoc.col) : createLocation(pieceLoc.row, pieceLoc.col+1);

	for(int i = 0; isLegalLoc(tmpLoc) ; ++i){
		if((enemyPiece = getPieceOnBoard(game, tmpLoc)) != NULL){
			if(enemyPiece->color != pieceColor){
				if(enemyPiece->type == QUEEN || enemyPiece->type == ROOK) return true;
				if(enemyPiece->type == KING && i == 0) return true;
			}
			break;
		}
		if(vertically) tmpLoc.row += 1;
		else tmpLoc.col += 1;
	}

	tmpLoc.col = vertically ? pieceLoc.col : pieceLoc.col - 1;
	tmpLoc.row = vertically ? pieceLoc.row - 1 : pieceLoc.row;

	for(int i = 0; isLegalLoc(tmpLoc); ++i){
		if((enemyPiece = getPieceOnBoard(game, tmpLoc)) != NULL){
			if(enemyPiece->color != pieceColor){
				if(enemyPiece->type == QUEEN || enemyPiece->type == ROOK) return true;
				if(enemyPiece->type == KING && i == 0) return true;
			}
			break;
		}
		if(vertically) tmpLoc.row -= 1;
		else tmpLoc.col -= 1;
	}
	return false;

}

bool checkingDiagonalThreat(ChessGame* game,Piece* piece, bool gradient){
	Location pieceLoc = copyLocation(piece->loc);
	Color pieceColor = piece->color;
	Piece* enemyPiece = NULL;
	Location tmpLoc = createLocation(gradient ? pieceLoc.row + 1 : pieceLoc.row - 1, pieceLoc.col + 1);
	for(int i = 0; isLegalLoc(tmpLoc); ++i){
		if((enemyPiece = getPieceOnBoard(game, tmpLoc)) != NULL){
			if(enemyPiece->color != pieceColor){
				if(enemyPiece->type == QUEEN || enemyPiece->type == BISHOP) return true;
				if(i == 0) {
					if(enemyPiece->type == KING) return true;
					if(enemyPiece->type == PAWN){
						if(pieceColor == WHITE && (enemyPiece->loc.row == pieceLoc.row + 1)) return true;
						if(pieceColor == BLACK && (enemyPiece->loc.row == pieceLoc.row - 1)) return true;
					}
				}
			}
			break;
		}
		tmpLoc.col += 1;
		tmpLoc.row = gradient ? tmpLoc.row + 1 : tmpLoc.row - 1;
	}

	tmpLoc.col = pieceLoc.col - 1;
	tmpLoc.row = gradient ? pieceLoc.row - 1 : pieceLoc.row + 1;
	for(int i = 0; isLegalLoc(tmpLoc); ++i){
		if((enemyPiece = getPieceOnBoard(game, tmpLoc)) != NULL){
			if(enemyPiece->color != pieceColor){
				if(enemyPiece->type == QUEEN || enemyPiece->type == BISHOP) return true;
				if(i == 0) {
					if(enemyPiece->type == KING) return true;
					if(enemyPiece->type == PAWN){
						if(pieceColor == WHITE && enemyPiece->loc.row == pieceLoc.row + 1) return true;
						if(pieceColor == BLACK && enemyPiece->loc.row == pieceLoc.row - 1) return true;
					}
				}
			}
			break;
		}
		tmpLoc.col -= 1;
		tmpLoc.row = gradient ? tmpLoc.row - 1 : tmpLoc.row + 1;
	}
	return false;
}

bool checkingKnightsThreat(ChessGame* game,Piece* piece){
	Location tmpLoc;
	Location pieceLoc = copyLocation(piece->loc);
	Color pieceColor = piece->color;
	Piece* tmpPiece = NULL;
	for(int i = -2; i <= 2; ++i){
		if(i == 0) continue;
		int j = 3 - abs(i); //if i == 1 than j == 2 and if i == 2 j == 1.
		for(int loopIndex = 0; loopIndex <= 1; ++loopIndex){
			tmpLoc = createLocation(pieceLoc.row + i, pieceLoc.col + j);
			tmpPiece = getPieceOnBoard(game, tmpLoc);
			if(isLegalLoc(tmpLoc) && tmpPiece != NULL && tmpPiece->type == KNIGHT && tmpPiece->color != pieceColor) return true;
			j = -j;
		}
	}
	return false;
}

GAME_STATUS checkingWinner(ChessGame* game){
	bool theresLegalMove = false;
	Location possibleMoves[28];
	int a = 0;
	int* actualSize = &a;
	Piece* movingPiece = NULL;
	Piece* currentKing = game->currentPlayer == WHITE ? game->whiteKing : game->blackKing;
	GAME_MESSAGE isThreatened = isPieceThreatened(game,currentKing);
	for(int i = 0; i < 8; ++i){
		if(theresLegalMove) break;
		for(int j = 0; j < 8; ++j){
			movingPiece = getPieceOnBoard(game,createLocation(i,j));
			if (movingPiece == NULL || (movingPiece->color != game->currentPlayer)) continue;
			if(getAllMoves(game,movingPiece->loc,possibleMoves,actualSize,false) == GAME_FAILED)
				return GAME_FAILED;
			if(*actualSize != 0) {
				theresLegalMove = true;
				break;
			}
		}
	}
	if(theresLegalMove) {
		if(isThreatened == PIECE_THREATENED) return CHECK;
		else return NORMAL;
	}
	else{
		if(isThreatened == PIECE_THREATENED) return CHECKMATE;
		else return TIE;
	}

}

GAME_STATUS printWinner(ChessGame* game){
	GAME_STATUS status = checkingWinner(game);
	char* player = (game->currentPlayer == WHITE) ? "white" : "black";
	char* opponent = (game->currentPlayer == WHITE) ? "black" : "white";
	switch(status){
	case CHECK:
		if(game->gameMode == 1 && game->currentPlayer == game->userColor) printf("Check!\n");
		else printf("Check: %s King is threatened!\n",player);
		break;
	case CHECKMATE:
		printf("Checkmate! %s player wins the game\n",opponent);
		break;
	case TIE:
		printf("The game is tied\n");
		break;
	case NORMAL:
		break;
	}
	return status;
}

char* getCurrentPlayerString(ChessGame* game){
	return game->currentPlayer == WHITE ? "white" : "black";
}
