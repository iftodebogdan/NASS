/*
 * Background.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Background.h"

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
	mPrimaryBackground->Render();
	if(IsParallaxBackgroundShown())
		mParallaxBackground->Render();
}
