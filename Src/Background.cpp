/*
 * Background.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Resources.hpp"

#include "../Includes/Background.hpp"

Background::Background(string pathToPrimaryBgImgFile)
{
	mPrimaryBackground = new ScrollingDrawable(pathToPrimaryBgImgFile, 0, 0);
	mParallaxBackground = NULL;

	oslAssert(
			mPrimaryBackground->GetWidth() == PSP_SCREEN_WIDTH &&
			mPrimaryBackground->GetHeight() == PSP_SCREEN_HEIGHT );

	ShowParallaxBackground(false);
	ResetBackground();
}

Background::Background(string pathToPrimaryBgImgFile, string pathToParallaxBgImgFile)
{
	mPrimaryBackground = new ScrollingDrawable(pathToPrimaryBgImgFile, 0, 0);
	mParallaxBackground = new ScrollingDrawable(pathToParallaxBgImgFile, 0, 0);

	oslAssert(
			mPrimaryBackground->GetWidth() == PSP_SCREEN_WIDTH &&
			mPrimaryBackground->GetHeight() == PSP_SCREEN_HEIGHT &&
			mParallaxBackground->GetWidth() == PSP_SCREEN_WIDTH &&
			mParallaxBackground->GetHeight() == PSP_SCREEN_HEIGHT );

	ShowParallaxBackground(true);
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
	mPrimaryBackground = new ScrollingDrawable(
								pathToPrimaryBgImgFile,
								primaryBgScrollSpeedX,
								primaryBgScrollSpeedY);
	mParallaxBackground = new ScrollingDrawable(
								pathToParallaxBgImgFile,
								parallaxBgScrollSpeedX,
								parallaxBgScrollSpeedY);

	oslAssert(
			mPrimaryBackground->GetWidth() == PSP_SCREEN_WIDTH &&
			mPrimaryBackground->GetHeight() == PSP_SCREEN_HEIGHT &&
			mParallaxBackground->GetWidth() == PSP_SCREEN_WIDTH &&
			mParallaxBackground->GetHeight() == PSP_SCREEN_HEIGHT );

	ShowParallaxBackground(true);
	ResetBackground();
}

Background::~Background()
{
	if(mPrimaryBackground != NULL)
		delete mPrimaryBackground;
	if(mParallaxBackground != NULL)
		delete mParallaxBackground;
}

void Background::SetBackgroundScrollSpeed(
			int primaryBgScrollSpeedX,
			int primaryBgScrollSpeedY,
			int parallaxBgScrollSpeedX,
			int parallaxBgScrollSpeedY)
{
	mPrimaryBackground->SetScrollSpeed(primaryBgScrollSpeedX, primaryBgScrollSpeedY);
	mParallaxBackground->SetScrollSpeed(parallaxBgScrollSpeedX, parallaxBgScrollSpeedY);
}

int Background::GetPrimaryBackgroundScrollSpeedX()
{
	return mPrimaryBackground->GetScrollSpeedX();
}

int Background::GetPrimaryBackgroundScrollSpeedY()
{
	return mPrimaryBackground->GetScrollSpeedY();
}

int Background::GetParallaxBackgroundScrollSpeedX()
{
	return mParallaxBackground->GetScrollSpeedX();
}

int Background::GetParallaxBackgroundScrollSpeedY()
{
	return mParallaxBackground->GetScrollSpeedY();
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
	mPrimaryBackground->Reset();
	mParallaxBackground->Reset();
}

void Background::Render()
{
	RenderBackground(mPrimaryBackground);
	if(IsParallaxBackgroundShown())
		RenderBackground(mParallaxBackground);
}

void Background::RenderBackground(ScrollingDrawable* background)
{
	if(abs(background->GetPositionX()) >= PSP_SCREEN_WIDTH)
		background->MoveX(background->GetScrollSpeedX() / abs(background->GetScrollSpeedX()) * -PSP_SCREEN_WIDTH);

	if(abs(background->GetPositionY()) >= PSP_SCREEN_HEIGHT)
		background->MoveY(background->GetScrollSpeedY() / abs(background->GetScrollSpeedY()) * -PSP_SCREEN_HEIGHT);

	background->Render();

	if(background->GetScrollSpeedX())
	{	//Move left/right by 480px
		background->MoveX(background->GetScrollSpeedX() / abs(background->GetScrollSpeedX()) * -PSP_SCREEN_WIDTH);
		background->Draw(); //Draw left/right image
		//Reset to center position
		background->MoveX(background->GetScrollSpeedX() / abs(background->GetScrollSpeedX()) * PSP_SCREEN_WIDTH);
	}

	if(background->GetScrollSpeedY())
	{	//Move up/down by 272px
		background->MoveY(background->GetScrollSpeedY() / abs(background->GetScrollSpeedY()) * -PSP_SCREEN_HEIGHT);
		background->Draw(); //Draw top/bottom image
		//Reset to center position
		background->MoveY(background->GetScrollSpeedY() / abs(background->GetScrollSpeedY()) * PSP_SCREEN_HEIGHT);
	}

	if(background->GetScrollSpeedX() && background->GetScrollSpeedY())
	{	//Move left/right by 480px
		background->MoveX(background->GetScrollSpeedX() / abs(background->GetScrollSpeedX()) * -PSP_SCREEN_WIDTH);
		//Move up/down by 272px
		background->MoveY(background->GetScrollSpeedY() / abs(background->GetScrollSpeedY()) * -PSP_SCREEN_HEIGHT);
		background->Draw(); //Draw diagonal image
		//Reset to center position
		background->MoveX(background->GetScrollSpeedX() / abs(background->GetScrollSpeedX()) * PSP_SCREEN_WIDTH);
		background->MoveY(background->GetScrollSpeedY() / abs(background->GetScrollSpeedY()) * PSP_SCREEN_HEIGHT);
	}
}
