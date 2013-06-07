/*
 * Game.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef GAME_H_
#define GAME_H_

#include <oslib/oslib.h>

class Game
{
	friend class DropDownMenu;

public:
	enum GameState	//holds the possible states of the game
	{
		TITLE_SCREEN,		//the game is at the title screen
		GAME_SCREEN,		//the game is at the game screen
		TRANSITION_GAME_OVER_SCREEN,
		GAME_OVER_SCREEN,	//the game is at the game over screen
		SKILLS_SCREEN,		//the game is at the skills screen
		CONTROLS_SCREEN
	};

	Game();	//creates the game
	~Game();	//destroys the game
	void Run();	//runs the game
	void SetState(GameState newGameState);
	GameState GetState();

private:
	void LoadResources();

	GameState mGameState;
};

#endif /* GAME_H_ */
