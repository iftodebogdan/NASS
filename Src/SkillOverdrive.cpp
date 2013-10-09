/*
 * SkillOverdrive.cpp
 *
 *  Created on: Jun 2, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillOverdrive.hpp"
#include "../Includes/Resources.hpp"

SkillOverdrive::SkillOverdrive()
{
	mOverdriveEffect = new AnimatedSprite(
								Resources::IMG_OVERDRIVE_EFFECT,
								OVERDRIVE_EFFECT_FRAME_WIDTH_SIZE,
								OVERDRIVE_EFFECT_FRAME_HEIGHT_SIZE,
								OVERDRIVE_EFFECT_FRAMERATE);
	oslAssert(mOverdriveEffect != NULL);

	mSkillOverdriveState = READY;
	mEnergyCost = 0;
	mEnergyCostPerSecond = 0;
}

void SkillOverdrive::SetState(SkillOverdriveState newSkillOverdriveState)
{
	switch(Resources::mSkillsSystem->GetOverdriveLevel())
	{
	case 1:
		mEnergyCostPerSecond = OVERDRIVE_ENERGY_COST_LV1;
		break;
	case 2:
		mEnergyCostPerSecond = OVERDRIVE_ENERGY_COST_LV2;
		break;
	case 3:
		mEnergyCostPerSecond = OVERDRIVE_ENERGY_COST_LV3;
		break;
	case 4:
		mEnergyCostPerSecond = OVERDRIVE_ENERGY_COST_LV4;
		break;
	case 5:
		mEnergyCostPerSecond = OVERDRIVE_ENERGY_COST_LV5;
		break;
	}

	if(newSkillOverdriveState == READY)
	{
		if(Resources::mSkillOverdriveSFX->IsPlaying())
			Resources::mSkillOverdriveSFX->Stop();

		mEnergyCost = 0;
		mOverdriveEffect->ResetAnimation();
	}

	if(newSkillOverdriveState == ACTIVE)
		if(!Resources::mSkillOverdriveSFX->IsPlaying())
			Resources::mSkillOverdriveSFX->PlayLooped();

	mSkillOverdriveState = newSkillOverdriveState;
}

SkillOverdrive::SkillOverdriveState SkillOverdrive::GetState()
{
	return mSkillOverdriveState;
}

bool SkillOverdrive::IsActive()
{
	if(GetState() == READY)
		return false;

	return true;
}

float SkillOverdrive::SpeedModifier()
{
	if(GetState() == READY)
		return 1.0f;

	switch(Resources::mSkillsSystem->GetOverdriveLevel())
	{
	case 1:
		return OVERDRIVE_BOOST_LV1;
	case 2:
		return OVERDRIVE_BOOST_LV2;
	case 3:
		return OVERDRIVE_BOOST_LV3;
	case 4:
		return OVERDRIVE_BOOST_LV4;
	case 5:
		return OVERDRIVE_BOOST_LV5;
	}

	return 1.0f;
}

void SkillOverdrive::Evaluate()
{
	if(Resources::mController->IsPressed(Controller::SQUARE) &&
	   GetState() == READY)
	{
		SetState(ACTIVE);
		return;
	}

	if(Resources::mController->IsHeld(Controller::SQUARE) &&
	   GetState() == ACTIVE)
	{
		mEnergyCost += (float)mEnergyCostPerSecond / (float)Resources::mDebug->GetFrameRate();

		if(Resources::mSkillsSystem->DepleteEnergy(floor(mEnergyCost)))
			mEnergyCost -= floor(mEnergyCost);
		else
			SetState(READY);
	}
	else
		SetState(READY);
}

void SkillOverdrive::Render()
{
	if(Resources::mSkillsSystem->GetOverdriveLevel())
		Evaluate();
	else
		return;

	if(GetState() == ACTIVE)
	{
		mOverdriveEffect->SetPositionXY(Resources::mPlayer->GetPositionX() -
										OVERDRIVE_EFFECT_FRAME_WIDTH_SIZE + 10,
										Resources::mPlayer->GetPositionY() +
										(PLAYER_SHIP_FRAME_HEIGHT_SIZE -
										OVERDRIVE_EFFECT_FRAME_HEIGHT_SIZE) / 2);
		mOverdriveEffect->Render();
	}
}
