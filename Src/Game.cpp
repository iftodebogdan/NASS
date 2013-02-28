/*
 * Game.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Game.h"

Game::Game()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	oslSetTransparentColor(RGB(255,0,255));
	oslSetQuitOnLoadFailure(1);
	oslSetKeyAutorepeatInit(40);
	oslSetKeyAutorepeatInterval(10);

	LoadResources();
	mGameState = TITLE_SCREEN;
}

Game::~Game()
{
	oslEndGfx();
	oslQuit();
}

void Game::Run()
{
	oslShowSplashScreen(1);

	while (!osl_quit)
	{
		while(GetGameState() == TITLE_SCREEN)
		{
			oslStartDrawing();
			oslCls();

			Controller::ReadKeys();
			mGameBackground->Render();
			mPlayerSprite->Render();
			mTitleScreen->Render();

			oslEndDrawing();
			oslSyncFrame();
			//oslSwapBuffers();
		}
	}
}

void Game::LoadResources()
{
	mPlayerSprite = new AnimatedSprite(Resources::IMG_PLAYER_SHIP, 68, 64, 15);
	mGameBackground = new Background(Resources::IMG_PRIMARY_BACKGROUND, Resources::IMG_PARALLAX_BACKGROUND, -30, 0, -60, 0);
	mTitleScreen = new TitleScreen();
	Font::LoadFont(Resources::FNT_PARAFONT);
}

void Game::SetGameState(GameState state)
{
	mGameState = state;
}

GameState Game::GetGameState()
{
	return mGameState;
}
