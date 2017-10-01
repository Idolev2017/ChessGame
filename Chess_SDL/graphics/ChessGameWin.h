#ifndef SPTICTACTOEGAMEWIN_H_
#define SPTICTACTOEGAMEWIN_H_
#include "SimpleWindow.h"
#include <math.h>

#define PANEL_WIDTH 200
#define GAME_BOARD_SIZE 600
#define GAME_NUM_OF_PANEL_BUTTONS 6
#define UNDO_IN_ARRAY 3
#define BOARD_LINE_SIZE 8
#define REC_SIZE (GAME_BOARD_SIZE / BOARD_LINE_SIZE)
#define NOT_CHOOSED -10
#define ERROR_GUI 42

typedef enum{
	GAME_WINDOW_SUCCESS,
	GAME_WINDOW_FAILED
}GAME_WINDOW_MESSAGE;

typedef enum {
	GAME_WHITE_CHECK_EVENT,
	GAME_BLACK_CHECK_EVENT,
	GAME_WHITE_CHECKMATE_EVENT,
	GAME_BLACK_CHECKMATE_EVENT,
	GAME_TIE_EVENT,
	GAME_SAVE_EVENT,
	GAME_LOAD_EVENT,
	GAME_MAIN_MENU_EVENT,
	GAME_EXIT_EVENT,
	GAME_UNDO_EVENT,
	GAME_NONE_EVENT,
	GAME_EVENT_INVALID_ARGUMENT
} GAME_EVENT;
/**
 * Struct: GameTextures
 * Description:
 * contains all the textures of the different pieces.
 */
typedef struct{
	SDL_Texture* grid_texture;
	SDL_Texture* p_white_texture;
	SDL_Texture* p_black_texture;
	SDL_Texture* b_white_texture;
	SDL_Texture* b_black_texture;
	SDL_Texture* q_white_texture;
	SDL_Texture* q_black_texture;
	SDL_Texture* k_white_texture;
	SDL_Texture* k_black_texture;
	SDL_Texture* n_white_texture;
	SDL_Texture* n_black_texture;
	SDL_Texture* r_white_texture;
	SDL_Texture* r_black_texture;
}GameTextures;
/**
 * Struct: GameWin
 * Description:
 * symbols the Game window.
 * contains a simple Window object, array of buttons,
 * array of pieces textures, array of steps and its size.
 * two Location objects of the clicked piece by the user and
 * the piece that has been choosen by the user to present all available moves.
 * and a boolean to be used to decide if the save button is active or not.
 */
typedef struct{
	SimpleWindow* simpleWindow;
	Button** panelButtons;
	GameTextures* gameTextures;
	Step* steps;
	int numOfSteps;
	Location  chosenLoc;
	Location getAllMovesLoc;
	bool savedLastMove;

}GameWin;

/**
 * Name: gameWindowCreate
 * Description:
 * Creates a GameWin object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * creates the instance of the matching simpleWindow.
 * returns a pointer to the new GameWin object that was created.
 */
GameWin* gameWindowCreate();
/**
 * Name: generatePanelButtons
 * Description:
 * Creates a panelButtons array, allocates a memory to it, initializes it and its fields to
 * pre-decided values.
 * also prints memory error messages if these occurs.
 * returns an appropriate GAME_WINDOW_MESSAGE message.
 */
GAME_WINDOW_MESSAGE generatePanelButtons(GameWin* gameWin,bool canUndo);
/**
 * Name: updateUndoButton
 * Description:
 * A function that is responsible to display the undo button in
 * the appropriate texture, i.e. if undo is allowed or not.
 */
void updateUndoButton(GameWin* gameWin,ChessGame* game);
/**
 * Name: gameWindowDraw
 * Description:
 * Draws all the background and all of the buttons that suppose
 * be presented in load window.
 * also draws the pieces in every moment, i.e. supports drag and drop, getAllMoves.
 * returns an appropriate GAME_WINDOW_MESSAGE message if it succeeded or not.
 */
GAME_WINDOW_MESSAGE gameWindowDraw(GameWin* gameWin,ChessGame* game,SDL_Event* event);
/**
 * Name: drawGetAllMoves
 * Description:
 * A function that is responsible to display on the screen
 * all the possible moves that the chosen piece can make.
 */
void drawGetAllMoves(GameWin* gameWin,ChessGame* game);
/**
 * Name: drawPiece
 * Description:
 * A function that is responsible to present the appropriate piece on the screen due the
 * matching piece on the gameboard that in the console mode.
 * returns a GAME_WINDOW_MESSAGE message if it succeeded or not.
 */
GAME_WINDOW_MESSAGE drawPiece(GameWin* gameWin,SDL_Rect* rec, char piece);
/**
 * Name: fillRecColor
 * Description:
 * A function that been used by getAllMoves to present the different locations that appear
 * in the possible moves array in different colors due to their stepType:
 * Threatened, EatSomeone, ThreatenedAndEat and NormalStep.
 */
