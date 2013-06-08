/*
 * SaveLoad.cpp
 *
 *  Created on: May 31, 2013
 *      Author: Bogdan
 */

#include "../Includes/SaveLoad.h"

#include "../Includes/Resources.h"
#include "../Includes/BinaryFileIO.h"

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
	if(oslMessageBox(
		Resources::STR_RESET_PROGRESS_MESSAGE.c_str(),
		Resources::STR_RESET_PROGRESS_TITLE.c_str(),
		oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_YES, OSL_KEY_CIRCLE, OSL_MB_NO, 0, 0)) == OSL_MB_NO)
		{
			Resources::mMenuCancel->Play();
			return;
		}
	else
		Resources::mMenuSelect->Play();

	Resources::mSkillsSystem->SetWarpLevel(0);
	Resources::mSkillsSystem->SetDematerializeLevel(0);
	Resources::mSkillsSystem->SetOverdriveLevel(0);
	Resources::mSkillsSystem->SetForceFieldLevel(0);
	Resources::mSkillsSystem->SetExperiencePoints(0);
	Resources::mSkillsSystem->SetHiScore(0);

	AutoSaveGame();
}
