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
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), -GetHeight() + 16 );
	SetScrollSpeed(100);
	SetState(RETRACTED);
}

DropDownMenu::DropDownMenu(string pathToImgFile, unsigned scrollSpeed)
				:ScrollingDrawable(pathToImgFile, 0, 0, false)
{
	SetPositionXY( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2), -GetHeight() + 16 );
	SetScrollSpeed(scrollSpeed);
	SetState(RETRACTED);
}

void DropDownMenu::SetState(DropDownMenuState newState)
{
	if(newState == EXTENDING)
		SetScrollSpeedY(GetScrollSpeed());
	if(newState == EXTENDED)
		SetPositionY(0);
	if(newState == RETRACTING)
		SetScrollSpeedY(-GetScrollSpeed());
	if(newState == RETRACTED)
		SetPositionY(-GetHeight() + 16);

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
}

void DropDownMenu::CheckState()
{
	if(GetState() == RETRACTING && GetPositionY() <= -GetHeight() + 16)
		SetState(RETRACTED);
	if(GetState() == RETRACTED && GetScrollSpeedY() != 0)
			SetScrollSpeedY(0);

	if(GetState() == EXTENDING && GetPositionY() >= 0)
		SetState(EXTENDED);
	if(GetState() == EXTENDED && GetScrollSpeedY() != 0)
			SetScrollSpeedY(0);
}
