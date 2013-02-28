/*
 * DropDownMenu.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/DropDownMenu.h"

DropDownMenu::DropDownMenu(string pathToImgFile)
				:ScrollingDrawable(pathToImgFile, 0, 0, false)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), POS_Y_RETRACTED );
	SetScrollSpeed(200);
	SetState(RETRACTED);

	mUpDownButtons = new Drawable(Resources::IMG_UP_DOWN_BUTTONS);
	mCrossButton = new Drawable(Resources::IMG_CROSS_BUTTON);
}

DropDownMenu::DropDownMenu(string pathToImgFile, unsigned scrollSpeed)
				:ScrollingDrawable(pathToImgFile, 0, 0, false)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), POS_Y_RETRACTED );
	SetScrollSpeed(scrollSpeed);
	SetState(RETRACTED);

	mUpDownButtons = new Drawable(Resources::IMG_UP_DOWN_BUTTONS);
	mCrossButton = new Drawable(Resources::IMG_CROSS_BUTTON);
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

	mUpDownButtons = new Drawable(Resources::IMG_UP_DOWN_BUTTONS);
	mCrossButton = new Drawable(Resources::IMG_CROSS_BUTTON);
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
	ScrollingDrawable::Render();
	CheckState();
}

void DropDownMenu::CheckState()
{
	if(GetState() == RETRACTING && GetPositionY() <= POS_Y_RETRACTED)
		SetState(RETRACTED);
	if(GetState() == RETRACTED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);

	if(GetState() == EXTENDING && GetPositionY() >= 0)
		SetState(EXTENDED);
	if(GetState() == EXTENDED && GetScrollSpeedY() != 0)
		SetScrollSpeedY(0);

	if(GetState() == EXTENDED)
		RenderMenuItems(Resources::STR_ARRAY_MENU_ITEMS);
}

void DropDownMenu::RenderMenuItems(string* MenuItems)
{
	mUpDownButtons->Draw(16, 7);
	mCrossButton->Draw(429, 14);
}
