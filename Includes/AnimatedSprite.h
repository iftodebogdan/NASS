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
	AnimatedSprite(
			string pathToImgFile,
			int frameWidthSize,
			int frameHeigthSize,
			int framesPerSecond);

	int GetFrameWidth();
	int GetFrameHeight();

	void ResetAnimation();
	void SetAnimationSpeed(int framesPerSecond);
	int GetAnimationSpeed();

	int GetFrameCount();

	void Render();

private:
	int mTicksLeft;
	int mFramesPerSecond;
	int mFrameCount;
	int mCurrentFrame;
};

#endif /* ANIMATEDSPRITE_H_ */
