/*
 * Game.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef GAME_H_
#define GAME_H_

#include <oslib/oslib.h>
#include "Background.h"
#include "AnimatedSprite.h"
#include "GameLogo.h"

enum GameState
	{
		TITLE_SCREEN
	} mGameState;

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	void LoadResources();
	void SetGameState(GameState state);
	GameState GetGameState();

	void RenderTitleScreen();

	Background* mGameBackground;
	AnimatedSprite* mPlayerSprite;
	GameLogo* mGameLogo;
};

#endif /* GAME_H_ */
