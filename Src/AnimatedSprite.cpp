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

	mAnimationTimer = new Timer();
	SetAnimationSpeed(framesPerSecond);
	ResetAnimation();
}

AnimatedSprite::AnimatedSprite(const AnimatedSprite *animatedSprite)
	: Drawable(animatedSprite)
{
	mCurrentFrame = animatedSprite->mCurrentFrame;
	mFrameCount = animatedSprite->mFrameCount;
	mFramesPerSecond = animatedSprite->mFramesPerSecond;
	mInvertedAnimation = animatedSprite->mInvertedAnimation;
	mAnimationTimer = new Timer(*animatedSprite->mAnimationTimer);
}

int AnimatedSprite::GetFrameWidth()
{
	return mDrawableImg->frameSizeX;
}

int AnimatedSprite::GetFrameHeight()
{
	return mDrawableImg->frameSizeY;
}

unsigned AnimatedSprite::GetFramePixel(int coordX, int coordY)
{
	return GetPixel(coordX + GetFrameWidth() * ((GetCurrentFrame() - 1) % (GetWidth() / GetFrameWidth())),
					coordY + GetFrameHeight() * ((GetCurrentFrame() - 1) % (GetHeight() / GetFrameHeight())));
}

void AnimatedSprite::ResetAnimation()
{
	mCurrentFrame = 0;
	mAnimationTimer->ResetStopwatch();
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

int AnimatedSprite::GetCurrentFrame()
{
	return mCurrentFrame + 1;
}

int AnimatedSprite::GetFrameCount()
{
	return mFrameCount;
}

void AnimatedSprite::Render()
{
	if(mAnimationTimer->Stopwatch(1000 / GetAnimationSpeed()))
	{
		if(!IsAnimationInverted())
			mCurrentFrame < GetFrameCount() - 1 ? mCurrentFrame++ : mCurrentFrame = 0;
		else
			mCurrentFrame > 0 ? mCurrentFrame-- : mCurrentFrame = GetFrameCount() - 1;
	}

	oslSetImageFrame(mDrawableImg, mCurrentFrame);
	Draw();
}
