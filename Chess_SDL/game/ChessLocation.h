/*
 * ChessLocation.h
 *
 *  Created on: 1 срхїз 2017
 *      Author: Dolev
 */

#ifndef CHESSLOCATION_H_
#define CHESSLOCATION_H_
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 * Struct: Location
 * Description:
 * holds detailes about a gameboard location.
 * row and col are integers in the range 0-7.
 */
typedef struct {
	int row;
	int col;
} Location;
/**
 * Name: createLocation
 * Description:
 * constructs a Location object,
 * initialize its fields to the arguments who were given.
 * returns the new Location.
 */
Location createLocation(int row, int col);
/**
 * Name: copyLocation
 * Description:
 * copies the Location loc with all of its fields and returns it.
 */
Location copyLocation(Location loc);
/**
 * Name: parseLocation
 * Description:
 * if it recives a string in the template "<number,upperCaseLetter>"
 * then it parses it to a Location object as follows:
 * number in range 1-8 will be reduced by 1, upperCaseLetter in range A-H
 * will be replaced with a matching number from 0-7.
 * returns the new Location.
 */
Location parseLocation(char* str);
/**
 * Name: isLegalLoc
 * Description:
 * returns true if loc.row and loc.col are in range 0-7 inclusive.
 * otherwise it returns false.
 */
bool isLegalLoc(Location loc);
/**
 * Name: equalLocations
 * Description:
 * returns true if loc1 and loc2 have the same row number and col number.
 * otherwise it returns false.
 */
bool equalLocations(Location loc1, Location loc2);
/**
 * Name: printLoc
 * Description:
 * prints the location loc as a gameboard location as follows:
 * loc.row promoted by 1, loc.col in range 0-7 will be replaced with a matching
 * letter from A-H.
 * The printing will be in the following format "<row,col>".
 */
void printLoc(Location loc);
/**
 * Name: isRepresentLocation
 * Description:
 * returns true if the string str is in the following format:
 * "<something1,something2>".
 * otherwise it returns false.
 */
bool isRepresentLocation(char* str);
#endif /* CHESSLOCATION_H_ */
