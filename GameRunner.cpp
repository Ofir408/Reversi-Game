/*
 * GameRunner.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: ofir
 */

#include "GameRunner.h"

namespace std {

GameRunner::GameRunner(Board b, char player) {
	board = b;
	GameLogic gameLogic(b);
	currentPlayer = player;
}

Cell GameRunner::getUserInput() {

	Cell inputCell = askInput();

	if (!checkValidInput(inputCell)) {
		do {
			if (!gameLogic.canAssign(this->currentPlayer, inputCell)) {
				cout << "\nYou didn't choose from your options.\n";
			}
			cout << "Your choice doesn't legal\n";
			this->gameLogic.printPossibleCells(this->currentPlayer);
			inputCell = askInput();
		} while (!checkValidInput(inputCell));
	}

//cout << "MY NEW PRINT: \n";
//this->board.printBoard();
	return inputCell;
}

bool GameRunner::checkValidInput(Cell inputCell) {
	return inputCell.isEmptyCell() && inputCell.isValid()
			&& gameLogic.canAssign(this->currentPlayer, inputCell);
}

} /* namespace std */

// come to this function with the knowlenge that we can continue in the game.
// It means that at least for one player has a possible move to do.
void std::GameRunner::playNextMove() {

	if (!this->gameLogic.hasPossibleMoves(this->currentPlayer)) {
		string userPassesChecking;
		cout << "\n No Possible Moves. Play passes back to the other player.\n "
				"Press any key to continue and then press on Enter.\n";
		cin >> userPassesChecking;
		if (userPassesChecking.length() != 0) {
			// switch the turn to the other player.
			this->switchCurrentPlayer();

			Cell userInput = getUserInput(); // gets input from the user
			gameLogic.inputAssignManager(this->currentPlayer, userInput);
			this->board = *gameLogic.getBoard();
			this->board.printBoard();

			// after he made his turn, switch the current player.
			this->switchCurrentPlayer();
		}
	} else {
		gameLogic.printPossibleCells(this->currentPlayer);
		Cell userInput = getUserInput(); // gets input from the user
		gameLogic.inputAssignManager(this->currentPlayer, userInput);
		this->board = *gameLogic.getBoard();
		this->board.printBoard();

		// after he made his turn, switch the current player.
		this->switchCurrentPlayer();
	}
}

void std::GameRunner::run() {
	// WRITE THIS FUNCTION. Using canToContinue while loop, while (canTOC..).

	this->gameLogic = GameLogic(Board());
	while (canToContinue()) {
		playNextMove();
	}
	// print who won.
	this->board.whoWon();
}

bool std::GameRunner::canToContinue() {
	// The game is ended when all the board is full or no more moves
	// is possible for the players.
	char before = this->currentPlayer; // the first.
	switchCurrentPlayer();
	char after = this->currentPlayer;  // the second.
	if (this->board.isBoardFull()
			|| (!this->gameLogic.hasPossibleMoves(before)
					&& !this->gameLogic.hasPossibleMoves(after))) {
		this->currentPlayer = before;
		return false; // need to stop.
	}
	this->currentPlayer = before;
	return true; // otherwise, can to continue in the game.

}

Cell std::GameRunner::askInput() {
	string lineInput; //, secondInput;
	getline(cin, lineInput);
	size_t temp = lineInput.find(",");
	string r = lineInput.substr(0, temp);
	string s = lineInput.substr(temp + 1);
	int inputRow = atoi(r.c_str());
	int inputCol = atoi(s.c_str());
	Cell inputCell(inputRow, inputCol);
	return inputCell;
}

void std::GameRunner::switchCurrentPlayer() {
	if (currentPlayer == 'X') {
		this->currentPlayer = 'O';
	} else {
		currentPlayer = 'X'; // because it was 'O'.
	}
}
