/*
 * SkillOverdrive.hpp
 *
 *  Created on: Jun 2, 2013
 *      Author: Bogdan
 */

#ifndef SKILLOVERDRIVE_H_
#define SKILLOVERDRIVE_H_

#include "AnimatedSprite.hpp"

#define OVERDRIVE_ENERGY_COST_LV1 MAX_ENERGY * 50 / 100
#define OVERDRIVE_ENERGY_COST_LV2 MAX_ENERGY * 50 / 100
#define OVERDRIVE_ENERGY_COST_LV3 MAX_ENERGY * 50 / 100
#define OVERDRIVE_ENERGY_COST_LV4 MAX_ENERGY * 50 / 100
#define OVERDRIVE_ENERGY_COST_LV5 MAX_ENERGY * 50 / 100

#define OVERDRIVE_BOOST_LV1 1.5f
#define OVERDRIVE_BOOST_LV2 2.0f
#define OVERDRIVE_BOOST_LV3 2.5f
#define OVERDRIVE_BOOST_LV4 3.0f
#define OVERDRIVE_BOOST_LV5 3.5f

class SkillOverdrive
{
public:
	enum SkillOverdriveState
	{
		ACTIVE,
		READY
	};

	SkillOverdrive();

	void SetState(SkillOverdriveState newSkillOverdriveState);
	SkillOverdriveState GetState();
	bool IsActive();
	float SpeedModifier();

	void Render();

private:
	void Evaluate();

	AnimatedSprite* mOverdriveEffect;

	SkillOverdriveState mSkillOverdriveState;
	float mEnergyCost;
	unsigned mEnergyCostPerSecond;
};

#endif /* SKILLOVERDRIVE_H_ */
