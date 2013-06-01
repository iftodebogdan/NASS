/*
 * DropDownMenu.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/DropDownMenu.h"
#include "../Includes/Resources.h"

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

DropDownMenuState DropDownMenu::GetState()
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
	if(GetState() == RETRACTED && Resources::mController->IsPressed(TRIANGLE))
		SetState(EXTENDING);

	if(GetState() == EXTENDING && GetPositionY() >= 0)
		SetState(EXTENDED);
	if(GetState() == EXTENDED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);
	if(GetState() == EXTENDED && Resources::mController->IsPressed(TRIANGLE))
		SetState(RETRACTING);

	if(GetState() == EXTENDED && Resources::mController->IsPressed(DPAD_DOWN) && mMenuItemIndex < Resources::MENU_ITEMS_COUNT - 1)
		mMenuItemIndex++;
	if(GetState() == EXTENDED && Resources::mController->IsPressed(DPAD_UP) && mMenuItemIndex > 0)
		mMenuItemIndex--;

	if(GetState() == EXTENDED && Resources::mController->IsPressed(CROSS))
		switch(mMenuItemIndex)
		{
		case 0:
			Resources::mGameApp->SetState(SKILLS_SCREEN);
			break;
		case 1:
			oslQuit();
			break;
		default:
			mMenuItemIndex = 0;
			break;
		}
}

void DropDownMenu::RenderMenuItems(string* MenuItems)
{
	Resources::mUpDownButtons->Draw(16, 7);
	Resources::mCrossButton->Draw(429, 14);

	Resources::mCopperPlateFont->DrawTextCentered(MenuItems[mMenuItemIndex], 20);
}
