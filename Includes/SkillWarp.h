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
		ACTIVE,
		WARPING,
		READY
	};

	SkillWarp();

	void SetState(SkillWarpState newSkillWarpState);
	SkillWarpState GetState();
	bool IsActive();

	void Render();

private:
	void Evaluate();
	void RenderDurationBar();

	AnimatedSprite* mWarpCrosshair;
	AnimatedSprite* mWarpEffect;

	SkillWarpState mSkillWarpState;
	int mWarpCrosshairXOffset;
	unsigned mEnergyCost;
};

#endif /* SKILLWARP_H_ */
