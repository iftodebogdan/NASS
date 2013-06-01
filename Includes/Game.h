/*
 * Game.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef GAME_H_
#define GAME_H_

#include <oslib/oslib.h>
#include <string>
using namespace std;

#define DEBUG_MODE 0

enum GameState	//holds the possible states of the game
	{
		TITLE_SCREEN,		//the game is at the title screen
		GAME_SCREEN,		//the game is at the game screen
		TRANSITION_GAME_OVER_SCREEN,
		GAME_OVER_SCREEN,	//the game is at the game over screen
		SKILLS_SCREEN,		//the game is at the skills screen
		CONTROLS_SCREEN
	};

class Game
{
	friend class DropDownMenu;

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
	void DisplaySkillLevel(unsigned skillLevel, int posX, int posY);
	void RenderSkillsScreen();
	void RenderControlsScreen();

	void DebugScreen();

	GameState mGameState;
	int mSkillsScreenCursor;
};

#endif /* GAME_H_ */
