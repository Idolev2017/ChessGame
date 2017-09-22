/*
 * Button.c
 *
 *  Created on: 18 בספט׳ 2017
 *      Author: Dolev
 */
#include "Button.h"

Button* buttonCreate(SDL_Renderer* renderer,BUTTON_TYPE type,bool isActive, bool isClickable){
	Button* button = (Button*) malloc(sizeof(Button));
	if(button == NULL){
		printf("Couldn't create Button struct\n");
		return NULL;
	}
	button->activeTexture = NULL;
	button->inactiveTexture = NULL;
	button->nonClickableTexture = NULL;
	if(typeToTextureAndRect(button,renderer, type) == BUTTON_FAILED){
		buttonDestroy(button);
		return NULL;
	}
	button->type = type;
	button->isActive = isActive;
	button->isClickable = isClickable;
	return button;
}
ButtonMessage buttonArrayCreate(SDL_Renderer* renderer,Button** buttons,BUTTON_TYPE* types,bool* isActiveArray,bool* isClickableArray, int size){
	for(int i = 0; i < size; ++i){
		buttons[i] = buttonCreate(renderer,types[i],isActiveArray[i],isClickableArray[i]);
		if(buttons[i] == NULL){
			buttonArrayDestroy(buttons, i);
			return BUTTON_FAILED;
		}
	}
	return BUTTON_SUCCESS;
}
void buttonArrayDestroy(Button** buttons,int size){
	if(buttons == NULL) return;
	for(int i = 0; i < size; ++i){
		buttonDestroy(buttons[i]);
		buttons[i] = NULL;
	}
}
void buttonDestroy(Button* button){
	if(button == NULL) return;
	if(!button->activeTexture) SDL_DestroyTexture(button->activeTexture);
	if(!button->inactiveTexture) SDL_DestroyTexture(button->inactiveTexture);
	if(!button->nonClickableTexture) SDL_DestroyTexture(button->nonClickableTexture);
	free(button);
	return;
}
Button* copyButton(Button* button){
	return NULL;
}
ButtonMessage activateButton(Button* button){
	if(button == NULL) return BUTTON_FAILED;
	button->isActive = true;
	return BUTTON_SUCCESS;
}
ButtonMessage inactivateButton(Button* button){
	if(button == NULL) return BUTTON_FAILED;
	button->isActive = false;
	return BUTTON_SUCCESS;
}
void addButtonToRenderer(Button* button,SDL_Renderer* renderer){
	if(!button || !renderer) return;
	if(!button->isClickable){
		SDL_RenderCopy(renderer, button->nonClickableTexture, NULL, &(button->rect));
	}
	else if(button->isActive){
		SDL_RenderCopy(renderer, button->activeTexture, NULL, &(button->rect));
	}
	else{
		SDL_RenderCopy(renderer, button->inactiveTexture, NULL, &(button->rect));
	}
	SDL_RenderPresent(renderer);
}

