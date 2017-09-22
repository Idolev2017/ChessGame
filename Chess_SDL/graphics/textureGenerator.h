/*
 * textureGenerator.h
 *
 *  Created on: 21 בספט׳ 2017
 *      Author: ido abulafya
 */

#ifndef GRAPHICS_TEXTUREGENERATOR_H_
#define GRAPHICS_TEXTUREGENERATOR_H_
#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#define MAX_PATH 1024
typedef enum {
	TEXTURE_FAILED,
	TEXTURE_SUCCESS
}TEXTURE_MESSAGE;

typedef enum {
	ACTIVE_TEXTURE,
	INACTIVE_TEXTURE,
	NON_CLICKABLE_TEXTURE
}TEXTURE_TYPE;

typedef struct{
	SDL_Texture* activeTexture;
	SDL_Texture* inactiveTexture;
	SDL_Texture* nonClickableTexture;
}ButtonTextures;

ButtonTextures* createButtonTextures();

void destroyButtonTextures(ButtonTextures* buttonTextures);

//main window
TEXTURE_MESSAGE setMainTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setMainNewGameTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setMainLoadTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setMainExitTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);

	//TEXTURE_MESSAGE settings window
TEXTURE_MESSAGE setSettingsStartTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setSettingsNextTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setSettingsBackTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameModeTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameMode1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameMode2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setDifficultyTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setDifficulty1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setDifficulty2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setDifficulty3Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setDifficulty4Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setDifficulty5Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setUserColorTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setUserColor1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setUserColor2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);

	//load window
TEXTURE_MESSAGE setLoadTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameSlot1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameSlot2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameSlot3Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameSlot4Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameSlot5Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setLoadLoadTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setLoadbackTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);

//game window
TEXTURE_MESSAGE setGameRestartTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameSaveTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameLoadTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameUndoTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setMainMenuTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);
TEXTURE_MESSAGE setGameExitTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer);

TEXTURE_MESSAGE setTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer,char* buttonName, TEXTURE_TYPE type);
#endif /* GRAPHICS_TEXTUREGENERATOR_H_ */
