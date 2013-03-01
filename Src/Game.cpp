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

	Resources::LoadResources();
	Resources::AssertResources();
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
		oslStartDrawing();
		oslCls();

		if(GetGameState() == TITLE_SCREEN)
			RenderTitleScreen();

		oslEndDrawing();
		oslSyncFrame();
		//oslSwapBuffers();
	}
}

void Game::SetGameState(GameState state)
{
	mGameState = state;
}

GameState Game::GetGameState()
{
	return mGameState;
}

void Game::RenderTitleScreen()
{
	Resources::mController->ReadKeys();
	Resources::mGameBackground->Render();
	Resources::mGameLogo->Render();
	Resources::mDropDownMenu->Render();

	if(Resources::mDropDownMenu->GetState() == RETRACTED)
	{
		Resources::mParafontFont->DrawTextCentered(Resources::STR_PRESS_X_TO_START, 240, 240);
		Resources::mCrossButton->Draw(210, 235);
	}
}
