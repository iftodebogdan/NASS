/*
 * ExperienceSystem.cpp
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/ExperienceSystem.h"

#include "../Includes/Resources.h"
#include <sstream>

ExperienceSystem::ExperienceSystem()
{
	ResetPlayerScore();
	SetExperiencePoints(0);
	SetHiScore(0);
}

ExperienceSystem::ExperienceSystem(unsigned long expPointsAvailable)
{
	ResetPlayerScore();
	SetExperiencePoints(expPointsAvailable);
}

void ExperienceSystem::AddExperiencePoints(unsigned long expPoints)
{
	mExperiencePoints += expPoints;
}

bool ExperienceSystem::DeductExperiencePoints(unsigned long expPoints)
{
	if(expPoints <= mExperiencePoints)
	{
		mExperiencePoints -= expPoints;
		return true;
	}
	else
		return false;
}

unsigned long ExperienceSystem::GetExperiencePoints()
{
	return mExperiencePoints;
}

unsigned long ExperienceSystem::GetPlayerScore()
{
	return mPlayerScore;
}

unsigned long ExperienceSystem::GetHiScore()
{
	return mPlayerHiScore;
}

void ExperienceSystem::ResetPlayerScore()
{
	SetPlayerScore(0);
	mUpdateScoreFlag = 60;
}

void ExperienceSystem::SetExperiencePoints(unsigned long newExperiencePoints)
{
	mExperiencePoints = newExperiencePoints;
}

void ExperienceSystem::SetPlayerScore(unsigned newPlayerScore)
{
	mPlayerScore = newPlayerScore;
}

void ExperienceSystem::SetHiScore(unsigned long newHiScore)
{
	mPlayerHiScore = newHiScore;
}

void ExperienceSystem::UpdateExperiencePoints()
{
	mExperiencePoints += mPlayerScore / SCORE_TO_XP_RATIO;

	if(GetHiScore() < mPlayerScore)
		SetHiScore(mPlayerScore);

	ResetPlayerScore();
}

void ExperienceSystem::UpdatePlayerScore(unsigned addPlayerScorePoints)
{
	mPlayerScore += addPlayerScorePoints;
}

void ExperienceSystem::RenderScore()
{
	if(mUpdateScoreFlag)
		mUpdateScoreFlag--;
	else
	{
		mUpdateScoreFlag = 60;
		mPlayerScore += Resources::mEnemyList->GetEnemySpeedModifier();
	}

	Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_SCORE_OSD +
												   string(static_cast<ostringstream*>
												   ( &(ostringstream() << GetPlayerScore()) )->str()), 5);
	Resources::mParafontFont->DrawTextAlignedRight(Resources::STR_HI_SCORE_OSD +
												   string(static_cast<ostringstream*>
												   ( &(ostringstream() << Resources::mSkillsSystem->GetHiScore()) )
												   ->str()), 35);
}
