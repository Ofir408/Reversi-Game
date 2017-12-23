/*
 * JoinGameFunc.h
 *
 *  Created on: Dec 23, 2017
 *      Author: Ofir Ben-Shoham
 */

#ifndef JOINGAMEFUNC_H_
#define JOINGAMEFUNC_H_
#include "Command.h"
using namespace std;

class JoinGameFunc: public Command {
public:
	JoinGameFunc(Server* server);

	/**
	 * virtual method that need to be implemented because it's a derive class of Command
	 * Gets vector<string> -> for this class the vector should contain in args[0]
	 *  **the SECOND client socket number** that asked to enter the game.
	 *  In args[1] - the name of the game that the second client want to enter.
	 *  To sum up: args[0]- socket of the client that wants to enter to args[1] game (name of game).
	 * It's the programmer responssiblity to give him this, when calling excute with list_games command.
	 *
	 */
	virtual void execute(vector<string> args);

};

#endif /* JOINGAMEFUNC_H_ */
