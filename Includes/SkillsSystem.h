/*
 * SkillsSystem.h
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#ifndef SKILLSSYSTEM_H_
#define SKILLSSYSTEM_H_

#include "../Includes/ExperienceSystem.h"

#define PER_LEVEL_EXP 2250
#define BASE_LEVEL_EXP 3750

#define ENERGY_BAR_X0 125
#define ENERGY_BAR_Y0 240
#define ENERGY_BAR_X1 460
#define ENERGY_BAR_Y1 265

#define MAX_ENERGY 1000
#define ENERGY_REGEN_RATE 1

class SkillsSystem : public ExperienceSystem
{
public:
	SkillsSystem();
	SkillsSystem(unsigned timeWarpLevel,
				 unsigned dematerializeLevel,
				 unsigned overdriveLevel,
				 unsigned forceFieldLevel,
				 unsigned long expPointsAvailable);

	unsigned GetTimeWarpLevel();
	unsigned GetDematerializeLevel();
	unsigned GetOverdriveLevel();
	unsigned GetForceFieldLevel();
	unsigned GetSkillLevelByIndex(unsigned skillIndex);

	void SetTimeWarpLevel(unsigned newTimeWarpLevel);
	void SetDematerializeLevel(unsigned newDematerializeLevel);
	void SetOverdriveLevel(unsigned newOverdriveLevel);
	void SetForceFieldLevel(unsigned newForceFieldLevel);

	unsigned long SkillLevelUpCost(unsigned skillLevel);
	unsigned long SkillRefundValue(unsigned skillLevel);

	void LevelUpTimeWarp();
	void LevelUpDematerialize();
	void LevelUpOverdrive();
	void LevelUpForceField();

	void RefundTimeWarp();
	void RefundDematerialize();
	void RefundOverdrive();
	void RefundForceField();

	void ResetEnergy();
	unsigned GetEnergy();
	void SetEnergy(unsigned newEnergy);
	void Render();

private:
	void RegenEnergy(unsigned regenValue);
	bool DepleteEnergy(unsigned requiredEnergy);
	int EnergyBarX1();

	unsigned mTimeWarpLevel;
	unsigned mDematerializeLevel;
	unsigned mOverdriveLevel;
	unsigned mForceFieldLevel;
	unsigned mEnergy;
};

#endif /* SKILLSSYSTEM_H_ */
