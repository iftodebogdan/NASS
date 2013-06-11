/*
 * DropDownMenu.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/DropDownMenu.h"

#include "../Includes/Resources.h"
#include "../Includes/Controller.h"
#include "../Includes/Font.h"

#define POS_Y_RETRACTED -GetHeight() + 16 -1

DropDownMenu::DropDownMenu(string pathToImgFile)
				:ScrollingDrawable(pathToImgFile, 0, 0)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), POS_Y_RETRACTED );
	SetScrollSpeed(200);
	SetState(RETRACTED);

	mMenuItemIndex = 0;
}

DropDownMenu::DropDownMenu(string pathToImgFile, unsigned scrollSpeed)
				:ScrollingDrawable(pathToImgFile, 0, 0)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), POS_Y_RETRACTED );
	SetScrollSpeed(scrollSpeed);
	SetState(RETRACTED);

	mMenuItemIndex = 0;
}

DropDownMenu::DropDownMenu(
				string pathToImgFile,
				unsigned scrollSpeed,
				DropDownMenuState dropDownMenuState)
					:ScrollingDrawable(pathToImgFile, 0, 0)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), POS_Y_RETRACTED );
	SetScrollSpeed(scrollSpeed);
	SetState(dropDownMenuState);

	mMenuItemIndex = 0;
}

void DropDownMenu::Reset()
{
	SetState(RETRACTED);
	mMenuItemIndex = 0;
}

void DropDownMenu::SetState(DropDownMenuState newState)
{
	if(newState == EXTENDING)
	{
		SetScrollSpeedY(GetScrollSpeed());
		SetPositionY(POS_Y_RETRACTED);
	}

	if(newState == EXTENDED)
		SetPositionY(0);

	if(newState == RETRACTING)
	{
		SetScrollSpeedY(-GetScrollSpeed());
		SetPositionY(0);
	}

	if(newState == RETRACTED)
		SetPositionY(POS_Y_RETRACTED);

	mDropDownMenuState = newState;
}

DropDownMenu::DropDownMenuState DropDownMenu::GetState()
{
	return mDropDownMenuState;
}

void DropDownMenu::SetScrollSpeed(unsigned scrollSpeed)
{
	mScrollSpeed = scrollSpeed;
}

unsigned DropDownMenu::GetScrollSpeed()
{
	return mScrollSpeed;
}

void DropDownMenu::Render()
{
	EvaluateState();
	ScrollingDrawable::Render();
	if(GetState() == EXTENDED)
		RenderMenuItems(Resources::STR_MENU_ITEMS);
}

void DropDownMenu::EvaluateState()
{
	if(GetState() == RETRACTING && GetPositionY() <= POS_Y_RETRACTED)
		Reset(); //SetState(RETRACTED);
	if(GetState() == RETRACTED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);
	if(GetState() == RETRACTED && Resources::mController->IsPressed(Controller::TRIANGLE))
	{
		Resources::mDropDownMenuSweep->Play();
		SetState(EXTENDING);
	}

	if(GetState() == EXTENDING && GetPositionY() >= 0)
		SetState(EXTENDED);
	if(GetState() == EXTENDED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);
	if(GetState() == EXTENDED && (Resources::mController->IsPressed(Controller::TRIANGLE) || Resources::mController->IsPressed(Controller::CIRCLE)))
	{
		Resources::mDropDownMenuSweep->Play();
		SetState(RETRACTING);
	}

	if(GetState() == EXTENDED && Resources::mController->IsPressed(Controller::DPAD_DOWN) && mMenuItemIndex < Resources::MENU_ITEMS_COUNT - 1)
	{
		Resources::mMenuNavigate->Play();
		mMenuItemIndex++;
	}
	if(GetState() == EXTENDED && Resources::mController->IsPressed(Controller::DPAD_UP) && mMenuItemIndex > 0)
	{
		Resources::mMenuNavigate->Play();
		mMenuItemIndex--;
	}

	if(GetState() == EXTENDED && Resources::mController->IsPressed(Controller::CROSS))
	{
		Resources::mMenuSelect->Play();

		switch(mMenuItemIndex)
		{
		case 0:
			Resources::mScreen->SetState(Screen::SKILLS_SCREEN);
			break;
		case 1:
			Resources::mScreen->SetState(Screen::CONTROLS_SCREEN);
			break;
		case 2:
			if(oslMessageBox(
				Resources::STR_RESET_PROGRESS_MESSAGE.c_str(),
				Resources::STR_RESET_PROGRESS_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_NO)
				{
					Resources::mMenuCancel->Play();
					Resources::mSaveLoad->ResetProgress();
				}
			else
				Resources::mMenuSelect->Play();
			break;
		case 3:
			Resources::mDebug->SetDebugMode(!Resources::mDebug->GetDebugMode());
			if(Resources::mDebug->GetDebugMode())
			{
				oslMessageBox(
					Resources::STR_DEBUG_MODE_ON_MESSAGE.c_str(),
					Resources::STR_DEBUG_MODE_ON_TITLE.c_str(),
					oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
				Resources::mMenuSelect->Play();
			}
			else
			{
				oslMessageBox(
					Resources::STR_DEBUG_MODE_OFF_MESSAGE.c_str(),
					Resources::STR_DEBUG_MODE_OFF_TITLE.c_str(),
					oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
				Resources::mMenuSelect->Play();
			}
			break;
		case 4:
			if(oslMessageBox(
				Resources::STR_QUIT_GAME_MESSAGE.c_str(),
				Resources::STR_QUIT_GAME_TITLE.c_str(),
				oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_YES)
				{
					Resources::mMenuSelect->Play();
					oslQuit();
				}
			else
				Resources::mMenuCancel->Play();
			break;
		default:
			mMenuItemIndex = 0;
			break;
		}
	}
}

void DropDownMenu::RenderMenuItems(string* MenuItems)
{
	Resources::mUpDownButtons->Draw(16, 7);
	Resources::mCrossButton->Draw(429, 14);

	Resources::mCopperPlateFont->DrawTextCentered(MenuItems[mMenuItemIndex], 20);
}
