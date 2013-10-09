/*
 * Screen.cpp
 *
 *  Created on: Jun 7, 2013
 *      Author: Bogdan
 */

#include "../Includes/Screen.hpp"

#include "../Includes/Resources.hpp"
#include <sstream>

Screen::Screen()
{
	SetSkillsScreenCursorPosition(1);
}

void Screen::RenderTitleScreen()
{
	Resources::mGameBackground->Render();
	Resources::mGameLogo->Render();
	if(Resources::mGameLogo->GetState() != GameLogo::EXITING && Resources::mGameLogo->GetState() != GameLogo::EXITED)
		Resources::mDropDownMenu->Render();

	if(Resources::mGameLogo->GetState() == GameLogo::ENTERING && Resources::mController->IsPressed(Controller::CROSS))
		Resources::mGameLogo->SetState(GameLogo::ENTERED);
	else
		if(Resources::mDropDownMenu->GetState() == DropDownMenu::RETRACTED && Resources::mGameLogo->GetState() == GameLogo::ENTERED)
		{
			Resources::mParafontFont->DrawTextCentered(Resources::STR_PRESS_X_TO_START, 240);
			Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_XP_OSD +
														   string(static_cast<ostringstream*>
														   ( &(ostringstream() << Resources::mSkillsSystem->GetExperiencePoints()) )
														   ->str()), 5);
			Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_HI_SCORE_OSD +
														   string(static_cast<ostringstream*>
														   ( &(ostringstream() << Resources::mSkillsSystem->GetHiScore()) )
														   ->str()), 35);
			Resources::mCrossButton->Draw(210, 235);

			if(Resources::mController->IsPressed(Controller::CROSS))
			{
				Resources::mMenuSelect->Play();
				Resources::mGameLogo->SetState(GameLogo::EXITING);
			}
		}

	if(Resources::mGameLogo->GetState() == GameLogo::EXITED)
		SetState(GAME_SCREEN);
}

void Screen::RenderGameScreen()
{
	Resources::mGameBackground->Render();
	Resources::mPlayer->Render();
	Resources::mEnemyList->Render();

	if(Resources::mPlayer->GetState() == Player::ALIVE)
		Resources::mSkillsSystem->Render();

	if(CollisionDetection::CheckForPixelPerfectCollisions(Resources::mPlayer, Resources::mEnemyList) &&
			GetState() != TRANSITION_GAME_OVER_SCREEN)
	{
		Resources::mPlayerExplosion->Play();
		SetState(TRANSITION_GAME_OVER_SCREEN);
	}


	if(Resources::mController->IsPressed(Controller::START))
	{
		Resources::mMenuSelect->Play();

		if(oslMessageBox(
			Resources::STR_RETURN_TO_TITLE_SCREEN_MESSAGE.c_str(),
			Resources::STR_RETURN_TO_TITLE_SCREEN_TITLE.c_str(),
			oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
			{
				Resources::mMenuSelect->Play();
				SetState(TITLE_SCREEN);
			}
		else
			Resources::mMenuCancel->Play();
	}
}

void Screen::RenderGameOverScreen()
{
	Resources::mGameBackground->Render();
	Resources::mEnemyList->Render();

	oslDrawFillRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 150));
	oslDrawRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 255));

	string strGameOverXPEarnedMessage = Resources::STR_GAME_OVER_XP_EARNED_MESSAGE +
								string(static_cast<ostringstream*>( &(ostringstream() << Resources::mSkillsSystem->GetPlayerScore() / SCORE_TO_XP_RATIO) )->str());
	Resources::mParafontFont->DrawTextCentered(Resources::STR_GAME_OVER_TITLE, 70);
	Resources::mCopperPlateFont->DrawTextCentered(Resources::STR_GAME_OVER_MESSAGE, 120);
	Resources::mCopperPlateFont->DrawTextCentered(strGameOverXPEarnedMessage, 150);
	if(Resources::mSkillsSystem->GetPlayerScore() > Resources::mSkillsSystem->GetHiScore())
		Resources::mCopperPlateFont->DrawTextCentered(Resources::STR_GAME_OVER_NEW_HI_SCORE_MESSAGE, 180);

	Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_PRESS_X_TO_CONTINUE, 240);
	Resources::mCrossButton->Draw(PSP_SCREEN_WIDTH - Resources::mCrossButton->GetWidth() - 5, 240);

	if(Resources::mController->IsPressed(Controller::CROSS))
	{
		Resources::mMenuSelect->Play();
		SetState(TITLE_SCREEN);
	}
}

