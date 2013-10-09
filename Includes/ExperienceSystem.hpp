/*
 * ExperienceSystem.hpp
 *
 *  Created on: May 27, 2013
 *      Author: Bogdan
 */

#ifndef EXPERIENCESYSTEM_H_
#define EXPERIENCESYSTEM_H_

//#include <iomanip>
//#include <locale>
//#include <sstream>
#include <string>
using namespace std;

class ExperienceSystem
{
public:
	ExperienceSystem();
	ExperienceSystem(unsigned long expPointsAvailable);

	void UpdatePlayerScore(unsigned addPlayerScorePoints);
	void UpdateExperiencePoints();
	void AddExperiencePoints(unsigned long expPoints);
	bool DeductExperiencePoints(unsigned long expPoints);
	unsigned long GetPlayerScore();
	void SetPlayerScore(unsigned newPlayerScore);
	void ResetPlayerScore();
	unsigned long GetHiScore();
	void SetHiScore(unsigned long newHiScore);
	unsigned long GetExperiencePoints();
	void SetExperiencePoints(unsigned long newExperiencePoints);
	void RenderScore();

private:
	unsigned long mPlayerScore;
	unsigned long mPlayerHiScore;
	unsigned long mExperiencePoints;
	int mUpdateScoreFlag;
};

#endif /* EXPERIENCESYSTEM_H_ */
