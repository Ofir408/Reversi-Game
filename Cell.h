/*
 * Cell.h
 *
 *  Created on: Oct 31, 2017
 *      Author: Ofir Ben Shoham
 */

#ifndef CELL_H_
#define CELL_H_
#define RowNumber 8
#define colNumber 8

#include <iostream>
#include <cstdlib>
using namespace std;

class Cell {
public:

	/**
	 * constructor method.
	 * Gets board places x,y and a char (X, O) to place in.
	 */
	Cell(int x, int y, char newSign = ' ');

	/**
	 * returns x index of this cell in the board.
	 */
	int getX() {
		return x;
	}

	/**
	 * returns y index of this cell in the board.
	 */
	int getY() {
		return y;
	}

	/**
	 * returns true if the cell into the board borders.
	 * Otherwise -> false.
	 */
	bool isValid();

	/**
	 * returns true if in this cell we have X
	 */
	bool hasX() {
		bool b = this->sign == 'X' || this->sign == 'x';
		return b;
	}

	/**
	 * returns true if in this cell we have O
	 */
	bool hasO() {
		bool b = this->sign == 'O' || this->sign == 'o';
		return b;
	}

	/**
	 * returns true this cell is empty. Otherwise -> false.
	 */
	bool isEmptyCell() {
		return !hasO() && !hasX();
	}

	/**
	 * currentSign - sign of a player (X/O).
	 * returns a char - the second player.
	 * For example if gets X then returns O.
	 */
	static char returnOtherSign(char currentSign);

	/**
	 * void function.
	 * Gets nothing, just help us to print the current cell.
	 */
	void printCell() {
		cout << " (" << getX() << ", " << getY() << ")";
	}

	/**
	 * Gets:
	 * Cell other - the other cell that we want to compare with.
	 * returns true if the cells equal. Otherwise returns false.
	 */
	bool compareCells(Cell other) {
		return x == other.getX() && y == other.getY();
	}

private:
	// x, y values of the current cell
	int x, y;
	// sign is  X / O / empty.
	char sign;
};

#endif /* CELL_H_ */
