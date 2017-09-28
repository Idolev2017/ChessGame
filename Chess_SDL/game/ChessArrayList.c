#include "ChessArrayList.h"


ChessArrayList* ChessArrayListCreate(int maxSize){
	if(maxSize <= 0) return NULL;
	ChessArrayList* array = (ChessArrayList*) malloc(sizeof(ChessArrayList)); //mallocHandling
	if(array == NULL) {
		printMallocError();
		return NULL;
	}
	array->actualSize = 0;
	array->elements = (ChessMove**) malloc(sizeof(ChessMove*)*maxSize); //mallocHandling
	if(array->elements == NULL){
		free(array);
		printMallocError();
		return NULL;
	}
	for(int i = 0; i < maxSize; ++i){
		array->elements[i] = NULL;
	}
	array->maxSize = maxSize;
	return array;
}

ChessArrayList* ChessArrayListCopy(ChessArrayList* src){
	if(src == NULL) return NULL;
	ChessArrayList* copied = ChessArrayListCreate(src->maxSize);
	if(copied == NULL) {
		printMallocError();
		return NULL;
	}
	copied->actualSize = src->actualSize;
	copied->maxSize = src ->maxSize;
	for(int i = 0; i < src->actualSize; ++i){
		copied->elements[i] = chessMoveCopy(src->elements[i]);
		if(copied->elements[i] == NULL && src->elements[i] != NULL){ //mallocHandling
			ChessArrayListDestroy(src);
			return NULL;
		}
	}
	return copied;
}

void ChessArrayListDestroy(ChessArrayList* src){
	if(src == NULL) return;
	for(int i = 0; i < src->actualSize; ++i){
		chessMoveDestroy(src->elements[i]);
	}
	free(src->elements);
	free(src);
}

Chess_ARRAY_LIST_MESSAGE ChessArrayListAddFirst(ChessArrayList* src, ChessMove* elem){
	if (src == NULL) return Chess_ARRAY_LIST_INVALID_ARGUMENT;
	if (src->actualSize == src->maxSize){
		Chess_ARRAY_LIST_MESSAGE Array_msg = ChessArrayListRemoveLast(src);
		if(Array_msg != Chess_ARRAY_LIST_SUCCESS) {
			return Array_msg; //Unknown Error
		}
	}
	for (int i = src->actualSize ; 0 < i ; --i){
		src->elements[i] = src->elements[i-1];
	}
	src->elements[0] = elem;
	src->actualSize += 1;
	return Chess_ARRAY_LIST_SUCCESS;
}

Chess_ARRAY_LIST_MESSAGE ChessArrayListRemoveAt(ChessArrayList* src, int index){
	if (src == NULL || (src->actualSize <= index && index != 0) || index < 0) return Chess_ARRAY_LIST_INVALID_ARGUMENT;
	if (src->actualSize == 0) return Chess_ARRAY_LIST_EMPTY;
	chessMoveDestroy(src->elements[index]);
	for (int i = index ; i < src->actualSize-1 ; ++i){
		src->elements[i] = src->elements[i+1];
	}
	src->actualSize -= 1;
	src->elements[src->actualSize] = NULL;
	return Chess_ARRAY_LIST_SUCCESS;
}
Chess_ARRAY_LIST_MESSAGE ChessArrayListRemoveFirst(ChessArrayList* src){
	return ChessArrayListRemoveAt(src,0);
}
Chess_ARRAY_LIST_MESSAGE ChessArrayListRemoveLast(ChessArrayList* src){
	return ChessArrayListRemoveAt(src,src->actualSize-1);
}

ChessMove* ChessArrayListGetAt(ChessArrayList* src, int index){
	if(src == NULL || src->actualSize <= index || index < 0) return NULL;
	return chessMoveCopy(src->elements[index]);
}
ChessMove* ChessArrayListGetFirst(ChessArrayList* src){
	return ChessArrayListGetAt(src,0);
}

int ChessArrayListMaxCapacity(ChessArrayList* src){
	if(src == NULL) return -1;
	return src->maxSize;
}
int ChessArrayListSize(ChessArrayList* src){
	if(src == NULL) return -1;
	return src->actualSize;
}
bool ChessArrayListIsFull(ChessArrayList* src){
	if(src == NULL || src->actualSize < src->maxSize) return false;
	return true;
}
bool ChessArrayListIsEmpty(ChessArrayList* src){
	if(src == NULL || src->actualSize != 0) return false;
	return true;
}


