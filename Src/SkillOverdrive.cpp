/*
 * SkillOverdrive.cpp
 *
 *  Created on: Jun 2, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillOverdrive.h"
#include "../Includes/Resources.h"

#define OVERDRIVE_ENERGY_COST 500.0f / 60.0f

SkillOverdrive::SkillOverdrive()
{
	mOverdriveEffect = new AnimatedSprite(
								Resources::IMG_OVERDRIVE_EFFECT,
								OVERDRIVE_EFFECT_FRAME_WIDTH_SIZE,
								OVERDRIVE_EFFECT_FRAME_HEIGHT_SIZE,
								OVERDRIVE_EFFECT_FRAMERATE);
	oslAssert(mOverdriveEffect != NULL);

	SetState(READY);
}

void SkillOverdrive::SetState(SkillOverdriveState newSkillOverdriveState)
{
	if(newSkillOverdriveState == READY)
	{
		mEnergyCost = 0;
		mOverdriveEffect->ResetAnimation();
	}

	mSkillOverdriveState = newSkillOverdriveState;
}

SkillOverdrive::SkillOverdriveState SkillOverdrive::GetState()
{
	return mSkillOverdriveState;
}

bool SkillOverdrive::IsActivated()
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
		return 1.5f;
	case 2:
		return 2.0f;
	case 3:
		return 2.5f;
	case 4:
		return 3.0f;
	case 5:
		return 3.5f;
	}

	return 1.0f;
}

void SkillOverdrive::Evaluate()
{
	if(Resources::mController->IsPressed(Controller::SQUARE) &&
	   GetState() == READY)
	{
		SetState(ACTIVATED);
		return;
	}

	if(Resources::mController->IsHeld(Controller::SQUARE) &&
	   GetState() == ACTIVATED)
	{
		mEnergyCost += OVERDRIVE_ENERGY_COST;

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

	if(GetState() == ACTIVATED)
	{
		mOverdriveEffect->SetPositionXY(Resources::mPlayer->GetPositionX() -
										OVERDRIVE_EFFECT_FRAME_WIDTH_SIZE + 10,
										Resources::mPlayer->GetPositionY() +
										(PLAYER_SHIP_FRAME_HEIGHT_SIZE -
										OVERDRIVE_EFFECT_FRAME_HEIGHT_SIZE) / 2);
		mOverdriveEffect->Render();
	}
}
