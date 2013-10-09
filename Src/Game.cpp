/*
 * Game.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Game.hpp"

#include "../Includes/Resources.hpp"

Game::Game()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	oslSetTransparentColor(COLOR_TRANSPARENT);
	oslSetQuitOnLoadFailure(1);

	Resources::LoadResources();
	Resources::AssertResources();
	Resources::mSaveLoad->LoadSaveGame();
	Resources::mScreen->SetState(Screen::TITLE_SCREEN);
	Resources::mGameApp = this;

	if(Resources::mDebug->GetDebugMode())
		Resources::mDebug->InitBenchmark();
}

Game::~Game()
{
	oslEndGfx();
	oslDeinitAudio();
	oslQuit();
}

void Game::Run()
{
	oslShowSplashScreen(1);

	while (!osl_quit)
	{
		if(Resources::mDebug->GetDebugMode())
			Resources::mDebug->StartBenckmark();

		Resources::mController->ReadKeys();

		oslStartDrawing();
		oslCls();

		switch(Resources::mScreen->GetState())
		{
		case Screen::TITLE_SCREEN:
			Resources::mScreen->RenderTitleScreen();
			break;
		case Screen::GAME_SCREEN:
			Resources::mScreen->RenderGameScreen();
			break;
		case Screen::TRANSITION_GAME_OVER_SCREEN:
			Resources::mScreen->RenderGameScreen();
			if(Resources::mPlayer->GetState() == Player::DEAD)
				Resources::mScreen->SetState(Screen::GAME_OVER_SCREEN);
			break;
		case Screen::GAME_OVER_SCREEN:
			Resources::mScreen->RenderGameOverScreen();
			break;
		case Screen::SKILLS_SCREEN:
			Resources::mScreen->RenderSkillsScreen();
			break;
		case Screen::CONTROLS_SCREEN:
			Resources::mScreen->RenderControlsScreen();
			break;
		}

		if(Resources::mDebug->GetDebugMode())
		{
			Resources::mDebug->EndBenchmark();
			Resources::mDebug->DebugScreen();
		}

		oslEndDrawing();
		oslEndFrame();
		oslSyncFrame();
		//oslSwapBuffers();
	}
}
