#ifndef CHESSARRAYLIST_H_
#define CHESSARRAYLIST_H_
#include <stdbool.h>
#include <stdlib.h>
#include "ChessMove.h"

/**
 * ChessArrayList summary:
 *
 * A container that represents a fixed size linked list. The capcity of the list
 * is Chessecified at the creation. The container supports typical list
 * functionalities with the addition of random access as in arrays.
 * Upon insertion, if the maximum capacity is reached then an error message is
 * returned and the list is not affected. A summary of the supported functions
 * is given below:
 *
 * ChessArrayListCreate       - Creates an empty array list with a Chessecified
 *                           max capacity.
 * ChessArrayListCopy         - Creates an exact copy of a Chessecified array list.
 * ChessArrayListDestroy      - frees all memory resources associated with an array
 *                           list.
 * ChessArrayListClear        - Clears all elements from a Chessecified array list.
 * ChessArrayListAddAt        - Inserts an element at a Chessecified index, elements
 *                           will be shifted to make place.
 * ChessArrayListAddFirst     - Inserts an element at the beginning of the array
 *                           list, elements will be shifted to make place.
 * ChessArrayListAddLast      - Inserts an element at the end of the array list.
 * ChessArrayListRemoveAt     - Removes an element at the Chessecified index, elements
 *                           elements will be shifted as a result.
 * ChessArrayListRemoveFirst  - Removes an element from the beginning of the array
 *                           list, elements will be shifted as a result.
 * ChessArrayListRemoveLast   - Removes an element from the end of the array list
 * ChessArrayListGetAt        - Accesses the element at the Chessecified index.
 * ChessArrayListGetFirst     - Accesses the first element of the array list.
 * ChessArrayListGetLast      - Accesses the last element of the array list.
 * ChessArrayListMaxCapcity   - Returns the maximum capcity of the array list.
 * ChessArrayListSize         - Returns the number of elements in that array list.
 * ChessArrayListIsFull       - Returns if the array list reached its max capacity.
 * ChessArrayListIsEmpty      - Returns true if the array list contains no elements.
 */
typedef struct Chess_array_list_t {
	ChessMove** elements;
	int actualSize;
	int maxSize;
} ChessArrayList;

/**
 * A type used for errors
 */
typedef enum Chess_array_list_message_t {
	Chess_ARRAY_LIST_SUCCESS,
	Chess_ARRAY_LIST_INVALID_ARGUMENT,
	Chess_ARRAY_LIST_FULL,
	Chess_ARRAY_LIST_EMPTY
} Chess_ARRAY_LIST_MESSAGE;

/**
 *  Creates an empty array list with the Chessecified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
ChessArrayList* ChessArrayListCreate(int maxSize);

/**
 *	Creates an exact copy of the src array list. Elements in the new copy will
 *	be in the same order as they appeared in the source list.
 *	@param src - the source array list.
 *	@return
 *	NULL if either an allocation error occurs or src == NULL.
 *	A new copy of the source array list, otherwise.
 */
ChessArrayList* ChessArrayListCopy(ChessArrayList* src);

/**
 * frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void ChessArrayListDestroy(ChessArrayList* src);

/**
 * Inserts element at a Chessecified index. The elements residing at and after the
 * Chessecified index will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @param index - the index where the new element will be placed. The index is
 *                0-based.
 * @return
 * Chess_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * Chess_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * Chess_ARRAY_LIST_SUCCESS - otherwise
 */
Chess_ARRAY_LIST_MESSAGE ChessArrayListAddAt(ChessArrayList* src, ChessMove* elem, int index);

/**
 * Inserts element at a the beginning of the source element. The elements
 * will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * Chess_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * Chess_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * Chess_ARRAY_LIST_SUCCESS - otherwise
 */
 Chess_ARRAY_LIST_MESSAGE ChessArrayListAddFirst(ChessArrayList* src, ChessMove* elem);

/**
 * Removes an element from a Chessecified index. The elements residing after the
 * Chessecified index will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param index - The index from where the element will be removed.
 *                The index is 0-based.
 * @return
 * Chess_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * Chess_ARRAY_LIST_EMPTY - if the source array list is empty
 * Chess_ARRAY_LIST_SUCCESS - otherwise
 */
Chess_ARRAY_LIST_MESSAGE ChessArrayListRemoveAt(ChessArrayList* src, int index);

/**
 * Removes an element from a the beginning of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * Chess_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * Chess_ARRAY_LIST_EMPTY - if the source array list is empty
 * Chess_ARRAY_LIST_SUCCESS - otherwise
 */
Chess_ARRAY_LIST_MESSAGE ChessArrayListRemoveFirst(ChessArrayList* src);

/**
 * Removes an element from a the end of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * Chess_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * Chess_ARRAY_LIST_EMPTY - if the source array list is empty
 * Chess_ARRAY_LIST_SUCCESS - otherwise.
 */
Chess_ARRAY_LIST_MESSAGE ChessArrayListRemoveLast(ChessArrayList* src);


/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
ChessMove* ChessArrayListGetFirst(ChessArrayList* src);

/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int ChessArrayListMaxCapacity(ChessArrayList* src);

/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int ChessArrayListSize(ChessArrayList* src);

/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool ChessArrayListIsFull(ChessArrayList* src);

/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool ChessArrayListIsEmpty(ChessArrayList* src);

/**
 * print the massage that malloc has failed.
 */
void printMallocError();
#endif
