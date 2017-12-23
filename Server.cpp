/*
 * Server.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: Ofir Ben Shoham.
 */

#define maxConnections 2
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>

namespace std {

Server::Server(int portNum, GameManager* gm) {
	this->serverPortNumber = portNum;
	this->serverSocket = 0; // by default, will change after initalize.
	canContinue = true; // until we get "END"
	this->gamesManager = gm;
}

void Server::socketInitialize() {
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serverSocket < 0) {
		perror("Failed in socketInitialize() \n");
	}
}

void Server::setAndStartServer() {
	// Assign a local address to the socket
	struct sockaddr_in serverAddress;
	// now, to be ensure that all his data is empty.
	memset(&serverAddress, 0, sizeof(serverAddress));

	// initialize the serverAdress as followsthrow "Error on binding";
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(this->serverPortNumber);

	// bind according the serverSocket that we built & the serverAdress.
	if (bind(serverSocket, (struct sockaddr *) &serverAddress,
			sizeof(serverAddress)) < 0) {
		perror("Failed in bind of serverSocket at setAndStartServer() \n");
	}

	// Start listening to incoming connections
	listen(serverSocket, maxConnections);
}

void Server::handleWithInput(int clientSocToRead, int clientSocToWrite) {
	GetAndSendIntsToClient(clientSocToRead, clientSocToWrite);
}

bool Server::checkIfcanContinue() {
	return this->canContinue;
}

void Server::workWithClients(GameDescriptor gameDes) {
	int firstClientSocket = gameDes.getFirstClientSocket();
	int secondClientSocket = gameDes.getSecondClientSocket();

	if (firstClientSocket == -1 || secondClientSocket == -1) {
		cout
				<< "I don't have the sockets of the clients, can't continue. Server::workWithClients() \n";
		exit(-1);
	}
	int i = 1;
	if (write(firstClientSocket, &i, sizeof(i)) < 0) {
		perror(
				"Failed to write 1 to the firstClientSocket after both connected");
	}

	i = 2;
	if (write(secondClientSocket, &i, sizeof(i)) < 0) {
		perror(
				"Failed to write 2 to the secondClientSocket after both connected");
	}

	// Connect them before the loop because we want to send "1 to player 1 & 2 to player 2
	// Just once and not always.

	// start the while loop until END was sent.

	while (checkIfcanContinue()) {

		handleWithInput(firstClientSocket, secondClientSocket);
		// check if still can continue:
		if (!checkIfcanContinue()) {
			break;
		} else {
			cout << "Passed to the other client to ask input from\n";
			// can continue, so do it but reverse to pass from the second to the first.
			handleWithInput(secondClientSocket, firstClientSocket);
		}
	}

	// when it comes to here, it means that we exited from the while and the game is ended.
	closeServer(); // then close the socket's server and finish the game.
}

void Server::closeServer() {
	close(this->serverSocket);
}

void Server::GetAndSendIntsToClient(int clientSocToGetFrom,
		int clientSocToSend) {
	int rowNum = 0, colNum = 0;

	//while (true) {
	rowNum = 0;
	colNum = 0;
	int n = read(clientSocToGetFrom, &rowNum, sizeof(rowNum)); // read the first arg.
	if (n <= 0) {
		cout << "Can't get the first number" << endl;
	}

	n = read(clientSocToGetFrom, &colNum, sizeof(colNum)); // read the second arg.
	if (n <= 0) {
		cout << "Can't get the second number" << endl;
	}

	// now write
	sendTurn(clientSocToSend, rowNum, colNum);
}

void Server::sendTurn(int clientSocToWriteInto, int row, int col) {
	int n = write(clientSocToWriteInto, &row, sizeof(row));
	if (n <= 0) {
		throw "Error writing arg1 to socket";
	}
	n = write(clientSocToWriteInto, &col, sizeof(col));
	if (n <= 0) {
		throw "Error writing arg2 to socket";
	}
}

int Server::acceptFirstClientSocket() {
	int firstClientSocket;
	struct sockaddr_in firstClientAddress;
	socklen_t firstClientAddressSize;

	cout << "Waiting for client connections..." << endl;
	// Accept a new client connection for the first client.
	firstClientSocket = accept(serverSocket,
			(struct sockaddr *) &firstClientAddress, &firstClientAddressSize);
	cout << "firstClientSocket is:  " << firstClientSocket << endl;

	if (firstClientSocket < 0) {
		perror("Problem in accept of the first client.\n");
	}
	return firstClientSocket;
}

int Server::acceptSecondClientSokcet() {
	int secondClientSocket;
	struct sockaddr_in secondClientAddress;
	socklen_t secondClientAddressSize;

	secondClientSocket = accept(serverSocket,
			(struct sockaddr *) &secondClientAddress, &secondClientAddressSize);
	if (secondClientSocket < 0) {
		perror("Problem in accept of the second client.\n");
	}
	return secondClientSocket;
}

string Server::getOnePlayerGames() {
	return this->gamesManager->getsOnePlayerGameNames();
}
}

