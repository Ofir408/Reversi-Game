/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: Ofir Ben Shoham
 */

#include "RemotePlayer.h"

using namespace std;

RemotePlayer::RemotePlayer(Client myClient, GameLogic gl) {
	client = myClient;
	gameLogic = gl;

	if (myClient.getPlayerNum() == 1) {
		// x is the first player
		currentPlayer = 'X';
	} else {
		currentPlayer = 'O';
	}
}

void RemotePlayer::printPossibleMoves(Board& b, char Ps) {
	vector<Cell> possibleMovesVec = b.possibleCellsToAssign(Ps);
	cout << "Player: " << Ps << " ,Your Possible Moves are: ";
	for (unsigned i = 0; i < possibleMovesVec.size(); i++) {
		possibleMovesVec[i].printCell();
	}
	cout << " \nPlease choose a cell from your possible options,"
			" for example write 3 and press enter" << endl
			<< "                   4 and press enter:" << endl;
}

Cell RemotePlayer::chooseCell(Board* board, char playerSign) {

	// update his board before passing to the second player his turn.
	DoubleCell dc;
	Cell otherTurn, myTurn;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	cout << "First print\n";
	board->printBoard();

>>>>>>> 0bf7b8a62706e6b806f89e0a8c10c8d4849dd80d
=======
>>>>>>> 037fe1e349cf32e98323e8b2e6eb63c7fb82739e
	if (playerSign == 'X') {
		// the first player first write his turn and then read
		printPossibleMoves(*board, playerSign);
		client.setPlayerNum(1);
		dc = client.sendAndWriteToServer(board); // write here his turn and then read other player turn.
	} else {
		client.setPlayerNum(2);
		// the second player first read other player sign and then write.
		dc = client.sendAndWriteToServer(board); // write here his turn and then read other player turn.
	}


	myTurn = dc.getCurrentPlayerMove();
	otherTurn = dc.getOtherPlayerMove();


	// first make the other player turn.
	board->inputAssignManager(Cell::returnOtherSign(playerSign), otherTurn);
<<<<<<< HEAD
<<<<<<< HEAD

=======
	cout << "Second print:\n";
	board->printBoard();

	cout << "\n And now makes my move and the board looks as follows:\n";
>>>>>>> 0bf7b8a62706e6b806f89e0a8c10c8d4849dd80d
=======

>>>>>>> 037fe1e349cf32e98323e8b2e6eb63c7fb82739e
	//board->inputAssignManager(playerSign, dc.getCurrentPlayerMove());

	// return the current player turn - the cell that choosen (that he entered via input from user).
	return myTurn;
}