void fillRecColor(GameWin* gameWin,SDL_Rect* rec,Step step);
/**
 * Name: gameWindowDestroy
 * Description:
 * Destroys all the background and all of the buttons and pieces that suppose
 * be presented in game window.
 * frees gameWin memory.
 */
void gameWindowDestroy(GameWin*);
/**
 * Name: gameWindowHandleEvent
 * Description:
 * Handles the different events that occurred in the window by the user,
 * reacts accordingly and calls the matching function that handles a specific type of button.
 * returns an appropriate GAME_EVENT message if it succeeded or not.
 */
GAME_EVENT gameWindowHandleEvent(GameWin* src,ChessGame* game, SDL_Event* event);
/**
 * Name: gameWindowPanelHandleEvent
 * Description:
 * Handles the different events that occurred in the side-Panel by the user,
 * reacts accordingly.
 * returns an appropriate GAME_EVENT message if it succeeded or not.
 */
GAME_EVENT gameWindowPanelHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event);
/**
 * Name: gameWindowBoardHandleEvent
 * Description:
 * Handles the different events that occurred in the gameboard by the user,
 * reacts accordingly.
 * returns an appropriate GAME_EVENT message if it succeeded or not.
 */
GAME_EVENT gameWindowBoardHandleEvent(GameWin* gameWin,ChessGame* game, SDL_Event* event);
/**
 * Name: destroyStepsArray
 * Description:
 * Destroys and initializes the steps array of the given GameWin.
 */
void destroyStepsArray(GameWin* gameWin);
/**
 * Name: mouseLocToBoardLoc
 * Description:
 * A function that translates mouse click on the screen to
 * a gameboard location and returns that location.
 */
Location mouseLocToBoardLoc(int x, int y);
/**
 * Name: boardLocToRect
 * Description:
 * A function that translates location on the game board to
 * a SDL_Rect and returns that location.
 */
SDL_Rect boardLocToRect(Location loc);
/**
 * Name: isClickedOnBoard
 * Description:
 * A function that returns if the mouse click on the screen
 * happened on the gameBoard.
 */
bool isClickedOnBoard(int x);
/**
 * Name: confirmExitFromGame
 * Description:
 * A function that is responsible to ask the user if
 * he agree to exit the game without save it.
 */
bool confirmExitFromGame();
/**
 * Name: pawnPromotingGUI
 * Description:
 * A function that is responsible to ask the user to what piece
 * he wants to promote his pawn beacause it got the enemy's base.
 */
PieceType pawnPromotingGUI();
/**
 * Name: gameUndoGui
 * Description:
 * A function that is responsible to perform the undo move,
 * return the pieces to the last position they were before the move has took place
 * IF it allowed.
 * returns a GAME_EVENT message if it succeeded or not.
 */
GAME_EVENT gameUndoGui(ChessGame* game);
/**
 * Name: gameRestartGui
 * Description:
 * A function that is responsible handle the user mouse click on
 * the Restart button that appered on the panel.
 * it initializes the gameboard.
 */
void gameRestartGui(int prevDifficulty, int prevGameMode, int prevUserColor, ChessGame* game);
/**
 * Name: gameWindowHide
 * Description:
 * Hides the game window from the screen.
 */
void gameWindowHide(GameWin* gameWin);
/**
 * Name: gameWindowShow
 * Description:
 * Initializes the game window and present it on the screen.
 */
void gameWindowShow(GameWin* gameWin);
/**
 * Name: gameCheckingWinnerGui
 * Description:
 * A functions that returns a GAME_EVENT if is there any
 * special condition in the game like: check, checkmate, tie.
 */
GAME_EVENT gameCheckingWinnerGui(ChessGame* game);
/**
 * Name: showWinnerMessage
 * Description:
 * A functions that prints to the screen if is there any
 * special condition in the game like: check, checkmate, tie.
 */
void showWinnerMessage(GAME_EVENT event);
/**
 * Name: gameTexturesCreate
 * Description:
 * Creates a GameTextures object, allocates a memory to it, initializes it and its fields to NULL.
 * also prints error messages if these occurs.
 * creates the instance of the matching simpleWindow.
 * returns a pointer to the new GameWin object that was created.
 */
GameTextures* gameTexturesCreate(GameWin* gameWin);
/**
 * Name: generateGameTexture
 * Description:
 * Loads the differenet pieces images from surfaces to the matching textures.
 * returns an appropriate GAME_WINDOW_MESSAGE message.
 */
GAME_WINDOW_MESSAGE generateGameTexture(GameWin* gameWin);
/**
 * Name: gameTexturesDestroy
 * Description:
 * Destroys all the pieces texutres.
 */
void gameTexturesDestroy(GameTextures* gameTextures);
#endif
