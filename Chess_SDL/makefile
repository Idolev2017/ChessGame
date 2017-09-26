CC = gcc
OBJS = ChessAux.o ChessArrayList.o ChessCommand.o ChessGame.o\
ChessMiniMax.o ChessMove.o ChessPiece.o GameSettings.o MainAux.o main.o\
Button.o ChessGameWin.o ChessGUIManager.o TextureGenerator.o\
ChessLoadWin.o ChessMainWin.o ChessSettingsWin.o SimpleWindow.o
EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT

SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
ChessGame.o: game/ChessGame.c game/ChessGame.h game/GameSettings.h
	$(CC) $(COMP_FLAG) -c game/$*.c
ChessArrayList.o: game/ChessArrayList.c game/ChessArrayList.h game/ChessMove.h
	$(CC) $(COMP_FLAG) -c game/$*.c
ChessAux.o: game/ChessAux.c game/ChessAux.h
	$(CC) $(COMP_FLAG) -c game/$*.c
ChessCommand.o: game/ChessCommand.c game/ChessCommand.h game/ChessMove.h game/ChessAux.h
	$(CC) $(COMP_FLAG) -c game/$*.c 
ChessMiniMax.o: game/ChessMiniMax.c game/ChessMiniMax.h game/ChessGame.h
	$(CC) $(COMP_FLAG) -c game/$*.c
ChessMove.o: game/ChessMove.c game/ChessMove.h game/ChessPiece.h
	$(CC) $(COMP_FLAG) -c game/$*.c
ChessPiece.o: game/ChessPiece.c game/ChessPiece.h game/ChessAux.h
	$(CC) $(COMP_FLAG) -c game/$*.c
GameSettings.o: game/GameSettings.c game/GameSettings.h game/ChessArrayList.h game/ChessCommand.h
	$(CC) $(COMP_FLAG) -c game/$*.c
MainAux.o: game/MainAux.c game/MainAux.h game/ChessMiniMax.h
	$(CC) $(COMP_FLAG) -c game/$*.c
main.o: game/main.c game/MainAux.h graphics/ChessGUIManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c game/$*.c
Button.o: graphics/Button.c graphics/Button.h graphics/TextureGenerator.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessGameWin.o: graphics/ChessGameWin.c graphics/ChessGameWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessGUIManager.o: graphics/ChessGUIManager.c graphics/ChessGUIManager.h\
graphics/ChessGameWin.h graphics/ChessMainWin.h graphics/ChessLoadWin.h graphics/ChessSettingsWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessLoadWin.o: graphics/ChessLoadWin.c graphics/ChessLoadWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessMainWin.o: graphics/ChessMainWin.c graphics/ChessMainWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessSettingsWin.o: graphics/ChessSettingsWin.c graphics/ChessSettingsWin.h graphics/SimpleWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
SimpleWindow.o: graphics/SimpleWindow.c graphics/SimpleWindow.h graphics/Button.h game/MainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
TextureGenerator.o: graphics/TextureGenerator.c graphics/TextureGenerator.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
	