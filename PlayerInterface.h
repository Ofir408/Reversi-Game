/*
 * PlayerInterface.h
 * This abstract class represents an "Iterface" to the player.
 * We have the original player that plays manually, and the AI player
 * that we will build in the future.
 * Bote will extend this PlayerInterface.
 *  Created on: Nov 4, 2017
 *      Author: Ofir Ben-Shoham
 */

#include "Board.h"
#include "Cell.h"
#include <iostream>
#include <vector>

#ifndef PLAYERINTERFACE_H_
#define PLAYERINTERFACE_H_

namespace std {

class PlayerInterface {
public:
	/**
	 * we will not implement this method since this is an interface and we don't want
	 * to enable opportionity to create objects.
	 */
	PlayerInterface() {
	}

	/**
	 * This function gets:
	 * char current player -> X / O.
	 * Cell emptyCellToCheck -> an empty cell that we check.
	 * returns true if the player can assign his sign in the input empty cell.
	 * Otherwise returns false.
	 */
	bool canToAssign(Board board, char player, Cell emptyCellToCheck) const {
		return board.canToAssign(player, emptyCellToCheck);
	}

	/**
	 * returns vector of cells that each one represents an empty cell that
	 * the current player can assign his sign there.
	 * each cell from the return vector is from (1..8, 1..8)
	 * Because we want to print the possible moves
	 * to the current player according how the board is printed and not from (0..7) as the array works.
	 *
	 */
	vector<Cell> possibleCellsToAssign(Board board, char player) const {
		vector<Cell> vecToReturn;
		// passing on the all cells in our board.
		for (int r = 1; r <= RowNumber; r++) {
			for (int c = 1; c <= colNumber; c++) {
				Cell currentCell(r, c);
				if (board.isCellEmpty(currentCell)
						&& canToAssign(board, player, currentCell)) {
					// add it to our vector with +1 because we want to show to our user
					// the possible cells from (1..8, 1..8) and not from (0..7, 0..7).
					vecToReturn.push_back(
							Cell(currentCell.getX() + 2,
									currentCell.getY() + 2)); // +2 because we lower twice when we created Cell using its constructor.
				}
			}
		}
		return vecToReturn;
	}
};

} /* namespace std */

#endif /* PLAYERINTERFACE_H_ */
