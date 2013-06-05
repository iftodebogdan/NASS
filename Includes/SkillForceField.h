/*
 * SkillForceField.h
 *
 *  Created on: Jun 3, 2013
 *      Author: Bogdan
 */

#ifndef SKILLFORCEFIELD_H_
#define SKILLFORCEFIELD_H_

#include "AnimatedSprite.h"

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
