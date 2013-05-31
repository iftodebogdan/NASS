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
	oslSetKeyAnalogToDPad(80);

	if(DEBUG_MODE)
		oslBenchmarkTest(OSL_BENCH_INIT);

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
		if(DEBUG_MODE)
			oslBenchmarkTest(OSL_BENCH_START);

		Resources::mController->ReadKeys();

		oslStartDrawing();
		oslCls();

		if(GetState() == TITLE_SCREEN)
			RenderTitleScreen();

		if(GetState() == GAME_SCREEN || GetState() == TRANSITION_GAME_OVER_SCREEN)
			RenderGameScreen();

		if(GetState() == TRANSITION_GAME_OVER_SCREEN)
			if(Resources::mPlayer->GetState() == DEAD)
				SetState(GAME_OVER_SCREEN);

		if(GetState() == GAME_OVER_SCREEN)
			RenderGameOverScreen();

		if(DEBUG_MODE)
		{
			oslBenchmarkTest(OSL_BENCH_END);
			oslSysBenchmarkDisplay();
			oslPrintf("\n");
			DebugScreen();
		}

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
		Resources::mSaveLoad->AutoSaveGame();
	}

	if(newState == GAME_SCREEN)
	{
		Resources::mPlayer->Reset();
		Resources::mEnemyList->Reset();
	}

	if(newState == TRANSITION_GAME_OVER_SCREEN)
	{
		Resources::mPlayer->SetState(DYING);
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
			Resources::mParafontFont->DrawTextCentered(Resources::STR_PRESS_X_TO_START, 240);
			Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_XP_OSD + string(static_cast<ostringstream*>( &(ostringstream() << Resources::mSkillsSystem->GetExperiencePoints()) )->str()), 5);
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
	Resources::mPlayer->Render();
	Resources::mEnemyList->Render();
	Resources::mSkillsSystem->RenderScore();
	if(CollisionDetection::CheckForCollisions(Resources::mPlayer, Resources::mEnemyList) &&
	   GetState() != TRANSITION_GAME_OVER_SCREEN)
			SetState(TRANSITION_GAME_OVER_SCREEN);


	if(Resources::mController->IsPressed(START))
		if(oslMessageBox(
			Resources::STR_QUIT_MESSAGE.c_str(),
			Resources::STR_QUIT_TITLE.c_str(),
			oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
				SetState(TITLE_SCREEN);
}

void Game::RenderGameOverScreen()
{
	Resources::mGameBackground->Render();
	Resources::mEnemyList->Render();
	Resources::mSkillsSystem->RenderScore();
	string strGameOverMessage = Resources::STR_GAME_OVER_MESSAGE +
								string(static_cast<ostringstream*>( &(ostringstream() << Resources::mSkillsSystem->GetPlayerScore()) )->str());
	Resources::mSkillsSystem->UpdateExperiencePoints();

	if(oslMessageBox(
		strGameOverMessage.c_str(),
		Resources::STR_GAME_OVER_TITLE.c_str(),
		oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0)) == OSL_MB_OK)
			SetState(TITLE_SCREEN);
}

void Game::DebugScreen()
{
	oslSetBkColor(COLOR_BLACK);
	oslSetTextColor(COLOR_WHITE);

	oslPrintf("Game state: %d\n", GetState());
	oslPrintf("GameLogo state: %d\n", Resources::mGameLogo->GetState());
	oslPrintf("DropDownMenu state: %d\n", Resources::mDropDownMenu->GetState());
	oslPrintf("Enemy count: %d\n", Resources::mEnemyList->GetEnemyCount());
	oslPrintf("mEnemySpeedModifier: %d\n", Resources::mEnemyList->GetEnemySpeedModifier());
	oslPrintf("timewarp level: %d\n", Resources::mSkillsSystem->GetTimeWarpLevel());
}
