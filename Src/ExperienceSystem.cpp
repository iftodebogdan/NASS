/*
 * ExperienceSystem.cpp
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/ExperienceSystem.h"

ExperienceSystem::ExperienceSystem()
{
	ResetPlayerScore();
	SetExperiencePoints(0);
}

ExperienceSystem::ExperienceSystem(unsigned expPointsAvailable)
{
	ResetPlayerScore();
	SetExperiencePoints(expPoints);
}

bool ExperienceSystem::DeductExperiencePoints(unsigned expPoints)
{
	if(expPoints >= mExperiencePoints)
	{
		mExperiencePoints -= expPoints;
		return true;
	}
	else
		return false;
}

unsigned ExperienceSystem::GetExperiencePoints()
{
	return mExperiencePoints;
}

unsigned ExperienceSystem::GetPlayerScore()
{
	return mPlayerScore;
}

void ExperienceSystem::ResetPlayerScore()
{
	SetPlayerScore(0);
}

void ExperienceSystem::SetExperiencePoints(unsigned newExperiencePoints)
{
	mExperiencePoints = newExperiencePoints;
}

void ExperienceSystem::SetPlayerScore(unsigned newPlayerScore)
{
	mPlayerScore = newPlayerScore;
}

void ExperienceSystem::UpdateExperiencePoints()
{
	mExperiencePoints += mPlayerScore;
	ResetPlayerScore();
}

void ExperienceSystem::UpdatePlayerScore(unsigned addPlayerScorePoints)
{
	mPlayerScore += addPlayerScorePoints;
}
