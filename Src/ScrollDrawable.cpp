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
	oslAssert(GetWidth() == PSP_SCREEN_WIDTH && GetHeight() == PSP_SCREEN_HEIGHT );

	SetScrollSpeed(0, 0);
	Reset();
}

ScrollDrawable::ScrollDrawable(
				string pathToImgFile,
				int scrollSpeedX,
				int scrollSpeedY)
					:Drawable(pathToImgFile)
{
	oslAssert(GetWidth() == PSP_SCREEN_WIDTH && GetHeight() == PSP_SCREEN_HEIGHT );

	SetScrollSpeed(scrollSpeedX, scrollSpeedY);
	Reset();
}

void ScrollDrawable::SetScrollSpeed(int scrollSpeedX, int scrollSpeedY)
{
	mScrollSpeedX = scrollSpeedX;
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
	if(abs(GetPositionX()) >= PSP_SCREEN_WIDTH)
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * -PSP_SCREEN_WIDTH);

	mPixelsToScrollY += mScrollSpeedY / 60.0f;
		if(abs(mPixelsToScrollY) >= 1)
		{
			MoveY(mPixelsToScrollY);
			mPixelsToScrollY -= (int)mPixelsToScrollY;
		}
		if(abs(GetPositionY()) >= PSP_SCREEN_HEIGHT)
			MoveY(mScrollSpeedY / abs(mScrollSpeedY) * -PSP_SCREEN_HEIGHT);

	Draw(); //Draw center image

	if(mScrollSpeedX)
	{	//Move left/right by 480px
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * -PSP_SCREEN_WIDTH);
		Draw(); //Draw left/right image
		//Reset to center position
		MoveX(mScrollSpeedX / abs(mScrollSpeedX) * PSP_SCREEN_WIDTH);
	}

	if(mScrollSpeedY)
	{	//Move up/down by 272px
		MoveY(mScrollSpeedY / abs(mScrollSpeedY) * -PSP_SCREEN_HEIGHT);
		Draw(); //Draw top/bottom image
		//Reset to center position
		MoveY(mScrollSpeedY / abs(mScrollSpeedY) * PSP_SCREEN_HEIGHT);
	}

	if(mScrollSpeedX && mScrollSpeedY)
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
