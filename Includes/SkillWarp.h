/*
 * SkillWarp.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#ifndef SKILLWARP_H_
#define SKILLWARP_H_

#include "AnimatedSprite.h"

#define WARP_LV1 100
#define WARP_LV2 110
#define WARP_LV3 125
#define WARP_LV4 150
#define WARP_LV5 180

class SkillWarp
{
	enum SkillWarpState
	{
		ACTIVATED,
		WARPING,
		READY
	};

public:
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
