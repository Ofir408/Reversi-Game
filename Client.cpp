/*
 * Client.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: Ofir Ben Shoham.
 */

#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "Client.h"

using namespace std;

Client::Client(const char *serverIP, int serverPort) :
		serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
	cout << "Client" << endl;
	playerNum = 0; // by default
}

void Client::connectToServer(bool isFirst) {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}
	// Convert the ip string to a network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address";
	}

	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	// Create a structure for the server address
	struct sockaddr_in serverAddress;
	bzero((char *) &address, sizeof(address));
	serverAddress.sin_family = AF_INET;
	memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	serverAddress.sin_port = htons(serverPort);
	// Establish a connection with the TCP server
	if (connect(clientSocket, (struct sockaddr *) &serverAddress,
			sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;

	// read his player number id
	if (isFirst) {
		readHisCilentNum();
		//cout << "Player Number is: " << getPlayerNum() << endl;
	} else {
		this->playerNum = 2;
		//cout << "Player Number is: " << getPlayerNum() << endl;
	}
}

DoubleCell Client::sendAndWriteToServer() {
	int x, y;
	Cell readenCell;
	Cell myCell;

	if (playerNum == 1) {
		cout << "Enter x\n";
		cin >> x;
		cout << "Enter y\n";
		cin >> y;
		myCell = Cell(x, y);
		sendTurnToServer(x, y);
		readenCell = getCurrentTurn(); // then he reads.
	} else {
		readenCell = getCurrentTurn(); // first he reads.
		cout << "Enter x\n";
		cin >> x;
		cout << "Enter y\n";
		cin >> y;
		sendTurnToServer(x, y);
		myCell = Cell(x, y);
	}
	this->turnsToPlay.setOtherPlayerMove(readenCell);
	this->turnsToPlay.setCurrentPlayerMove(myCell);

	DoubleCell toReturn(readenCell, myCell);
	return toReturn;
}

void Client::readHisCilentNum() {
	int clientNumber;
	int r = read(clientSocket, &clientNumber, sizeof(clientNumber));
	if (r < 0) {
		throw "Error reading from the socket in sendToServer() ";
	}
	cout << "*** My Client id is: " << clientNumber << " ***\n";
	if (clientNumber == 1) {
		this->playerNum = 1;
	} else {
		this->playerNum = 2;
	}
}

// ********************************** CHANGE TO RETURN CELL IN ORDER TO USE IN REMOTE PLAYER *****************
Cell Client::getCurrentTurn() {
	int row = 0;
	int col = 0;


	// ************************** NOTE ********************************************
	// The above line makes an exception. In debug it looks that clientSocket has his socket as needed,
	// So , I don't know what's the problem. Try to take a look in order to solve it.

	int n = read(clientSocket, &row, sizeof(row));
	if (n <= 0) {
		throw "Exception in getCurrentTurn() In Client Class -  can't read the row number\n";
	}

	if (read(clientSocket, &col, sizeof(col)) <= 0) {
		throw "Error reading arg2";
	}
	cout << "I'm the client and I read:  (" << row << ", " << col << ") ";
	Cell c(row, col);
	return c;
}

void Client::sendTurnToServer(int row, int col) {
	// Write the point arguments to the socket
	int n = write(clientSocket, &row, sizeof(row));
	if (n < 0) {
		throw "Error writing arg1 to socket";
	}
	if (write(clientSocket, &col, sizeof(col)) < 0) {
		throw "Error writing arg2 to socket";
	}
}

void Client::startClient() {
	try {
		sendAndWriteToServer(); // Have a return value - it's double cell. & update his turnsToPlay field.
		cout << "passed the writing\n";

	} catch (const char *msg) {
		cout << "Failed to send exercise to server. Reason is: " << msg << endl;
	}
}
