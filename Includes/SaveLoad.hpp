/*
 * SaveLoad.hpp
 *
 *  Created on: May 31, 2013
 *      Author: Bogdan
 */

#ifndef SAVELOAD_H_
#define SAVELOAD_H_

class SaveLoad
{
	struct SaveGame
	{
		unsigned warpLevel;
		unsigned dematerializeLevel;
		unsigned overdriveLevel;
		unsigned forceFieldLevel;
		unsigned long expPointsAvailable;
		unsigned long playerHiScore;
	};

public:
	void AutoSaveGame();
	void LoadSaveGame();
	void ResetProgress();
};

#endif /* SAVELOAD_H_ */
