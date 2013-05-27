/*
 * SkillsSystem.cpp
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillsSystem.h"

#define PER_LEVEL_EXP 1250
#define BASE_LEVEL_EXP 3000

SkillsSystem::SkillsSystem()
				:ExperienceSystem()
{
	SetTimeWarpLevel(0);
	SetDematerializeLevel(0);
	SetOverdriveLevel(0);
	SetForceFieldLevel(0);
}

SkillsSystem::SkillsSystem(
				unsigned timeWarpLevel,
				unsigned dematerializeLevel,
				unsigned overdriveLevel,
				unsigned forceFieldLevel,
				unsigned expPointsAvailable)
					:ExperienceSystem(expPointsAvailable)
{
	SetTimeWarpLevel(timeWarpLevel);
	SetDematerializeLevel(dematerializeLevel);
	SetOverdriveLevel(overdriveLevel);
	SetForceFieldLevel(forceFieldLevel);
}

unsigned SkillsSystem::GetTimeWarpLevel()
{
	return mTimeWarpLevel;
}

unsigned SkillsSystem::GetDematerializeLevel()
{
	return mDematerializeLevel;
}

unsigned SkillsSystem::GetOverdriveLevel()
{
	return mOverdriveLevel;
}

unsigned SkillsSystem::GetForceFieldLevel()
{
	return mForceFieldLevel;
}

void SkillsSystem::LevelUpTimeWarp()
{
	if(	GetTimeWarpLevel() < 5 &&
		DeductExperiencePoints(
				(GetTimeWarpLevel() + 1) * PER_LEVEL_EXP +
				(GetTimeWarpLevel() + 1) * BASE_LEVEL_EXP))
					mTimeWarpLevel++;

}

void SkillsSystem::LevelUpDematerialize()
{
	if(	GetDematerializeLevel() < 5 &&
		DeductExperiencePoints(
				(GetDematerializeLevel() + 1) * PER_LEVEL_EXP +
				(GetDematerializeLevel() + 1) * BASE_LEVEL_EXP))
					mDematerializeLevel++;

}

void SkillsSystem::LevelUpOverdrive()
{
	if(	GetOverdriveLevel() < 5 &&
		DeductExperiencePoints(
				(GetOverdriveLevel() + 1) * PER_LEVEL_EXP +
				(GetOverdriveLevel() + 1) * BASE_LEVEL_EXP))
					mOverdriveLevel++;

}

void SkillsSystem::LevelUpForceField()
{
	if(	GetForceFieldLevel() < 5 &&
		DeductExperiencePoints(
				(GetForceFieldLevel() + 1) * PER_LEVEL_EXP +
				(GetForceFieldLevel() + 1) * BASE_LEVEL_EXP))
					mForceFieldLevel++;

}

void SkillsSystem::SetTimeWarpLevel(unsigned newTimeWarpLevel)
{
	if(newTimeWarpLevel <= 5)
		mTimeWarpLevel = newTimeWarpLevel;
}

void SkillsSystem::SetDematerializeLevel(unsigned newDematerializeLevel)
{
	if(newDematerializeLevel <= 5)
		mDematerializeLevel = newDematerializeLevel;
}

void SkillsSystem::SetOverdriveLevel(unsigned newOverdriveLevel)
{
	if(newOverdriveLevel <= 5)
		mOverdriveLevel = newOverdriveLevel;
}

void SkillsSystem::SetForceFieldLevel(unsigned newForceFieldLevel)
{
	if(newForceFieldLevel <= 5)
		mForceFieldLevel = newForceFieldLevel;
}
