/*
 * SaveLoad.h
 *
 *  Created on: May 31, 2013
 *      Author: Bogdan
 */

#ifndef SAVELOAD_H_
#define SAVELOAD_H_

#include <fstream>

struct SaveGame
{
	unsigned warpLevel;
	unsigned dematerializeLevel;
	unsigned overdriveLevel;
	unsigned forceFieldLevel;
	unsigned long expPointsAvailable;
};

class SaveLoad
{
public:
	void AutoSaveGame();
	void LoadSaveGame();
};

#endif /* SAVELOAD_H_ */
