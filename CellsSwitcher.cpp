/*
 * CellsSwitcher.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: ofir
 */

#include "CellsSwitcher.h"

namespace std {

CellsSwitcher::CellsSwitcher() {
}

void CellsSwitcher::rowSwitch(Board *b, Cell start, Cell end, char replaceTo) {
	// start.getY() should be smaller than end.getY().
	if (start.getX() == end.getX()) {
		for (int i = start.getY(); i <= end.getY(); i++) {
			b->setCell(start.getX(), i, replaceTo);
		}
	}
}

void CellsSwitcher::colSwitch(Board *b, Cell start, Cell end, char replaceTo) {
	// need to be sure that start.getX() smaller than end.getX()
	if (start.getY() == end.getY()) {
		for (int i = start.getX(); i <= end.getX(); i++) {
			b->setCell(i, start.getY(), replaceTo);
		}
	}
}

void CellsSwitcher::slantSwitch(Board *b, Cell start, Cell end,
		char replaceTo) {

	if (start.getX() > end.getX() && start.getY() < end.getY()) {
		for (int row = start.getX(), col = start.getY();
				row >= end.getX() && col <= end.getY(); row--, col++) { // check if col <= end.getY() or without =
			b->setCell(row, col, replaceTo);
		}
	} else if (start.getX() > end.getX() && start.getY() > end.getY()) {
		for (int r = end.getX(), c = end.getY();
				r <= start.getX() && c <= start.getY(); r++, c++) {
			b->setCell(r, c, replaceTo);
		}
	} else if (start.getX() < end.getX() && start.getY() < end.getY()) {
		for (int row = start.getX(), col = start.getY();
				row <= end.getX() && col <= end.getY(); row++, col++) {
			b->setCell(row, col, replaceTo);
		}
	} else if (start.getX() < end.getX() && start.getY() > end.getY()) {
		for (int r = end.getX(), c = end.getY();
				r >= start.getX() && c <= start.getX(); r--, c++) {
			b->setCell(r, c, replaceTo);
		}
	}
}

}
