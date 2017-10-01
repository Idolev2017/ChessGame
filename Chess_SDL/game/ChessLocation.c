/*
 * ChessLocation.c
 *
 *  Created on: 1 срхїз 2017
 *      Author: Dolev
 */
#include "ChessLocation.h"

Location createLocation(int row, int col){
	Location loc;
	loc.row = row;
	loc.col = col;
	return loc;
}

Location copyLocation(Location loc){
	Location copy;
	copy.col = loc.col;
	copy.row = loc.row;
	return copy;
}

Location parseLocation(char* str){

	Location loc;
	loc.row = -1;
	loc.col = -1;
	if(strlen(str) !=5) return loc;
	if( str[0] == '<' && '1' <= str[1] && str[1] <= '8' && str[2] == ',' && 'A' <= str[3] && str[3] <= 'H' && str[4] == '>')
	{
		loc.row = str[1] - '1';
		loc.col = str[3] - 'A';
	}
	return loc;
}

bool isLegalLoc(Location loc){
	if(0 <= loc.row && loc.row <= 7 && 0 <= loc.col && loc.col <= 7) return true;
	return false;
}

bool equalLocations(Location loc1, Location loc2){
	return (loc1.row == loc2.row) && (loc1.col == loc2.col);
}

void printLoc(Location loc){
	printf("<%d,%c>",loc.row+1,loc.col + 'A');
}

bool isRepresentLocation(char* str){
	bool commaSeen = false;
	if(str[0] != '<' || str[strlen(str) - 1] != '>') return false;
	for(unsigned int i = 0; i < strlen(str); ++i){
		if(i == 1 && str[i] == '-') continue;
		if(str[i] == ','){
			if(commaSeen) return false;
			commaSeen = true;

		}
		//		else if(str[i] < '0' || '9' < str[i] || str[i] < 'A' || 'Z' < str[i]) return false;
	}
	return true;
}
