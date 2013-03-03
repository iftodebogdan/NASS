/*
 * GameLogo.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/GameLogo.h"

GameLogo::GameLogo(string pathToImgFile, int scrollSpeedX, int scrollSpeedY)
			:ScrollingDrawable(pathToImgFile, scrollSpeedX, scrollSpeedY)
{

	mScrollSpeedX_backup = scrollSpeedX;
	mScrollSpeedY_backup = scrollSpeedY;
	Reset();
}

void GameLogo::Reset()
{
	SetScrollSpeed(mScrollSpeedX_backup, mScrollSpeedY_backup);

	if(GetScrollSpeedX() > 0) //Left -> Right
		SetPositionX(-GetWidth());
	else if(GetScrollSpeedX() < 0) //Right -> Left
			SetPositionX(PSP_SCREEN_WIDTH);
		else if(GetScrollSpeedX() == 0) //Center on Ox
				SetPositionX( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2) );

	if(GetScrollSpeedY() > 0) //Up -> Down
		SetPositionY(-GetHeight());
	else if(GetScrollSpeedY() < 0) //Down -> Up
			SetPositionY(PSP_SCREEN_HEIGHT);
		else if(GetScrollSpeedY() == 0) //Center on Oy
			SetPositionY( (PSP_SCREEN_HEIGHT / 2) - (GetHeight() / 2) );

	mGameLogoState = ENTERING;
}

void GameLogo::SetState(GameLogoState newState)
{
	if(newState == ENTERING)
		Reset();

	if(newState == ENTERED || newState == EXITED)
	{
		mGameLogoState = newState;
		if(newState == ENTERED)
		{
			SetPositionX( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2) );
			SetPositionY( (PSP_SCREEN_HEIGHT / 2) - (GetHeight() / 2) );
		}
		else
		{
			if(mScrollSpeedX_backup > 0) //Left -> Right
				SetPositionX(PSP_SCREEN_WIDTH);
			else if(mScrollSpeedX_backup < 0) //Right -> Left
					SetPositionX(-GetWidth());
				else if(mScrollSpeedX_backup == 0) //Center on Ox
						SetPositionX( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2) );

			if(mScrollSpeedY_backup > 0) //Up -> Down
				SetPositionY(PSP_SCREEN_HEIGHT);
			else if(mScrollSpeedY_backup < 0) //Down -> Up
					SetPositionY(-GetHeight());
				else if(mScrollSpeedY_backup == 0) //Center on Oy
					SetPositionY( (PSP_SCREEN_HEIGHT / 2) - (GetHeight() / 2) );
		}
		SetScrollSpeed(0, 0);
	}

	if(newState == EXITING)
	{
		mGameLogoState = newState;
		SetPositionX( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2) );
		SetPositionY( (PSP_SCREEN_HEIGHT / 2) - (GetHeight() / 2) );
		SetScrollSpeed(mScrollSpeedX_backup, mScrollSpeedY_backup);
	}
}

GameLogoState GameLogo::GetState()
{
	return mGameLogoState;
}

void GameLogo::Render()
{
	EvaluateState();
	ScrollingDrawable::Render();
}

void GameLogo::EvaluateState()
{
	if(GetState() == ENTERING)
	{
		if(
			(
				GetScrollSpeedX() > 0 &&
				GetPositionX() >= ( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2) )
			)
			||
			(
				GetScrollSpeedX() < 0 &&
				GetPositionX() <= ( (PSP_SCREEN_WIDTH / 2) - (GetWidth() / 2) )
			)
		  )
					SetScrollSpeedX(0);

		if(
				(
					GetScrollSpeedY() > 0 &&
					GetPositionY() >= ( (PSP_SCREEN_HEIGHT / 2) - (GetHeight() / 2) )
				)
				||
				(
					GetScrollSpeedY() < 0 &&
					GetPositionY() <= ( (PSP_SCREEN_HEIGHT / 2) - (GetHeight() / 2) )
				)
			  )
						SetScrollSpeedY(0);
	}

	if(GetState() == EXITING)
	{
		if(
			(
				GetScrollSpeedX() > 0 &&
				GetPositionX() >= PSP_SCREEN_WIDTH
			)
			||
			(
				GetScrollSpeedX() < 0 &&
				GetPositionX() <= -GetWidth()
			)
		  )
					SetScrollSpeedX(0);

		if(
				(
					GetScrollSpeedY() > 0 &&
					GetPositionY() >= PSP_SCREEN_HEIGHT
				)
				||
				(
					GetScrollSpeedY() < 0 &&
					GetPositionY() <= -GetHeight()
				)
			  )
						SetScrollSpeedY(0);
	}

	if(GetScrollSpeedX() == 0 && GetScrollSpeedY() == 0)
	{
		if(GetState() == ENTERING && GetState() != ENTERED && GetState() != EXITED)
			SetState(ENTERED);
		else
			if(GetState() == EXITING && GetState() != ENTERED && GetState() != EXITED)
				SetState(EXITED);
	}
}