Button* whichButtonWasClicked(Button** button, int size, int x, int y){
	for(int i = 0; i < size; ++i){
		if(button[i] == NULL) printf("ERROR in whichButtonWasClicked\n");
		if(isClickOnButton(button[i],x,y) && button[i]->isClickable) return button[i];
	}
	return NULL;
}
bool isClickOnButton(Button* button, int x, int y){
	int leftLimit = button->rect.x;
	int rightLimit = leftLimit + button->rect.w;
	int topLimit = button->rect.y;
	int bottomLimit = topLimit + button->rect.h;
	if ((leftLimit <= x && x <= rightLimit) && (topLimit <= y && y <= bottomLimit)) {
		return true;
	}
	return false;
}
ButtonMessage typeToTextureAndRect(Button* button,SDL_Renderer* renderer, BUTTON_TYPE type){
	ButtonTextures* buttonTextures =  createButtonTextures();
	switch(type){
	case MAIN_NEW_GAME_BUTTON:
		if(setMainNewGameTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(300, 200,200, 50);
		break;
	case MAIN_LOAD_BUTTON:
		if(setMainLoadTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(300, 300,200, 50);
		break;
	case MAIN_EXIT_BUTTON:
		if(setMainExitTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(300, 500,200, 50);
		break;

	case SETTINGS_START_BUTTON:
		if(setSettingsStartTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(450, 460,200, 120);
		break;
	case SETTINGS_NEXT_BUTTON:
		if(setSettingsNextTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(450, 460,200, 120);
		break;
	case SETTINGS_BACK_BUTTON:
		if(setSettingsBackTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 460,200, 120);
		break;
	case GAME_MODE_TITLE_BUTTON:
		if(setGameModeTitleTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(175, 50,500, 70);
		break;
	case GAME_MODE_1_BUTTON:
		if(setGameMode1Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(250, 200,350, 50);
		break;
	case GAME_MODE_2_BUTTON:
		if(setGameMode2Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(250, 300,350, 50);
		break;
	case DIFFICULTY_TITLE_BUTTON:
		if(setDifficultyTitleTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(175, 50,500, 70);
		break;
	case DIFFICULTY_1_BUTTON:
		if(setDifficulty1Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 125,200, 50);
		break;
	case DIFFICULTY_2_BUTTON:
		if(setDifficulty2Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 195,200, 50);
		break;
	case DIFFICULTY_3_BUTTON:
		if(setDifficulty3Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 265,200, 50);
		break;
	case DIFFICULTY_4_BUTTON:
		if(setDifficulty4Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 335,200, 50);
		break;
	case DIFFICULTY_5_BUTTON:
		if(setDifficulty5Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 405,200, 50);
		break;
	case USER_COLOR_TITLE_BUTTON:
		if(setUserColorTitleTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(175, 50,500, 70);
		break;
	case COLOR_BLACK_PLAYER_BUTTON:
		if(setUserColor1Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(250, 200,350, 50);
		break;
	case COLOR_WHITE_PLAYER_BUTTON:
		if(setUserColor2Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(250, 300,350, 50);
		break;

		//load window
	case GAME_SLOT1_BUTTON:
		if(setGameSlot1Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 125,200, 50);
		break;
	case GAME_SLOT2_BUTTON:
		if(setGameSlot2Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 195,200, 50);
		break;
	case GAME_SLOT3_BUTTON:
		if(setGameSlot3Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 265,200, 50);
		break;
	case GAME_SLOT4_BUTTON:
		if(setGameSlot4Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 335,200, 50);
		break;
	case GAME_SLOT5_BUTTON:
		if(setGameSlot5Textures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 405,200, 50);
		break;
	case LOAD_LOAD_BUTTON:
		if(setLoadLoadTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(450, 460,200, 120);
		break;
	case LOAD_BACK_BUTTON:
		if(setLoadbackTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(350, 460,200, 120);
		break;

		//game window
	case GAME_UNDO_BUTTON:
		if(setGameUndoTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(20, 100,150, 50);
		break;
	case GAME_SAVE_BUTTON:
		if(setGameSaveTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(20, 160,150, 50);
		break;
	case GAME_LOAD_BUTTON:
		if(setGameLoadTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(20, 220,150, 50);
		break;
	case GAME_RESTART_BUTTON:
		if(setGameRestartTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(20, 280,150, 50);
		break;
	case GAME_MAIN_MENU_BUTTON:
		if(setMainMenuTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(20, 450,150, 50);
		break;
	case GAME_EXIT_BUTTON:
		if(setGameExitTextures(buttonTextures,renderer) == TEXTURE_FAILED) return BUTTON_FAILED;
		button->rect = createRect(20, 510,150, 50);
		break;
	default:
		break;
	}
	button->activeTexture = buttonTextures->activeTexture;
	button->inactiveTexture = buttonTextures->inactiveTexture;
	button->nonClickableTexture = buttonTextures->nonClickableTexture;
	destroyButtonTextures(buttonTextures);
	return BUTTON_SUCCESS;
}
SDL_Rect createRect(int x, int y,int w, int h){
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}
