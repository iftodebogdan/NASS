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
			string pathToFile,
			int frameWidthSize,
			int frameHeigthSize,
			int ticksPerFrame);

	int GetFrameWidth();
	int GetFrameHeight();

	void ResetAnimation();
	void SetAnimationSpeed(int ticksPerFrame);
	int GetAnimationSpeed();

	int GetFrameCount();

	void Render();

private:
	int mTicksPerFrame;
	int mTicksLeft;
	int mFrameCount;
	int mCurrentFrame;
};

#endif /* ANIMATEDSPRITE_H_ */
