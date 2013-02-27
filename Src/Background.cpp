/*
 * Background.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Background.h"

Background::Background(string pathToPrimaryBgImgFile)
{
	mPrimaryBackground = new Drawable(pathToPrimaryBgImgFile);
	mParallaxBackground = NULL;

	oslAssert(
			mPrimaryBackground->GetWidth() == 480 &&
			mPrimaryBackground->GetHeight() == 272 );

	ShowParallaxBackground(false);
	SetBackgroundScrollSpeed(0,0,0,0);
	ResetBackground();
}

Background::Background(string pathToPrimaryBgImgFile, string pathToParallaxBgImgFile)
{
	mPrimaryBackground = new Drawable(pathToPrimaryBgImgFile);
	mParallaxBackground = new Drawable(pathToParallaxBgImgFile);

	oslAssert(
			mPrimaryBackground->GetWidth() == 480 &&
			mPrimaryBackground->GetHeight() == 272 &&
			mParallaxBackground->GetWidth() == 480 &&
			mParallaxBackground->GetHeight() == 272 );

	ShowParallaxBackground(true);
	SetBackgroundScrollSpeed(0,0,0,0);
	ResetBackground();
}

Background::Background(
				string pathToPrimaryBgImgFile,
				string pathToParallaxBgImgFile,
				int primaryBgScrollSpeedX,
				int primaryBgScrollSpeedY,
				int parallaxBgScrollSpeedX,
				int parallaxBgScrollSpeedY)
{
	mPrimaryBackground = new Drawable(pathToPrimaryBgImgFile);
	mParallaxBackground = new Drawable(pathToParallaxBgImgFile);

	oslAssert(
			mPrimaryBackground->GetWidth() == 480 &&
			mPrimaryBackground->GetHeight() == 272 &&
			mParallaxBackground->GetWidth() == 480 &&
			mParallaxBackground->GetHeight() == 272 );

	ShowParallaxBackground(true);
	SetBackgroundScrollSpeed(
				primaryBgScrollSpeedX,
				primaryBgScrollSpeedY,
				parallaxBgScrollSpeedX,
				parallaxBgScrollSpeedY);
	ResetBackground();
}

void Background::SetBackgroundScrollSpeed(
			int primaryBgScrollSpeedX,
			int primaryBgScrollSpeedY,
			int parallaxBgScrollSpeedX,
			int parallaxBgScrollSpeedY)
{
	mPrimaryBgScrollSpeedX = primaryBgScrollSpeedX;
	mPrimaryBgScrollSpeedY = primaryBgScrollSpeedY;
	mParallaxBgScrollSpeedX = parallaxBgScrollSpeedX;
	mParallaxBgScrollSpeedY = parallaxBgScrollSpeedY;
}

void Background::ShowParallaxBackground(bool isShown)
{
	if(mParallaxBackground != NULL)
		mParallaxBgIsShown = isShown;
	else
		mParallaxBgIsShown = false;
}

bool Background::IsParallaxBackgroundShown()
{
	return mParallaxBgIsShown;
}

void Background::ResetBackground()
{
	mPrimaryBackground->SetPositionXY(0,0);
	if(mParallaxBackground != NULL)
		mParallaxBackground->SetPositionXY(0,0);
	mPrimaryBgPixelsToScrollX = 0;
	mPrimaryBgPixelsToScrollY = 0;
	mParallaxBgPixelsToScrollX = 0;
	mParallaxBgPixelsToScrollY = 0;
}

void Background::Render()
{
	RenderBackground(
			mPrimaryBackground,
			mPrimaryBgScrollSpeedX,
			mPrimaryBgScrollSpeedY,
			mPrimaryBgPixelsToScrollX,
			mPrimaryBgPixelsToScrollY);
	if(mParallaxBgIsShown)
		RenderBackground(
				mParallaxBackground,
				mParallaxBgScrollSpeedX,
				mParallaxBgScrollSpeedY,
				mParallaxBgPixelsToScrollX,
				mParallaxBgPixelsToScrollY);
}

void Background::RenderBackground(
			Drawable* backgroundImg,
			int bgScrollSpeedX,
			int bgScrollSpeedY,
			float &bgPixelsToScrollX,
			float &bgPixelsToScrollY)
{
	bgPixelsToScrollX += bgScrollSpeedX / 60.0f;
	if(abs(bgPixelsToScrollX) >= 1)
	{
		backgroundImg->MoveX(bgPixelsToScrollX);
		bgPixelsToScrollX -= (int)bgPixelsToScrollX;
	}
	if(abs(backgroundImg->GetPositionX()) >= 480)
		backgroundImg->MoveX(bgScrollSpeedX / abs(bgScrollSpeedX) * -480);

	bgPixelsToScrollY += bgScrollSpeedY / 60.0f;
		if(abs(bgPixelsToScrollY) >= 1)
		{
			backgroundImg->MoveY(bgPixelsToScrollY);
			bgPixelsToScrollY -= (int)bgPixelsToScrollY;
		}
		if(abs(backgroundImg->GetPositionY()) >= 272)
			backgroundImg->MoveY(bgScrollSpeedY / abs(bgScrollSpeedY) * -272);

	backgroundImg->Draw(); //Draw center image

	if(bgScrollSpeedX)
	{	//Move left/right by 480px
		backgroundImg->MoveX(bgScrollSpeedX / abs(bgScrollSpeedX) * -480);
		backgroundImg->Draw(); //Draw left/right image
		//Reset to center position
		backgroundImg->MoveX(bgScrollSpeedX / abs(bgScrollSpeedX) * 480);
	}

	if(bgScrollSpeedY)
	{	//Move up/down by 272px
		backgroundImg->MoveY(bgScrollSpeedY / abs(bgScrollSpeedY) * -272);
		backgroundImg->Draw(); //Draw top/bottom image
		//Reset to center position
		backgroundImg->MoveY(bgScrollSpeedY / abs(bgScrollSpeedY) * 272);
	}

	if(bgScrollSpeedX && bgScrollSpeedY)
	{	//Move left/right by 480px
		backgroundImg->MoveX(bgScrollSpeedX / abs(bgScrollSpeedX) * -480);
		//Move up/down by 272px
		backgroundImg->MoveY(bgScrollSpeedY / abs(bgScrollSpeedY) * -272);
		backgroundImg->Draw(); //Draw diagonal image
		//Reset to center position
		backgroundImg->MoveX(bgScrollSpeedX / abs(bgScrollSpeedX) * 480);
		backgroundImg->MoveY(bgScrollSpeedY / abs(bgScrollSpeedY) * 272);
	}
	backgroundImg->Draw();
}
