/*
 * SkillsSystem.h
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#ifndef SKILLSSYSTEM_H_
#define SKILLSSYSTEM_H_

#include "../Includes/ExperienceSystem.h"

class SkillsSystem : public ExperienceSystem
{
public:
	SkillsSystem();
	SkillsSystem(unsigned timeWarpLevel,
				 unsigned dematerializeLevel,
				 unsigned overdriveLevel,
				 unsigned forceFieldLevel,
				 unsigned expPointsAvailable);

	unsigned GetTimeWarpLevel();
	unsigned GetDematerializeLevel();
	unsigned GetOverdriveLevel();
	unsigned GetForceFieldLevel();

	void SetTimeWarpLevel(unsigned newTimeWarpLevel);
	void SetDematerializeLevel(unsigned newDematerializeLevel);
	void SetOverdriveLevel(unsigned newOverdriveLevel);
	void SetForceFieldLevel(unsigned newForceFieldLevel);

	void LevelUpTimeWarp();
	void LevelUpDematerialize();
	void LevelUpOverdrive();
	void LevelUpForceField();

private:
	unsigned mTimeWarpLevel;
	unsigned mDematerializeLevel;
	unsigned mOverdriveLevel;
	unsigned mForceFieldLevel;
};

#endif /* SKILLSSYSTEM_H_ */
