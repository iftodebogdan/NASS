/*
 * ScrollDrawable.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/ScrollingDrawable.h"

ScrollingDrawable::ScrollingDrawable(string pathToImgFile)
					:Drawable(pathToImgFile)
{
	SetScrollSpeed(0, 0);
	Reset();
	SetTiling(true);
}

ScrollingDrawable::ScrollingDrawable(
				string pathToImgFile,
				int scrollSpeedX,
				int scrollSpeedY)
					:Drawable(pathToImgFile)
{
	SetScrollSpeed(scrollSpeedX, scrollSpeedY);
	Reset();
	SetTiling(true);
}

ScrollingDrawable::ScrollingDrawable(
				string pathToImgFile,
				int scrollSpeedX,
				int scrollSpeedY,
				bool isTiling)
					:Drawable(pathToImgFile)
{
	SetScrollSpeed(scrollSpeedX, scrollSpeedY);
	Reset();
	SetTiling(isTiling);
}

void ScrollingDrawable::SetScrollSpeed(int scrollSpeedX, int scrollSpeedY)
{
	SetScrollSpeedX(scrollSpeedX);
	SetScrollSpeedY(scrollSpeedY);
}

void ScrollingDrawable::SetScrollSpeedX(int scrollSpeedX)
{
	mScrollSpeedX = scrollSpeedX;
}

void ScrollingDrawable::SetScrollSpeedY(int scrollSpeedY)
{
	mScrollSpeedY = scrollSpeedY;
}

int ScrollingDrawable::GetScrollSpeedX()
{
	return mScrollSpeedX;
}

int ScrollingDrawable::GetScrollSpeedY()
{
	return mScrollSpeedY;
}

bool ScrollingDrawable::IsTiling()
{
	return mIsTiling;
}

void ScrollingDrawable::SetTiling(bool isTiling)
{
	mIsTiling = isTiling;
}
void ScrollingDrawable::Reset()
{
	SetPositionXY(0,0);
	mPixelsToScrollX = 0;
	mPixelsToScrollY = 0;
}

void ScrollingDrawable::Render()
{
	mPixelsToScrollX += GetScrollSpeedX() / 60.0f;
	if(abs(mPixelsToScrollX) >= 1)
	{
		MoveX(mPixelsToScrollX);
		mPixelsToScrollX -= (int)mPixelsToScrollX;
	}
	if(abs(GetPositionX()) > PSP_SCREEN_WIDTH)
		MoveX(GetScrollSpeedX() / abs(GetScrollSpeedX()) * -PSP_SCREEN_WIDTH);

	mPixelsToScrollY += GetScrollSpeedY() / 60.0f;
		if(abs(mPixelsToScrollY) >= 1)
		{
			MoveY(mPixelsToScrollY);
			mPixelsToScrollY -= (int)mPixelsToScrollY;
		}
		if(abs(GetPositionY()) > PSP_SCREEN_HEIGHT)
			MoveY(GetScrollSpeedY() / abs(GetScrollSpeedY()) * -PSP_SCREEN_HEIGHT);

	Draw(); //Draw center image

	if(GetScrollSpeedX() && IsTiling())
	{	//Move left/right by 480px
		MoveX(GetScrollSpeedX() / abs(GetScrollSpeedX()) * -PSP_SCREEN_WIDTH);
		Draw(); //Draw left/right image
		//Reset to center position
		MoveX(GetScrollSpeedX() / abs(GetScrollSpeedX()) * PSP_SCREEN_WIDTH);
	}

	if(GetScrollSpeedY() && IsTiling())
	{	//Move up/down by 272px
		MoveY(GetScrollSpeedY() / abs(GetScrollSpeedY()) * -PSP_SCREEN_HEIGHT);
		Draw(); //Draw top/bottom image
		//Reset to center position
		MoveY(GetScrollSpeedY() / abs(GetScrollSpeedY()) * PSP_SCREEN_HEIGHT);
	}

	if(GetScrollSpeedX() && GetScrollSpeedY() && IsTiling())
	{	//Move left/right by 480px
		MoveX(GetScrollSpeedX() / abs(GetScrollSpeedX()) * -PSP_SCREEN_WIDTH);
		//Move up/down by 272px
		MoveY(GetScrollSpeedY() / abs(GetScrollSpeedY()) * -PSP_SCREEN_HEIGHT);
		Draw(); //Draw diagonal image
		//Reset to center position
		MoveX(GetScrollSpeedX() / abs(GetScrollSpeedX()) * PSP_SCREEN_WIDTH);
		MoveY(GetScrollSpeedY() / abs(GetScrollSpeedY()) * PSP_SCREEN_HEIGHT);
	}

	Draw();
}
