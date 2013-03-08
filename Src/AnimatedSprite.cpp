/*
 * AnimatedSprite.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(
		string pathToImgFile,
		int frameWidthSize,
		int frameHeightSize,
		int framesPerSecond)
			:Drawable(pathToImgFile)
{
	oslSetImageFrameSize(mDrawableImg, frameWidthSize, frameHeightSize);

	mFrameCount = ( GetWidth() / GetFrameWidth() ) *
					  ( GetHeight() / GetFrameHeight() );

	SetAnimationSpeed(framesPerSecond);
	ResetAnimation();
}

AnimatedSprite::AnimatedSprite(const AnimatedSprite *animatedSprite)
	: Drawable(animatedSprite)
{
	mCurrentFrame = animatedSprite->mCurrentFrame;
	mFrameCount = animatedSprite->mFrameCount;
	mFramesPerSecond = animatedSprite->mFramesPerSecond;
	mTicksLeft = animatedSprite->mTicksLeft;
	mInvertedAnimation = animatedSprite->mInvertedAnimation;
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
	InvertAnimation(false);
}

void AnimatedSprite::InvertAnimation(bool isInverted)
{
	mInvertedAnimation = isInverted;
}

bool AnimatedSprite::IsAnimationInverted()
{
	return mInvertedAnimation;
}

void AnimatedSprite::SetAnimationSpeed(int framesPerSecond)
{
	mFramesPerSecond = framesPerSecond;
}

int AnimatedSprite::GetAnimationSpeed()
{
	return mFramesPerSecond;
}

int AnimatedSprite::GetFrameCount()
{
	return mFrameCount;
}

void AnimatedSprite::Render()
{
	if(mTicksLeft <= 0)
	{
		mTicksLeft = 60 / GetAnimationSpeed();
		if(!IsAnimationInverted())
			mCurrentFrame < GetFrameCount() - 1 ? mCurrentFrame++ : mCurrentFrame = 0;
		else
			mCurrentFrame > 0 ? mCurrentFrame-- : mCurrentFrame = GetFrameCount() - 1;
	}
	else
		mTicksLeft--;

	oslSetImageFrame(mDrawableImg, mCurrentFrame);
	Draw();
}
