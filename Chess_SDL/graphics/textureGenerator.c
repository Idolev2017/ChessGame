/*
 * textureGenerator.c
 *
 *  Created on: 21 בספט׳ 2017
 *      Author: ido abulafya
 */
#include "textureGenerator.h"

ButtonTextures createButtonTextures(){
	ButtonTextures buttonTexturesTextures;
	buttonTexturesTextures.activeTexture = NULL;
	buttonTexturesTextures.inactiveTexture = NULL;
	buttonTexturesTextures.nonClickableTexture = NULL;
	return buttonTexturesTextures;
}

void destroyButtonTextures(ButtonTextures* buttonTexturesTextures){
	if(buttonTexturesTextures == NULL) return;
	if(buttonTexturesTextures->activeTexture != NULL) SDL_DestroyTexture(buttonTexturesTextures->activeTexture);
	if(buttonTexturesTextures->inactiveTexture != NULL) SDL_DestroyTexture(buttonTexturesTextures->inactiveTexture);
	if(buttonTexturesTextures->nonClickableTexture != NULL) SDL_DestroyTexture(buttonTexturesTextures->nonClickableTexture);
}

//main window
TEXTURE_MESSAGE setMainTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"mainTitle", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setMainNewGameTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"mainNewGame", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setMainLoadTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"mainLoad", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setMainExitTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"mainExit", ACTIVE_TEXTURE);
}

//TEXTURE_MESSAGE settings window
TEXTURE_MESSAGE setSettingsStartTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"settingsStartActive", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"settingsStartUnclickable", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setSettingsNextTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"settingsNextActive", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"settingsNextUnclickable", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setSettingsBackTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"settingsBack", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameModeTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"gameModeTitle", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setGameMode1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameMode1Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameMode1Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameMode2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameMode2Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameMode2Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setDifficultyTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"difficultyTitle", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setDifficulty1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"difficulty1Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"difficulty1Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setDifficulty2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"difficulty2Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"difficulty2Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setDifficulty3Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"difficulty3Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"difficulty3Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setDifficulty4Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"difficulty4Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"difficulty4Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setUserColorTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"userColorTitle", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setUserColor1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"userColor1Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"userColor1Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setUserColor2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"userColor2Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"userColor2Inactive", INACTIVE_TEXTURE);
}

//load window
TEXTURE_MESSAGE setLoadTitleTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"mainExit", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameSlot1Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameSlot1Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameSlot1Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameSlot2Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameSlot2Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameSlot2Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameSlot3Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameSlot3Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameSlot3Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameSlot4Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameSlot4Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameSlot4Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameSlot5Textures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"gameSlot5Active", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"gameSlot5Inactive", INACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setLoadLoadTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"LoadButtonActive", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"LoadButtonUnclickable", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setLoadbackTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"loadBack", ACTIVE_TEXTURE);
}

//game window
TEXTURE_MESSAGE setGameRestartTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"gameRestart", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameSaveTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"gameSave", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameLoadTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"gameLoad", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameUndoTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	if(setTextures(buttonTextures,renderer,"GameUndoActive", ACTIVE_TEXTURE) == TEXTURE_FAILED) return TEXTURE_FAILED;
	return setTextures(buttonTextures,renderer,"GameUndoUnclickable", NON_CLICKABLE_TEXTURE);
}
TEXTURE_MESSAGE setMainMenuTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"mainMenu", ACTIVE_TEXTURE);
}
TEXTURE_MESSAGE setGameExitTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer){
	return setTextures(buttonTextures,renderer,"gameExit", ACTIVE_TEXTURE);
}

TEXTURE_MESSAGE setTextures(ButtonTextures* buttonTextures,SDL_Renderer* renderer,char* buttonTexturesName, TEXTURE_TYPE type){
	char path[MAX_PATH];
	bool failed = false;
	sprintf(path,"./graphics/images/buttons/%s.bmp",buttonTexturesName);
	SDL_Surface* loadingSurface = SDL_LoadBMP(path);
	if (loadingSurface == NULL) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		return TEXTURE_FAILED;
	}
	switch(type){
	case ACTIVE_TEXTURE:
		buttonTextures->activeTexture = SDL_CreateTextureFromSurface(renderer,loadingSurface);
		if (buttonTextures->activeTexture == NULL) failed = true;
		break;
	case INACTIVE_TEXTURE:
		buttonTextures->inactiveTexture = SDL_CreateTextureFromSurface(renderer,loadingSurface);
		if (buttonTextures->inactiveTexture == NULL) failed = true;
		break;
	case NON_CLICKABLE_TEXTURE:
		buttonTextures->nonClickableTexture = SDL_CreateTextureFromSurface(renderer,loadingSurface);
		if (buttonTextures->nonClickableTexture == NULL) failed = true;
		break;
	}
	if(failed){
		printf("Could not create a texture: %s\n", SDL_GetError());
		SDL_FreeSurface(loadingSurface);
		return TEXTURE_FAILED;
	}
	SDL_FreeSurface(loadingSurface);
	return TEXTURE_SUCCESS;
}

void freeButtonTextures(ButtonTextures* buttonTextures){
	free(buttonTextures->activeTexture);
	free(buttonTextures->inactiveTexture);
	free(buttonTextures->nonClickableTexture);
}
