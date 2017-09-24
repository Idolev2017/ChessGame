CC = gcc
OBJS = game/ChessAux.o game/ChessArrayList.o game/ChessCommand.o game/ChessGame.o\
game/ChessMiniMax.o game/ChessMove.o game/ChessPiece.o game/GameSettings.o game/MainAux.o game/main.o\
graphics/Button.o graphics/ChessGameWin.o graphics/ChessGUIManager.o graphics/ChessGUIManager.o graphics/TextureGenerator.o\
graphics/ChessLoadWin.o graphics/ChessMainWin.o graphics/ChessSettingsWin.o graphics/SimpleWindow.o
EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT

SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
game/ChessGame.o: game/ChessGame.c game/ChessGame.h game/GameSettings.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/ChessArrayList.o: game/ChessArrayList.c game/ChessArrayList.h game/ChessMove.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/ChessAux.o: game/ChessAux.c game/ChessAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/ChessCommand.o: game/ChessCommand.c game/ChessCommand.h game/ChessMove.h game/ChessAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c 
game/ChessMiniMax.o: game/ChessMiniMax.c game/ChessMiniMax.h game/ChessGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/ChessMove.o: game/ChessMove.c game/ChessMove.h game/ChessPiece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/ChessPiece.o: game/ChessPiece.c game/ChessPiece.h game/ChessAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/GameSettings.o: game/GameSettings.c game/GameSettings.h game/ChessArrayList.h game/ChessCommand.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/MainAux.o: game/MainAux.c game/MainAux.h game/ChessMiniMax.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game/main.o: game/main.c game/MainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/Button.o: graphics/Button.c graphics/Button.h graphics/TextureGenerator.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/ChessGameWin.o: graphics/ChessGameWin.c graphics/ChessGameWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/ChessGUIManager.o: graphics/ChessGUIManager.c graphics/ChessGUIManager.h\
graphics/ChessGameWin.h graphics/ChessMainWin.h graphics/ChessLoadWin.h graphics/ChessSettingsWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/ChessLoadWin.o: graphics/ChessLoadWin.c graphics/ChessLoadWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/ChessMainWin.o: graphics/ChessMainWin.c graphics/ChessMainWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/ChessSettingsWin.o: graphics/ChessSettingsWin.c graphics/ChessSettingsWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SimpleWindow.o: graphics/SimpleWindow.c graphics/SimpleWindow.h graphics/Button.h game/MainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/TextureGenerator.o: graphics/TextureGenerator.c graphics/TextureGenerator.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)