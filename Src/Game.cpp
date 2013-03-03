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
		Resources::mController->ReadKeys();

		oslStartDrawing();
		oslCls();

		if(GetState() == TITLE_SCREEN)
			RenderTitleScreen();

		if(GetState() == GAME_SCREEN)
			RenderGameScreen();

		if(DEBUG_MODE)
			DebugScreen();

		oslEndDrawing();
		oslSyncFrame();
		//oslSwapBuffers();
	}
}

void Game::SetState(GameState newState)
{
	if(newState == TITLE_SCREEN)
	{
		Resources::mGameLogo->Reset();
		Resources::mDropDownMenu->Reset();
	}

	mGameState = newState;
}

GameState Game::GetState()
{
	return mGameState;
}

void Game::RenderTitleScreen()
{
	Resources::mGameBackground->Render();
	Resources::mGameLogo->Render();
	if(Resources::mGameLogo->GetState() != EXITING && Resources::mGameLogo->GetState() != EXITED)
		Resources::mDropDownMenu->Render();

	if(Resources::mGameLogo->GetState() == ENTERING && Resources::mController->IsPressed(CROSS))
		Resources::mGameLogo->SetState(ENTERED);
	else
		if(Resources::mDropDownMenu->GetState() == RETRACTED && Resources::mGameLogo->GetState() == ENTERED)
		{
			Resources::mParafontFont->DrawTextCentered(Resources::STR_PRESS_X_TO_START, 240, 240);
			Resources::mCrossButton->Draw(210, 235);

			if(Resources::mController->IsPressed(CROSS))
			{
				Resources::mGameLogo->SetState(EXITING);
			}
		}

	if(Resources::mGameLogo->GetState() == EXITED)
		SetState(GAME_SCREEN);
}

void Game::RenderGameScreen()
{
	Resources::mGameBackground->Render();

	if(Resources::mController->IsPressed(CIRCLE))
		SetState(TITLE_SCREEN);
}

void Game::DebugScreen()
{
	oslPrintf("Game state: %d\n", GetState());
	oslPrintf("GameLogo state: %d\n", Resources::mGameLogo->GetState());
	oslPrintf("DropDownMenu state: %d\n", Resources::mDropDownMenu->GetState());
}
