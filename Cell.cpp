/*
 * Cell.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: ofir
 */

#include "Cell.h"

Cell::Cell(int newX, int newY, char newSign) {
	x = newX - 1;
	y = newY - 1;
	sign = newSign;

	if (newSign != 'O' && newSign != 'o' && newSign != 'X' && newSign != 'x') {
		sign = ' ';
	}
}

bool Cell::isValid() {
	return (x >= 0 && x < RowNumber && y >= 0 && y < colNumber);
}

char Cell::returnOtherSign(char currentSign) {
	if (currentSign == 'X' || currentSign == 'x') {
		return 'O';
	}
	if (currentSign == 'O' || currentSign == 'o') {
		return 'X';
	}
	return ' ';
}

