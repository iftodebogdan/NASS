/*
 * Game.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef GAME_H_
#define GAME_H_

#include <oslib/oslib.h>
#include "Resources.h"

enum GameState	//holds the possible states of the game
	{
		TITLE_SCREEN,	//the game is at the title screen
		IN_GAME
	};

class Game
{
public:
	Game();	//creates the game
	~Game();	//destroys the game
	void Run();	//runs the game

private:
	void LoadResources();
	void SetGameState(GameState newGameState);
	GameState GetGameState();
	void RenderTitleScreen();

	GameState mGameState;
};

#endif /* GAME_H_ */
