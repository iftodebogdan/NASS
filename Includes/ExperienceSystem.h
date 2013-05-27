/*
 * ExperienceSystem.h
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#ifndef EXPERIENCESYSTEM_H_
#define EXPERIENCESYSTEM_H_

class ExperienceSystem
{
public:
	ExperienceSystem();
	ExperienceSystem(unsigned expPointsAvailable);

	void UpdatePlayerScore(unsigned addPlayerScorePoints);
	void UpdateExperiencePoints();
	bool DeductExperiencePoints(unsigned expPoints);
	unsigned GetPlayerScore();
	void SetPlayerScore(unsigned newPlayerScore);
	void ResetPlayerScore();
	unsigned GetExperiencePoints();
	void SetExperiencePoints(unsigned newExperiencePoints);

private:

	unsigned mPlayerScore;
	unsigned mExperiencePoints;
};

#endif /* EXPERIENCESYSTEM_H_ */
