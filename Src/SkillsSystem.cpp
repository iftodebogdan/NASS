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
	SetWarpLevel(0);
	SetDematerializeLevel(0);
	SetOverdriveLevel(0);
	SetForceFieldLevel(0);

	ResetEnergy();

	mSkillWarp = new SkillWarp();
	mSkillDematerialize = new SkillDematerialize();
}

SkillsSystem::SkillsSystem(
				unsigned warpLevel,
				unsigned dematerializeLevel,
				unsigned overdriveLevel,
				unsigned forceFieldLevel,
				unsigned long expPointsAvailable)
					:ExperienceSystem(expPointsAvailable)
{
	SetWarpLevel(warpLevel);
	SetDematerializeLevel(dematerializeLevel);
	SetOverdriveLevel(overdriveLevel);
	SetForceFieldLevel(forceFieldLevel);

	ResetEnergy();

	mSkillWarp = new SkillWarp();
	mSkillDematerialize = new SkillDematerialize();
}

unsigned SkillsSystem::GetWarpLevel()
{
	return mWarpLevel;
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

unsigned SkillsSystem::GetSkillLevelByIndex(unsigned skillIndex)
{
	switch(skillIndex)
	{
	case 1:
		return GetWarpLevel();
	case 2:
		return GetDematerializeLevel();
	case 3:
		return GetOverdriveLevel();
	case 4:
		return GetForceFieldLevel();
	}

	return NULL;
}

unsigned long SkillsSystem::SkillLevelUpCost(unsigned skillLevel)
{
	if(skillLevel >= 5)
		return 0;

	return skillLevel * (skillLevel + 1) * PER_LEVEL_EXP + (skillLevel + 1) * BASE_LEVEL_EXP;
}

unsigned long SkillsSystem::SkillRefundValue(unsigned skillLevel)
{
	return skillLevel * BASE_LEVEL_EXP;
}

void SkillsSystem::LevelUpWarp()
{
	if(	GetWarpLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetWarpLevel()) ))
					mWarpLevel++;

}

void SkillsSystem::LevelUpDematerialize()
{
	if(	GetDematerializeLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetDematerializeLevel()) ))
					mDematerializeLevel++;

}

void SkillsSystem::LevelUpOverdrive()
{
	if(	GetOverdriveLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetOverdriveLevel()) ))
					mOverdriveLevel++;

}

void SkillsSystem::LevelUpForceField()
{
	if(	GetForceFieldLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetForceFieldLevel()) ))
					mForceFieldLevel++;

}

void SkillsSystem::RefundWarp()
{
	if(	GetWarpLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetWarpLevel()));
		mWarpLevel--;
	}
}

void SkillsSystem::RefundDematerialize()
{
	if(	GetDematerializeLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetDematerializeLevel()));
		mDematerializeLevel--;
	}
}

void SkillsSystem::RefundOverdrive()
{
	if(	GetOverdriveLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetOverdriveLevel()));
		mOverdriveLevel--;
	}
}

void SkillsSystem::RefundForceField()
{
	if(	GetForceFieldLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetForceFieldLevel()));
		mForceFieldLevel--;
	}
}

void SkillsSystem::SetWarpLevel(unsigned newWarpLevel)
{
	if(newWarpLevel <= 5)
		mWarpLevel = newWarpLevel;
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

bool SkillsSystem::NoSkillActivated()
{
	if(mSkillWarp->IsActivated() ||
	   mSkillDematerialize->IsActivated())
		return false;

	return true;
}

void SkillsSystem::RegenerateEnergy(unsigned regenValue)
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

void SkillsSystem::RenderEnergy()
{
	Resources::mParafontFont->DrawText(Resources::STR_ENERGY_OSD, 5, 240);
	oslDrawFillRect(
			ENERGY_BAR_X0,
			ENERGY_BAR_Y0,
			EnergyBarX1(),
			ENERGY_BAR_Y1,
			RGBA(255, 255, 255, 128));
	oslDrawRect(ENERGY_BAR_X0, ENERGY_BAR_Y0, ENERGY_BAR_X1, ENERGY_BAR_Y1, COLOR_WHITE);
}

void SkillsSystem::Render()
{
	RenderScore();
	RenderEnergy();

	if(NoSkillActivated())
		RegenerateEnergy(ENERGY_REGEN_RATE);

	mSkillWarp->Render();
	mSkillDematerialize->Render();
}
