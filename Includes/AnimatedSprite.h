/*
 * AnimatedSprite.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef ANIMATEDSPRITE_H_
#define ANIMATEDSPRITE_H_

#include "Drawable.h"

class AnimatedSprite : public Drawable
{
public:
	AnimatedSprite(					//creates an animated sprite
			string pathToImgFile,	//an image file in png format
			int frameWidthSize,		//the width of a frame
			int frameHeigthSize,	//the height of a frame
			int framesPerSecond);	//animation speed in frames/second
	AnimatedSprite(const AnimatedSprite *animatedSprite);

	int GetFrameWidth(); //returns the width of a frame in pixels
	int GetFrameHeight(); //returns the height of a frame in pixels

	void ResetAnimation(); //resets the animation sequence
	void InvertAnimation(bool isInverted);
	bool IsAnimationInverted();
	void SetAnimationSpeed(int framesPerSecond); //sets an animation speed in frames/second
	int GetAnimationSpeed(); //returns the animation speed in frames/second

	int GetCurrentFrame();
	int GetFrameCount(); //returns the number of frames for the animated sprite

	void Render(); //renders the animation

private:
	int mTicksLeft;
	int mFramesPerSecond;
	int mFrameCount;
	int mCurrentFrame;
	bool mInvertedAnimation;
};

#endif /* ANIMATEDSPRITE_H_ */
