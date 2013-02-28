/*
 * ScrollDrawable.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/ScrollDrawable.h"

ScrollDrawable::ScrollDrawable(string pathToImgFile)
					:Drawable(pathToImgFile)
{
	SetScrollSpeed(0, 0);
	Reset();
	SetTileable(true);
}

ScrollDrawable::ScrollDrawable(
				string pathToImgFile,
				int scrollSpeedX,
				int scrollSpeedY)
					:Drawable(pathToImgFile)
{
	SetScrollSpeed(scrollSpeedX, scrollSpeedY);
	Reset();
	SetTileable(true);
}

ScrollDrawable::ScrollDrawable(
				string pathToImgFile,
				int scrollSpeedX,
				int scrollSpeedY,
				bool isTileable)
					:Drawable(pathToImgFile)
{
	SetScrollSpeed(scrollSpeedX, scrollSpeedY);
	Reset();
	SetTileable(isTileable);
}

void ScrollDrawable::SetScrollSpeed(int scrollSpeedX, int scrollSpeedY)
{
	mScrollSpeedX = scrollSpeedX;
	mScrollSpeedY = scrollSpeedY;
}

void ScrollDrawable::SetScrollSpeedX(int scrollSpeedX)
{
	mScrollSpeedX = scrollSpeedX;
}

void ScrollDrawable::SetScrollSpeedY(int scrollSpeedY)
{
	mScrollSpeedY = scrollSpeedY;
}

int ScrollDrawable::GetScrollSpeedX()
{
	return mScrollSpeedX;
}

int ScrollDrawable::GetScrollSpeedY()
{
	return mScrollSpeedY;
}

bool ScrollDrawable::IsTileable()
{
	return mIsTileable;
}

void ScrollDrawable::SetTileable(bool isTileable)
{
	mIsTileable = isTileable;
}
void ScrollDrawable::Reset()
{
	SetPositionXY(0,0);
	mPixelsToScrollX = 0;
	mPixelsToScrollY = 0;
}

void ScrollDrawable::Render()
{
	mPixelsToScrollX += mScrollSpeedX / 60.0f;
	if(abs(mPixelsToScrollX) >= 1)
	{
		MoveX(mPixelsToScrollX);
		mPixelsToScrollX -= (int)mPixelsToScrollX;
	}
	if(abs(GetPositionX()) > PSP_SCREEN_WIDTH)
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * -PSP_SCREEN_WIDTH);

	mPixelsToScrollY += mScrollSpeedY / 60.0f;
		if(abs(mPixelsToScrollY) >= 1)
		{
			MoveY(mPixelsToScrollY);
			mPixelsToScrollY -= (int)mPixelsToScrollY;
		}
		if(abs(GetPositionY()) > PSP_SCREEN_HEIGHT)
			MoveY(mScrollSpeedY / abs(mScrollSpeedY) * -PSP_SCREEN_HEIGHT);

	Draw(); //Draw center image

	if(mScrollSpeedX && IsTileable())
	{	//Move left/right by 480px
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * -PSP_SCREEN_WIDTH);
		Draw(); //Draw left/right image
		//Reset to center position
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * PSP_SCREEN_WIDTH);
	}

	if(mScrollSpeedY && IsTileable())
	{	//Move up/down by 272px
		MoveY(mScrollSpeedY / abs(mScrollSpeedY) * -PSP_SCREEN_HEIGHT);
		Draw(); //Draw top/bottom image
		//Reset to center position
		MoveY(mScrollSpeedY / abs(mScrollSpeedY) * PSP_SCREEN_HEIGHT);
	}

	if(mScrollSpeedX && mScrollSpeedY && IsTileable())
	{	//Move left/right by 480px
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * -PSP_SCREEN_WIDTH);
		//Move up/down by 272px
		MoveY(mScrollSpeedY / abs(mScrollSpeedY) * -PSP_SCREEN_HEIGHT);
		Draw(); //Draw diagonal image
		//Reset to center position
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * PSP_SCREEN_WIDTH);
		MoveY(mScrollSpeedY / abs(mScrollSpeedY) * PSP_SCREEN_HEIGHT);
	}

	Draw();
}
