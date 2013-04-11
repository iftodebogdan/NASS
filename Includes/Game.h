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

#define DEBUG_MODE 1

enum GameState	//holds the possible states of the game
	{
		TITLE_SCREEN,		//the game is at the title screen
		GAME_SCREEN,		//the game is at the game screen
		TRANSITION_GAME_OVER_SCREEN,
		GAME_OVER_SCREEN	//the game is at the game over screen
	};

class Game
{
public:
	Game();	//creates the game
	~Game();	//destroys the game
	void Run();	//runs the game

private:
	void LoadResources();
	void SetState(GameState newGameState);
	GameState GetState();
	void RenderTitleScreen();
	void RenderGameScreen();
	void RenderGameOverScreen();

	void DebugScreen();

	GameState mGameState;
};

#endif /* GAME_H_ */
