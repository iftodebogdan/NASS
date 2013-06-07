/*
 * SkillDematerialize.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#ifndef SKILLDEMATERIALIZE_H_
#define SKILLDEMATERIALIZE_H_

#include "AnimatedSprite.h"

#define DEMATERIALIZE_ENERGY_COST_LV1 MAX_ENERGY * 100.0f / 100.0f
#define DEMATERIALIZE_ENERGY_COST_LV2 MAX_ENERGY * 90.0f / 100.0f
#define DEMATERIALIZE_ENERGY_COST_LV3 MAX_ENERGY * 80.0f / 100.0f
#define DEMATERIALIZE_ENERGY_COST_LV4 MAX_ENERGY * 70.0f / 100.0f
#define DEMATERIALIZE_ENERGY_COST_LV5 MAX_ENERGY * 50.0f / 100.0f

class SkillDematerialize
{
public:
	enum SkillDematerializeState
	{
		ACTIVE,
		READY
	};

	SkillDematerialize();

	void SetState(SkillDematerializeState newSkillDematerializeState);
	SkillDematerializeState GetState();
	bool IsActive();

	void Render();

private:
	void Evaluate();

	AnimatedSprite* mDematerializeEffect;

	SkillDematerializeState mSkillDematerializeState;
	float mEnergyCost;
	unsigned mEnergyCostPerSecond;
};

#endif /* SKILLDEMATERIALIZE_H_ */
