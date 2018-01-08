/*
 * GameLogic.h
 *
 *  Created on: Nov 4, 2017
 *      Author: Ofir Ben shoham
 *      Id: 208642496.
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "PlayerInterface.h"
#include "Board.h"

namespace std {

class GameLogic: public PlayerInterface {
public:

	/**
	 * GameLogic constructor.
	 * Gets newBoard - a board that the game is played into.
	 */
	GameLogic(Board newBoard);

	/**
	 * defualt constructor.
	 */
	GameLogic() {
	}

	/**
	 * void method that gets char that represents the current player (X/O) and prints
	 * his possible moves.
	 */
	void printPossibleCells(char player) const;
	/**
	 * This method checks if the input player can to assign the input cell
	 * in our board.
	 * if it's possible return true. Otherwise -> false.
	 * Cell cellToCheck borders are from: (0..7, 0..7) after the constructor.
	 */
	bool canAssign(char player, Cell cellToCheck) const;

	/**
	 * gets char of the current player (X / O) and returns true if he has possible moves.
	 * Otherwise-> false.
	 */
	bool hasPossibleMoves(char player) const {
		return !possibleCellsToAssign(board, player).empty();
	}

	/**
	 * char player -> X\O, the sign of the current player.
	 * Cell input  -> the input that the player wrote,
	 * here we assume that his choose
	 * is valid.
	 */
	void inputAssignManager(char player, Cell input);

	/**
	 * return a pointer to the board.
	 */
	Board *getBoard() {
		return &this->board;
	}

private:
	/**
	 * The gameLogic has a board object.
	 */
	Board board;

};

} /* namespace std */

#endif /* GAMELOGIC_H_ */
