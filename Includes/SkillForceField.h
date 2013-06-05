/*
 * SkillForceField.h
 *
 *  Created on: Jun 3, 2013
 *      Author: Bogdan
 */

#ifndef SKILLFORCEFIELD_H_
#define SKILLFORCEFIELD_H_

#include "AnimatedSprite.h"

#define FORCE_FIELD_DURATION_LV1 1
#define FORCE_FIELD_DURATION_LV2 2
#define FORCE_FIELD_DURATION_LV3 3
#define FORCE_FIELD_DURATION_LV4 4
#define FORCE_FIELD_DURATION_LV5 5

#define FORCE_FIELD_IMPACTS_LV1 1
#define FORCE_FIELD_IMPACTS_LV2 2
#define FORCE_FIELD_IMPACTS_LV3 3
#define FORCE_FIELD_IMPACTS_LV4 4
#define FORCE_FIELD_IMPACTS_LV5 5

#define FORCE_FIELD_ENERGY_COST_LV1 MAX_ENERGY * 50 / 100
#define FORCE_FIELD_ENERGY_COST_LV2 MAX_ENERGY * 55 / 100
#define FORCE_FIELD_ENERGY_COST_LV3 MAX_ENERGY * 60 / 100
#define FORCE_FIELD_ENERGY_COST_LV4 MAX_ENERGY * 65 / 100
#define FORCE_FIELD_ENERGY_COST_LV5 MAX_ENERGY * 70 / 100

#define FORCE_FIELD_ENERGY_REGEN_LV1 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV2 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV3 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV4 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV5 MAX_ENERGY * 10 / 100

class SkillForceField
{
	friend class CollisionDetection;
	friend class SkillsSystem;

public:
	enum SkillForceFieldState
	{
		ACTIVE,
		READY
	};

	SkillForceField();
	void SetState(SkillForceFieldState newSkillForceFieldState);
	SkillForceFieldState GetState();
	bool IsActive();
	void Evaluate();
	void Render();

private:
	void ForceFieldImpact();
	void RenderDurationBar();
	unsigned GetSkillDuration();
	int GetForceFieldImpacts();
	unsigned GetSkillEnergyCost();

	AnimatedSprite* mForceFieldEffect;
	SkillForceFieldState mSkillForceFieldState;
	int mSkillDuration;
	int mForceFieldImpacts;
	unsigned mEnergyCost;
	unsigned mEnergyRegen;
};

#endif /* SKILLFORCEFIELD_H_ */