void Screen::DisplaySkillLevel(unsigned skillLevel, int posX, int posY)
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

void Screen::SetSkillsScreenCursorPosition(unsigned newSkillsScreenCursorPosition)
{
	if(newSkillsScreenCursorPosition >= 1 && newSkillsScreenCursorPosition <= 4)
		mSkillsScreenCursor = newSkillsScreenCursorPosition;
	else
		mSkillsScreenCursor = 1;
}

void Screen::RenderSkillsScreen()
{
	Resources::mGameBackground->Render();

	oslDrawFillRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 150));
	oslDrawRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 255));

	unsigned selectedSkillLevel = 0;
	switch(mSkillsScreenCursor)
	{
	case 1:
		selectedSkillLevel = Resources::mSkillsSystem->GetWarpLevel();
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
	default:
		mSkillsScreenCursor = 1;
		break;
	};

	if(Resources::mController->IsHeld(Controller::TRIANGLE))
	{
		string infoMessage;
		switch(mSkillsScreenCursor)
		{
		case 1:
			infoMessage = Resources::STR_WARP_INFO_MESSAGE;
			break;
		case 2:
			infoMessage = Resources::STR_DEMATERIALIZE_INFO_MESSAGE;
			break;
		case 3:
			infoMessage = Resources::STR_OVERDRIVE_INFO_MESSAGE;
			break;
		case 4:
			infoMessage = Resources::STR_FORCE_FIELD_INFO_MESSAGE;
			break;
		};

		int textBoxHeight = oslGetTextBoxHeight(PSP_SCREEN_WIDTH - 40 * 2, PSP_SCREEN_HEIGHT, infoMessage.c_str(), 0);
		oslSetTextColor(COLOR_BLACK);
		oslSetBkColor(RGBA(0,0,0,0));
		oslDrawTextBox(40,
					   (PSP_SCREEN_HEIGHT - textBoxHeight) / 2,
					   PSP_SCREEN_WIDTH - 40,
					   PSP_SCREEN_HEIGHT - (PSP_SCREEN_HEIGHT - textBoxHeight) / 2,
					   infoMessage.c_str(), 0);

		return;
	}

	oslDrawGradientRect(35,
						35 + (mSkillsScreenCursor - 1) * 25,
						300,
						65 + (mSkillsScreenCursor - 1) * 25,
						RGBA(0, 0, 255, 127),
						RGBA(255, 255, 255, 0),
						RGBA(0, 0, 255, 127),
						RGBA(255, 255, 255, 0));

	Resources::mCopperPlateFont->DrawText(Resources::STR_WARP_SKILL, 40, 40);
	DisplaySkillLevel(Resources::mSkillsSystem->GetWarpLevel(), 300, 40);

	Resources::mCopperPlateFont->DrawText(Resources::STR_DEMATERIALIZE_SKILL, 40, 65);
	DisplaySkillLevel(Resources::mSkillsSystem->GetDematerializeLevel(), 300, 65);

	Resources::mCopperPlateFont->DrawText(Resources::STR_OVERDRIVE_SKILL, 40, 90);
	DisplaySkillLevel(Resources::mSkillsSystem->GetOverdriveLevel(), 300, 90);

	Resources::mCopperPlateFont->DrawText(Resources::STR_FORCE_FIELD_SKILL, 40, 115);
	DisplaySkillLevel(Resources::mSkillsSystem->GetForceFieldLevel(), 300, 115);

	oslDrawFillRect(40, PSP_SCREEN_HEIGHT / 2 + 20, PSP_SCREEN_WIDTH - 40, PSP_SCREEN_HEIGHT -40, RGBA(255, 255, 255, 127));
	oslDrawRect(40, PSP_SCREEN_HEIGHT / 2 + 20, PSP_SCREEN_WIDTH - 40, PSP_SCREEN_HEIGHT -40, COLOR_BLACK);

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

	unsigned driveCoreLoad =(Resources::mSkillsSystem->GetWarpLevel() +
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

	Resources::mTriangleButton->Draw(5, 240);
	Resources::mParafontFont->DrawText(Resources::STR_SKILLS_SCREEN_INFO_BUTTON_LABEL, 40, 240);

	Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_PRESS_O_TO_GO_BACK, 240);
	Resources::mCircleButton->Draw(PSP_SCREEN_WIDTH - Resources::mCircleButton->GetWidth() - 5, 240);

	if(Resources::mController->IsPressed(Controller::CIRCLE))
	{
		Resources::mMenuCancel->Play();
		SetState(TITLE_SCREEN);
	}

	if(Resources::mController->IsPressed(Controller::DPAD_UP))
		if(mSkillsScreenCursor > 1)
		{
			Resources::mMenuNavigate->Play();
			mSkillsScreenCursor--;
		}
	if(Resources::mController->IsPressed(Controller::DPAD_DOWN))
		if(mSkillsScreenCursor < 4)
		{
			Resources::mMenuNavigate->Play();
			mSkillsScreenCursor++;
		}

	if(Resources::mController->IsPressed(Controller::CROSS))
	{
		Resources::mMenuSelect->Play();
		if(Resources::mSkillsSystem->GetSkillLevelByIndex(mSkillsScreenCursor) == 5)
		{
			oslMessageBox(
				Resources::STR_SKILL_LEVEL_5_MESSAGE.c_str(),
				Resources::STR_SKILL_LEVEL_5_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
			Resources::mMenuSelect->Play();
		}
		else
			if(driveCoreLoad >= 100)
			{
				oslMessageBox(
					Resources::STR_DRIVE_CORE_OVERLOADED_MESSAGE.c_str(),
					Resources::STR_DRIVE_CORE_OVERLOADED_TITLE.c_str(),
					oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
				Resources::mMenuSelect->Play();
			}
			else
				if(Resources::mSkillsSystem->SkillLevelUpCost(selectedSkillLevel) > Resources::mSkillsSystem->GetExperiencePoints())
				{
					oslMessageBox(
						Resources::STR_SKILL_NO_XP_MESSAGE.c_str(),
						Resources::STR_SKILL_NO_XP_TITLE.c_str(),
						oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
					Resources::mMenuSelect->Play();
				}
				else
					if(oslMessageBox(
						Resources::STR_SKILL_LEVEL_UP_CONFIRMATION_MESSAGE.c_str(),
						Resources::STR_SKILL_LEVEL_UP_CONFIRMATION_TITLE.c_str(),
						oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
						{
							Resources::mMenuSelect->Play();
							switch(mSkillsScreenCursor)
							{
							case 1:
								Resources::mSkillsSystem->LevelUpWarp();
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
					else
						Resources::mMenuCancel->Play();
	}
	if(Resources::mController->IsPressed(Controller::SQUARE))
	{
		Resources::mMenuSelect->Play();

		if(Resources::mSkillsSystem->GetSkillLevelByIndex(mSkillsScreenCursor) == 0)
		{
			oslMessageBox(
				Resources::STR_SKILL_LEVEL_0_MESSAGE.c_str(),
				Resources::STR_SKILL_LEVEL_0_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
			Resources::mMenuSelect->Play();
		}
		else
			if(oslMessageBox(
				Resources::STR_SKILL_REFUND_CONFIRMATION_MESSAGE.c_str(),
				Resources::STR_SKILL_REFUND_CONFIRMATION_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
				{
					Resources::mMenuSelect->Play();
					switch(mSkillsScreenCursor)
					{
					case 1:
						Resources::mSkillsSystem->RefundWarp();
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
			else
				Resources::mMenuCancel->Play();
	}
}

void Screen::RenderControlsScreen()
{
	Resources::mGameBackground->Render();

	oslDrawFillRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 150));
	oslDrawRect(20, 20, PSP_SCREEN_WIDTH - 20, PSP_SCREEN_HEIGHT - 20, RGBA(255, 255, 255, 255));

	Resources::mPSPControls->Draw(0, 0);

	Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_PRESS_O_TO_GO_BACK, 240);
	Resources::mCircleButton->Draw(PSP_SCREEN_WIDTH - Resources::mCircleButton->GetWidth() - 5, 240);

	if(Resources::mController->IsPressed(Controller::CIRCLE))
	{
		Resources::mMenuCancel->Play();
		SetState(TITLE_SCREEN);
	}
}

void Screen::SetState(ScreenState newState)
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

	mScreenState = newState;
}

Screen::ScreenState Screen::GetState()
{
	return mScreenState;
}
