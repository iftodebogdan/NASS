/*
 * SkillsSystem.h
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#ifndef SKILLSSYSTEM_H_
#define SKILLSSYSTEM_H_

#include "ExperienceSystem.h"
#include "SkillWarp.h"
#include "SkillDematerialize.h"
#include "SkillOverdrive.h"

class SkillsSystem : public ExperienceSystem
{
	friend class SkillWarp;
	friend class SkillDematerialize;
	friend class SkillOverdrive;
	friend class CollisionDetection;
	friend class Player;

public:
	SkillsSystem();
	SkillsSystem(unsigned warpLevel,
				 unsigned dematerializeLevel,
				 unsigned overdriveLevel,
				 unsigned forceFieldLevel,
				 unsigned long expPointsAvailable);

	unsigned GetWarpLevel();
	unsigned GetDematerializeLevel();
	unsigned GetOverdriveLevel();
	unsigned GetForceFieldLevel();
	unsigned GetSkillLevelByIndex(unsigned skillIndex);

	void SetWarpLevel(unsigned newWarpLevel);
	void SetDematerializeLevel(unsigned newDematerializeLevel);
	void SetOverdriveLevel(unsigned newOverdriveLevel);
	void SetForceFieldLevel(unsigned newForceFieldLevel);

	unsigned long SkillLevelUpCost(unsigned skillLevel);
	unsigned long SkillRefundValue(unsigned skillLevel);

	void LevelUpWarp();
	void LevelUpDematerialize();
	void LevelUpOverdrive();
	void LevelUpForceField();

	void RefundWarp();
	void RefundDematerialize();
	void RefundOverdrive();
	void RefundForceField();

	void ResetEnergy();
	unsigned GetEnergy();
	void SetEnergy(unsigned newEnergy);
	void RenderEnergy();
	void Render();

private:
	bool NoSkillActivated();
	void RegenerateEnergy(unsigned regenValue);
	bool DepleteEnergy(unsigned requiredEnergy);
	int EnergyBarX1();

	unsigned mWarpLevel;
	unsigned mDematerializeLevel;
	unsigned mOverdriveLevel;
	unsigned mForceFieldLevel;
	unsigned mEnergy;

	SkillWarp* mSkillWarp;
	SkillDematerialize* mSkillDematerialize;
	SkillOverdrive* mSkillOverdrive;
};

#endif /* SKILLSSYSTEM_H_ */
