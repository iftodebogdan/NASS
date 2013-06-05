/*
 * SkillWarp.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#ifndef SKILLWARP_H_
#define SKILLWARP_H_

#include "AnimatedSprite.h"

#define WARP_DISTANCE_LV1 PLAYER_SHIP_FRAME_WIDTH_SIZE + 50
#define WARP_DISTANCE_LV2 PLAYER_SHIP_FRAME_WIDTH_SIZE + 70
#define WARP_DISTANCE_LV3 PLAYER_SHIP_FRAME_WIDTH_SIZE + 100
#define WARP_DISTANCE_LV4 PLAYER_SHIP_FRAME_WIDTH_SIZE + 140
#define WARP_DISTANCE_LV5 PLAYER_SHIP_FRAME_WIDTH_SIZE + 190

#define WARP_ACTIVATION_ENERGY_COST_LV1 MAX_ENERGY * 50 / 100
#define WARP_ACTIVATION_ENERGY_COST_LV2 MAX_ENERGY * 50 / 100
#define WARP_ACTIVATION_ENERGY_COST_LV3 MAX_ENERGY * 50 / 100
#define WARP_ACTIVATION_ENERGY_COST_LV4 MAX_ENERGY * 50 / 100
#define WARP_ACTIVATION_ENERGY_COST_LV5 MAX_ENERGY * 50 / 100

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
