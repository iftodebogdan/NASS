/*
 * SaveLoad.cpp
 *
 *  Created on: May 31, 2013
 *      Author: Bogdan
 */

#include "../Includes/SaveLoad.hpp"

#include "../Includes/Resources.hpp"
#include "../Includes/BinaryFileIO.hpp"

void SaveLoad::AutoSaveGame()
{
	SaveGame save;
	memset(&save, 0, sizeof(save));
	save.warpLevel = Resources::mSkillsSystem->GetWarpLevel();
	save.dematerializeLevel = Resources::mSkillsSystem->GetDematerializeLevel();
	save.overdriveLevel = Resources::mSkillsSystem->GetOverdriveLevel();
	save.forceFieldLevel = Resources::mSkillsSystem->GetForceFieldLevel();
	save.expPointsAvailable = Resources::mSkillsSystem->GetExperiencePoints();
	save.playerHiScore = Resources::mSkillsSystem->GetHiScore();

	BinaryFileIO *saveGameFile;
	saveGameFile = new BinaryFileIO("savegame.bin");

	saveGameFile->Write(&save, sizeof(save));

	delete saveGameFile;
}

void SaveLoad::LoadSaveGame()
{
	SaveGame save;
	memset(&save, 0, sizeof(save));

	BinaryFileIO *saveGameFile;
	saveGameFile = new BinaryFileIO("savegame.bin");

	if(!saveGameFile->IsFileOpen())
	{
		AutoSaveGame();
		return;
	}

	saveGameFile->Read(&save, sizeof(save));

	delete saveGameFile;

	Resources::mSkillsSystem->SetWarpLevel(save.warpLevel);
	Resources::mSkillsSystem->SetDematerializeLevel(save.dematerializeLevel);
	Resources::mSkillsSystem->SetOverdriveLevel(save.overdriveLevel);
	Resources::mSkillsSystem->SetForceFieldLevel(save.forceFieldLevel);
	Resources::mSkillsSystem->SetExperiencePoints(save.expPointsAvailable);
	Resources::mSkillsSystem->SetHiScore(save.playerHiScore);
}

void SaveLoad::ResetProgress()
{
	Resources::mSkillsSystem->SetWarpLevel(0);
	Resources::mSkillsSystem->SetDematerializeLevel(0);
	Resources::mSkillsSystem->SetOverdriveLevel(0);
	Resources::mSkillsSystem->SetForceFieldLevel(0);
	Resources::mSkillsSystem->SetExperiencePoints(0);
	Resources::mSkillsSystem->SetHiScore(0);

	AutoSaveGame();
}
