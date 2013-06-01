/*
 * Game.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Game.h"
#include "../Includes/Resources.h"

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
	mSkillsScreenCursor = 1;

	Resources::mGameApp = this;
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

		switch(GetState())
		{
		case TITLE_SCREEN:
			RenderTitleScreen();
			break;
		case GAME_SCREEN:
			RenderGameScreen();
			break;
		case TRANSITION_GAME_OVER_SCREEN:
			RenderGameScreen();
			if(Resources::mPlayer->GetState() == DEAD)
				SetState(GAME_OVER_SCREEN);
			break;
		case GAME_OVER_SCREEN:
			RenderGameOverScreen();
			break;
		case SKILLS_SCREEN:
			RenderSkillsScreen();
			break;
		}

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
		Resources::mSkillsSystem->ResetPlayerScore();
		Resources::mSkillsSystem->ResetEnergy();
	}

	if(newState == TRANSITION_GAME_OVER_SCREEN)
	{
		Resources::mPlayer->SetState(DYING);
	}

	if(newState == SKILLS_SCREEN)
	{
		mSkillsScreenCursor = 1;
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
			Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_XP_OSD +
														   string(static_cast<ostringstream*>
														   ( &(ostringstream() << Resources::mSkillsSystem->GetExperiencePoints()) )
														   ->str()), 5);
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
	Resources::mSkillsSystem->Render();
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

void Game::DisplaySkillLevel(unsigned skillLevel, int posX, int posY)
{
	if(skillLevel > 5)
		return;

	oslDrawRect(posX, posY, posX+100, posY+20, COLOR_BLUE);
	for(int i = 1; i <= (int)skillLevel; i++)
	{
		oslDrawFillRect(posX + (i-1) * 20 + 2,
						posY + 2,
						posX + i * 20 - 2,
						posY + 20 - 2,
						RGBA(0, 0, 255, 175));
	}
}

void Game::RenderSkillsScreen()
{
	Resources::mGameBackground->Render();

	oslDrawFillRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 150));
	oslDrawRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 255));

	oslDrawGradientRect(35,
						35 + (mSkillsScreenCursor - 1) * 25,
						300,
						65 + (mSkillsScreenCursor - 1) * 25,
						RGBA(0, 0, 255, 127),
						RGBA(255, 255, 255, 0),
						RGBA(0, 0, 255, 127),
						RGBA(255, 255, 255, 0));

	Resources::mCopperPlateFont->DrawText(Resources::STR_TIME_WARP_SKILL, 40, 40);
	DisplaySkillLevel(Resources::mSkillsSystem->GetTimeWarpLevel(), 300, 40);

	Resources::mCopperPlateFont->DrawText(Resources::STR_DEMATERIALIZE_SKILL, 40, 65);
	DisplaySkillLevel(Resources::mSkillsSystem->GetDematerializeLevel(), 300, 65);

	Resources::mCopperPlateFont->DrawText(Resources::STR_OVERDRIVE_SKILL, 40, 90);
	DisplaySkillLevel(Resources::mSkillsSystem->GetOverdriveLevel(), 300, 90);

	Resources::mCopperPlateFont->DrawText(Resources::STR_FORCE_FIELD_SKILL, 40, 115);
	DisplaySkillLevel(Resources::mSkillsSystem->GetForceFieldLevel(), 300, 115);

	oslDrawFillRect(40, PSP_SCREEN_HEIGHT / 2 + 20, PSP_SCREEN_WIDTH - 40, PSP_SCREEN_HEIGHT -40, RGBA(255, 255, 255, 127));
	oslDrawRect(40, PSP_SCREEN_HEIGHT / 2 + 20, PSP_SCREEN_WIDTH - 40, PSP_SCREEN_HEIGHT -40, COLOR_BLACK);

	unsigned selectedSkillLevel = 0;
	switch(mSkillsScreenCursor)
	{
	case 1:
		selectedSkillLevel = Resources::mSkillsSystem->GetTimeWarpLevel();
		break;
	case 2:
		selectedSkillLevel = Resources::mSkillsSystem->GetDematerializeLevel();
		break;
	case 3:
		selectedSkillLevel = Resources::mSkillsSystem->GetOverdriveLevel();
		break;
	case 4:
		selectedSkillLevel = Resources::mSkillsSystem->GetForceFieldLevel();
		break;
	};

	Resources::mCrossButton_small->Draw(60, PSP_SCREEN_HEIGHT / 2 + 20 + 10);
	Resources::mSmallStoneFont->DrawText(Resources::STR_SKILLS_SCREEN_XP_COST +
										 string(static_cast<ostringstream*>
										 ( &(ostringstream() << Resources::mSkillsSystem->SkillLevelUpCost(selectedSkillLevel)) )
									 	 ->str()) +
									 	Resources::STR_SKILLS_SCREEN_XP_COST_2,
										 60 + Resources::mCrossButton_small->GetWidth() + 2, PSP_SCREEN_HEIGHT / 2 + 20 + 10);

	Resources::mSquareButton_small->Draw(60, PSP_SCREEN_HEIGHT / 2 + 20 + 10 + 15);
	Resources::mSmallStoneFont->DrawText(Resources::STR_SKILLS_SCREEN_REFUND +
										 string(static_cast<ostringstream*>
										 ( &(ostringstream() << Resources::mSkillsSystem->SkillRefundValue(selectedSkillLevel)) )
										 ->str()) +
										 Resources::STR_SKILLS_SCREEN_REFUND_2,
										 60 + Resources::mSquareButton_small->GetWidth() + 2, PSP_SCREEN_HEIGHT / 2 + 20 + 10 + 15);

	unsigned driveCoreLoad =(Resources::mSkillsSystem->GetTimeWarpLevel() +
							 Resources::mSkillsSystem->GetDematerializeLevel() +
							 Resources::mSkillsSystem->GetOverdriveLevel() +
							 Resources::mSkillsSystem->GetForceFieldLevel() ) * 10;
	Resources::mSmallStoneFont->DrawText(Resources::STR_DRIVE_CORE_LOAD +
										 string(static_cast<ostringstream*>
										 ( &(ostringstream() << driveCoreLoad) )
										 ->str()) + "%",
										 60, PSP_SCREEN_HEIGHT / 2 + 20 + 10 + 15 * 2);

	Resources::mSmallStoneFont->DrawText(Resources::STR_SKILLS_SCREEN_AVAILABLE_XP +
										 string(static_cast<ostringstream*>
									 	 ( &(ostringstream() << Resources::mSkillsSystem->GetExperiencePoints()) )
									 	 ->str()),
										 60, PSP_SCREEN_HEIGHT / 2 + 20 + 10 + 15 * 3);

	Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_PRESS_O_TO_GO_BACK, 240);
	Resources::mCircleButton->Draw(PSP_SCREEN_WIDTH - Resources::mCircleButton->GetWidth() - 5, 240);

	if(Resources::mController->IsPressed(CIRCLE))
		Resources::mGameApp->SetState(TITLE_SCREEN);

	if(Resources::mController->IsPressed(DPAD_UP))
		if(mSkillsScreenCursor > 1)
			mSkillsScreenCursor--;
	if(Resources::mController->IsPressed(DPAD_DOWN))
		if(mSkillsScreenCursor < 4)
			mSkillsScreenCursor++;

	if(Resources::mController->IsPressed(CROSS))
	{
		if(Resources::mSkillsSystem->GetSkillLevelByIndex(mSkillsScreenCursor) == 5)
			oslMessageBox(
				Resources::STR_SKILL_LEVEL_5_MESSAGE.c_str(),
				Resources::STR_SKILL_LEVEL_5_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
		else
			if(driveCoreLoad >= 100)
				oslMessageBox(
					Resources::STR_DRIVE_CORE_OVERLOADED_MESSAGE.c_str(),
					Resources::STR_DRIVE_CORE_OVERLOADED_TITLE.c_str(),
					oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
			else
				if(oslMessageBox(
					Resources::STR_SKILL_LEVEL_UP_CONFIRMATION_MESSAGE.c_str(),
					Resources::STR_SKILL_LEVEL_UP_CONFIRMATION_TITLE.c_str(),
					oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
						switch(mSkillsScreenCursor)
						{
						case 1:
							Resources::mSkillsSystem->LevelUpTimeWarp();
							break;
						case 2:
							Resources::mSkillsSystem->LevelUpDematerialize();
							break;
						case 3:
							Resources::mSkillsSystem->LevelUpOverdrive();
							break;
						case 4:
							Resources::mSkillsSystem->LevelUpForceField();
							break;
						};
	}
	if(Resources::mController->IsPressed(SQUARE))
	{
		if(Resources::mSkillsSystem->GetSkillLevelByIndex(mSkillsScreenCursor) == 0)
			oslMessageBox(
				Resources::STR_SKILL_LEVEL_0_MESSAGE.c_str(),
				Resources::STR_SKILL_LEVEL_0_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
		else
			if(oslMessageBox(
				Resources::STR_SKILL_REFUND_CONFIRMATION_MESSAGE.c_str(),
				Resources::STR_SKILL_REFUND_CONFIRMATION_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
					switch(mSkillsScreenCursor)
					{
					case 1:
						Resources::mSkillsSystem->RefundTimeWarp();
						break;
					case 2:
						Resources::mSkillsSystem->RefundDematerialize();
						break;
					case 3:
						Resources::mSkillsSystem->RefundOverdrive();
						break;
					case 4:
						Resources::mSkillsSystem->RefundForceField();
						break;
					};
	}
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
	oslPrintf("mEnergy: %d\n", Resources::mSkillsSystem->GetEnergy());
}
