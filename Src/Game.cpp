/*
 * Game.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Game.h"

#include "../Includes/Resources.h"

#define DEBUG_MODE 0

Game::Game()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	oslSetTransparentColor(COLOR_TRANSPARENT);
	oslSetQuitOnLoadFailure(1);

	if(DEBUG_MODE)
		oslBenchmarkTest(OSL_BENCH_INIT);

	Resources::LoadResources();
	Resources::AssertResources();

	Resources::mSaveLoad->LoadSaveGame();

	//mGameState = TITLE_SCREEN;
	SetState(TITLE_SCREEN);
	Resources::mScreen->SetSkillsScreenCursorPosition(1);

	Resources::mGameApp = this;
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
		if(DEBUG_MODE)
			oslBenchmarkTest(OSL_BENCH_START);

		Resources::mController->ReadKeys();

		oslStartDrawing();
		oslCls();

		switch(GetState())
		{
		case TITLE_SCREEN:
			Resources::mScreen->RenderTitleScreen();
			break;
		case GAME_SCREEN:
			Resources::mScreen->RenderGameScreen();
			break;
		case TRANSITION_GAME_OVER_SCREEN:
			Resources::mScreen->RenderGameScreen();
			if(Resources::mPlayer->GetState() == Player::DEAD)
				SetState(GAME_OVER_SCREEN);
			break;
		case GAME_OVER_SCREEN:
			Resources::mScreen->RenderGameOverScreen();
			break;
		case SKILLS_SCREEN:
			Resources::mScreen->RenderSkillsScreen();
			break;
		case CONTROLS_SCREEN:
			Resources::mScreen->RenderControlsScreen();
			break;
		}

		if(DEBUG_MODE)
		{
			oslBenchmarkTest(OSL_BENCH_END);
			oslSysBenchmarkDisplay();
			oslPrintf("\n");
			Resources::mScreen->DebugScreen();
		}

		oslEndDrawing();
		oslEndFrame();
		oslSyncFrame();
		//oslSwapBuffers();
	}
}

void Game::SetState(GameState newState)
{
	if(newState == TITLE_SCREEN)
	{
		//Resources::mGameLogo->Reset();
		//Resources::mDropDownMenu->Reset();

		if(Resources::mInGameBGM->IsPlaying())
			Resources::mInGameBGM->Stop();
		if(!Resources::mMainMenuBGM->IsPlaying())
			Resources::mMainMenuBGM->PlayLooped();

		Resources::mSaveLoad->AutoSaveGame();
	}

	if(newState == GAME_SCREEN)
	{
		if(!Resources::mInGameBGM->IsPlaying())
			Resources::mInGameBGM->PlayLooped();

		Resources::mGameLogo->Reset();

		Resources::mPlayer->Reset();
		Resources::mEnemyList->Reset();

		Resources::mSkillsSystem->ResetPlayerScore();
		Resources::mSkillsSystem->ResetEnergy();
		Resources::mSkillsSystem->ResetSkills();
	}

	if(newState == TRANSITION_GAME_OVER_SCREEN)
	{
		Resources::mPlayer->SetState(Player::DYING);
	}

	if(newState == TITLE_SCREEN && GetState() == GAME_OVER_SCREEN)
		Resources::mSkillsSystem->UpdateExperiencePoints();

	if(newState == SKILLS_SCREEN)
		Resources::mScreen->SetSkillsScreenCursorPosition(1);

	mGameState = newState;
}

Game::GameState Game::GetState()
{
	return mGameState;
}
