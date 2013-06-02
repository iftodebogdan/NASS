/*
 * SkillWarp.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#ifndef SKILLWARP_H_
#define SKILLWARP_H_

#include "AnimatedSprite.h"

class SkillWarp
{
public:
	enum SkillWarpState
	{
		ACTIVATED,
		WARPING,
		READY
	};

	SkillWarp();

	void SetState(SkillWarpState newSkillWarpState);
	SkillWarpState GetState();
	bool IsActivated();

	void Render();

private:
	void Evaluate();

	AnimatedSprite* mWarpCrosshair;
	AnimatedSprite* mWarpEffect;

	SkillWarpState mSkillWarpState;
};

#endif /* SKILLWARP_H_ */
