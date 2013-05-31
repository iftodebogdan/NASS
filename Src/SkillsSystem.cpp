/*
 * SkillsSystem.cpp
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillsSystem.h"
#include "../Includes/Resources.h"

SkillsSystem::SkillsSystem()
				:ExperienceSystem()
{
	SetTimeWarpLevel(0);
	SetDematerializeLevel(0);
	SetOverdriveLevel(0);
	SetForceFieldLevel(0);

	ResetEnergy();
}

SkillsSystem::SkillsSystem(
				unsigned timeWarpLevel,
				unsigned dematerializeLevel,
				unsigned overdriveLevel,
				unsigned forceFieldLevel,
				unsigned long expPointsAvailable)
					:ExperienceSystem(expPointsAvailable)
{
	SetTimeWarpLevel(timeWarpLevel);
	SetDematerializeLevel(dematerializeLevel);
	SetOverdriveLevel(overdriveLevel);
	SetForceFieldLevel(forceFieldLevel);

	ResetEnergy();
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

void SkillsSystem::ResetEnergy()
{
	mEnergy = 0;
}

unsigned SkillsSystem::GetEnergy()
{
	return mEnergy;
}

void SkillsSystem::SetEnergy(unsigned newEnergy)
{
	if(newEnergy <= MAX_ENERGY)
		mEnergy = newEnergy;
}

void SkillsSystem::RegenEnergy(unsigned regenValue)
{
	if(GetEnergy() + regenValue <= MAX_ENERGY)
		mEnergy += regenValue;
	else
		mEnergy = MAX_ENERGY;
}

bool SkillsSystem::DepleteEnergy(unsigned requiredEnergy)
{
	if(requiredEnergy <= GetEnergy())
	{
		mEnergy -= requiredEnergy;
		return true;
	}
	else
		return false;
}

int SkillsSystem::EnergyBarX1()
{
	unsigned currentEnergy = GetEnergy();
	unsigned maxEnergy = MAX_ENERGY;
	unsigned currentBarLength;
	unsigned maxBarLength = ENERGY_BAR_X1 - ENERGY_BAR_X0;

	currentBarLength = (currentEnergy * maxBarLength) / maxEnergy;

	return currentBarLength + ENERGY_BAR_X0;
}

void SkillsSystem::Render()
{
	RenderScore();

	RegenEnergy(1);

	Resources::mParafontFont->DrawText(Resources::STR_ENERGY_OSD, 5, 240);
	oslDrawFillRect(
			ENERGY_BAR_X0,
			ENERGY_BAR_Y0,
			EnergyBarX1(),
			ENERGY_BAR_Y1,
			RGBA(255, 255, 255, 128));
	oslDrawRect(ENERGY_BAR_X0, ENERGY_BAR_Y0, ENERGY_BAR_X1, ENERGY_BAR_Y1, COLOR_WHITE);
}
