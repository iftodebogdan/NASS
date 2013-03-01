/*
 * DropDownMenu.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/DropDownMenu.h"
#include "../Includes/Resources.h"

DropDownMenu::DropDownMenu(string pathToImgFile)
				:ScrollingDrawable(pathToImgFile, 0, 0, false)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), POS_Y_RETRACTED );
	SetScrollSpeed(200);
	SetState(RETRACTED);

	mMenuItemIndex = 0;
}

DropDownMenu::DropDownMenu(string pathToImgFile, unsigned scrollSpeed)
				:ScrollingDrawable(pathToImgFile, 0, 0, false)
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
					:ScrollingDrawable(pathToImgFile, 0, 0, false)
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
	CheckState();
	ScrollingDrawable::Render();
	if(GetState() == EXTENDED)
		RenderMenuItems(Resources::STR_MENU_ITEMS);
}

void DropDownMenu::CheckState()
{
	if(GetState() == RETRACTING && GetPositionY() <= POS_Y_RETRACTED)
		Reset(); //SetState(RETRACTED);
	if(GetState() == RETRACTED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);
	if(GetState() == RETRACTED && Controller::IsPressed(TRIANGLE))
		SetState(EXTENDING);

	if(GetState() == EXTENDING && GetPositionY() >= 0)
		SetState(EXTENDED);
	if(GetState() == EXTENDED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);
	if(GetState() == EXTENDED && Controller::IsPressed(TRIANGLE))
		SetState(RETRACTING);

	if(GetState() == EXTENDED && Controller::IsPressed(DPAD_DOWN) && mMenuItemIndex < Resources::MENU_ITEMS_COUNT - 1)
		mMenuItemIndex++;
	if(GetState() == EXTENDED && Controller::IsPressed(DPAD_UP) && mMenuItemIndex > 0)
		mMenuItemIndex--;

	if(GetState() == EXTENDED && Controller::IsPressed(CROSS))
		switch(mMenuItemIndex)
		{
		case 0:
			//DoSomething(0);
			break;
		case 1:
			//DoSomething(1);
			break;
		case 2:
			//DoSomething(2);
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

	Font::DrawTextCentered(MenuItems[mMenuItemIndex], 240, 15);
}
