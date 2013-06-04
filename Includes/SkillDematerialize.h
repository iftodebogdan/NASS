/*
 * SkillDematerialize.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#ifndef SKILLDEMATERIALIZE_H_
#define SKILLDEMATERIALIZE_H_

#include "AnimatedSprite.h"
#include <math.h>

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
