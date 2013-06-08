/*
 * Debug.cpp
 *
 *  Created on: Jun 8, 2013
 *      Author: Bogdan
 */

#include "../Includes/Debug.h"

#include "../Includes/Resources.h"

void Debug::DebugScreen()
{
	oslSetBkColor(COLOR_BLACK);
	oslSetTextColor(COLOR_WHITE);

	oslPrintf("RAM free: %f KB\n", (float)oslGetRamStatus().maxAvailable / 1024);
	oslPrintf("Enemy count: %d\n", Resources::mEnemyList->GetEnemyCount());
	oslPrintf("mEnemySpeedModifier: %d\n", Resources::mEnemyList->GetEnemySpeedModifier());
	oslPrintf("Available audio channels: ");
	for(int i=0;i<=7;i++)
		if(Audio::IsChannelAvailable(i))
			oslPrintf("%i ", i);
	oslPrintf("\n");
}
