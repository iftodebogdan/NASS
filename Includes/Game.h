/*
 * Game.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef GAME_H_
#define GAME_H_

#include <oslib/oslib.h>
#include "../Includes/Screen.h"

class Game
{
	friend class DropDownMenu;

public:
	Game();	//creates the game
	~Game();	//destroys the game
	void Run();	//runs the game
};

#endif /* GAME_H_ */
