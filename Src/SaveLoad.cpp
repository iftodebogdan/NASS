/*
 * SaveLoad.cpp
 *
 *  Created on: May 31, 2013
 *      Author: Bogdan
 */

#include "../Includes/SaveLoad.h"
#include "../Includes/Resources.h"

void SaveLoad::AutoSaveGame()
{
	FILE* saveGameFile = NULL;

	SaveGame save;
	memset(&save, 0, sizeof(save));
	save.timeWarpLevel = Resources::mSkillsSystem->GetTimeWarpLevel();
	save.dematerializeLevel = Resources::mSkillsSystem->GetDematerializeLevel();
	save.overdriveLevel = Resources::mSkillsSystem->GetOverdriveLevel();
	save.forceFieldLevel = Resources::mSkillsSystem->GetForceFieldLevel();
	save.expPointsAvailable = Resources::mSkillsSystem->GetExperiencePoints();

	if((saveGameFile = fopen("savegame.bin", "wb")) != NULL)
	{
		fwrite(&save, sizeof(save), 1, saveGameFile);
		fclose(saveGameFile);
	}
}

void SaveLoad::LoadSaveGame()
{
	FILE* saveGameFile = NULL;

	SaveGame save;
	memset(&save, 0, sizeof(save));

	if((saveGameFile = fopen("savegame.bin", "rb")) == NULL)
	{
		AutoSaveGame();
		return;
	}

	fread(&save, sizeof(save), 1, saveGameFile); // load the game save data
	fclose(saveGameFile);

	Resources::mSkillsSystem->SetTimeWarpLevel(save.timeWarpLevel);
	Resources::mSkillsSystem->SetDematerializeLevel(save.dematerializeLevel);
	Resources::mSkillsSystem->SetOverdriveLevel(save.overdriveLevel);
	Resources::mSkillsSystem->SetForceFieldLevel(save.forceFieldLevel);
	Resources::mSkillsSystem->SetExperiencePoints(save.expPointsAvailable);
}
