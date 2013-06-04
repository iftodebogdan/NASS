/*
 * SkillsSystem.cpp
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillsSystem.h"
#include "../Includes/Resources.h"

#define PER_LEVEL_EXP 2250
#define BASE_LEVEL_EXP 3750

#define ENERGY_BAR_X0 125
#define ENERGY_BAR_Y0 240
#define ENERGY_BAR_X1 460
#define ENERGY_BAR_Y1 265

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
	mSkillOverdrive = new SkillOverdrive();
	mSkillForceField = new SkillForceField();
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
	mSkillOverdrive = new SkillOverdrive();
	mSkillForceField = new SkillForceField();
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

bool SkillsSystem::LevelUpWarp()
{
	if(	GetWarpLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetWarpLevel()) ))
	{
		mWarpLevel++;
		return true;
	}

	return false;
}

bool SkillsSystem::LevelUpDematerialize()
{
	if(	GetDematerializeLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetDematerializeLevel()) ))
	{
		mDematerializeLevel++;
		return true;
	}

	return false;
}

bool SkillsSystem::LevelUpOverdrive()
{
	if(	GetOverdriveLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetOverdriveLevel()) ))
	{
		mOverdriveLevel++;
		return true;
	}

	return false;
}

bool SkillsSystem::LevelUpForceField()
{
	if(	GetForceFieldLevel() < 5 &&
		DeductExperiencePoints( SkillLevelUpCost(GetForceFieldLevel()) ))
	{
		mForceFieldLevel++;
		return true;
	}

	return false;
}

bool SkillsSystem::RefundWarp()
{
	if(	GetWarpLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetWarpLevel()));
		mWarpLevel--;
		return true;
	}

	return false;
}

bool SkillsSystem::RefundDematerialize()
{
	if(	GetDematerializeLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetDematerializeLevel()));
		mDematerializeLevel--;
		return true;
	}

	return false;
}

bool SkillsSystem::RefundOverdrive()
{
	if(	GetOverdriveLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetOverdriveLevel()));
		mOverdriveLevel--;
		return true;
	}

	return false;
}

bool SkillsSystem::RefundForceField()
{
	if(	GetForceFieldLevel() > 0)
	{
		AddExperiencePoints(SkillRefundValue(GetForceFieldLevel()));
		mForceFieldLevel--;
		return true;
	}

	return false;
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

bool SkillsSystem::NoSkillActive()
{
	if(mSkillWarp->IsActive() ||
	   mSkillDematerialize->IsActive() ||
	   mSkillOverdrive->IsActive() ||
	   mSkillForceField->IsActive())
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

	oslSetTextColor(COLOR_WHITE);
	oslSetBkColor(RGBA(0,0,0,0));
	oslDrawString(ENERGY_BAR_X0, ENERGY_BAR_Y0 - 8, "0");

	for(int i = 1; i <= 9; i++)
		if(i != 5)
			oslDrawLine(ENERGY_BAR_X0 +
						(ENERGY_BAR_X1 - ENERGY_BAR_X0) * i / 10,
						ENERGY_BAR_Y0,
						ENERGY_BAR_X0 +
						(ENERGY_BAR_X1 - ENERGY_BAR_X0) * i / 10,
						ENERGY_BAR_Y0 - 5,
						COLOR_WHITE);
		else
			oslDrawLine(ENERGY_BAR_X0 +
						(ENERGY_BAR_X1 - ENERGY_BAR_X0) * i / 10,
						ENERGY_BAR_Y0,
						ENERGY_BAR_X0 +
						(ENERGY_BAR_X1 - ENERGY_BAR_X0) * i / 10,
						ENERGY_BAR_Y0 - 8,
						COLOR_WHITE);

	oslDrawString(ENERGY_BAR_X1 - oslGetStringWidth("100") + 2, ENERGY_BAR_Y0 - 8, "100");
}

void SkillsSystem::Render()
{
	if(NoSkillActive())
		RegenerateEnergy(ENERGY_REGEN_RATE);

	mSkillWarp->Render();
	mSkillDematerialize->Render();
	mSkillOverdrive->Render();
	mSkillForceField->Render();

	RenderScore();
	RenderEnergy();
}

void SkillsSystem::ResetSkills()
{
	mSkillWarp->SetState(SkillWarp::READY);
	mSkillDematerialize->SetState(SkillDematerialize::READY);
	mSkillOverdrive->SetState(SkillOverdrive::READY);
	mSkillForceField->SetState(SkillForceField::READY);
}
