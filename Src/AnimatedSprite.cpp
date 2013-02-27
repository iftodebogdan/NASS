/*
 * AnimatedSprite.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(
		string pathToFile,
		int frameWidthSize,
		int frameHeightSize,
		int ticksPerFrame)
			:Drawable(pathToFile)
{
	oslSetImageFrameSize(mDrawableImg, frameWidthSize, frameHeightSize);

	mFrameCount = ( GetWidth() / GetFrameWidth() ) *
					  ( GetHeight() / GetFrameHeight() );

	SetAnimationSpeed(ticksPerFrame);
	ResetAnimation();
}

int AnimatedSprite::GetFrameWidth()
{
	return mDrawableImg->frameSizeX;
}

int AnimatedSprite::GetFrameHeight()
{
	return mDrawableImg->frameSizeY;
}

void AnimatedSprite::ResetAnimation()
{
	mCurrentFrame = 0;
	mTicksLeft = 0;
}

void AnimatedSprite::SetAnimationSpeed(int ticksPerFrame)
{
	mTicksPerFrame = ticksPerFrame;
}

int AnimatedSprite::GetAnimationSpeed()
{
	return mTicksPerFrame;
}

int AnimatedSprite::GetFrameCount()
{
	return mFrameCount;
}

void AnimatedSprite::Render()
{
	if(mTicksLeft <= 0)
	{
		mTicksLeft = mTicksPerFrame;
		mCurrentFrame < mFrameCount - 1 ? mCurrentFrame++ : mCurrentFrame = 0;
	}
	else
		mTicksLeft--;

	oslSetImageFrame(mDrawableImg, mCurrentFrame);
	Draw();
}
