/*
 * SkillDematerialize.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillDematerialize.h"
#include "../Includes/Resources.h"

SkillDematerialize::SkillDematerialize()
{
	mDematerializeEffect = new AnimatedSprite(Resources::IMG_DEMATERIALIZE_EFFECT,
											  DEMATERIALIZE_EFFECT_FRAME_WIDTH_SIZE,
											  DEMATERIALIZE_EFFECT_FRAME_HEIGHT_SIZE,
											  DEMATERIALIZE_EFFECT_FRAMERATE);
	oslAssert(mDematerializeEffect != NULL);

	mSkillDematerializeState = READY;
	mEnergyCost = 0;
	mEnergyCostPerSecond = 0;
}

void SkillDematerialize::SetState(SkillDematerializeState newSkillDematerializeState)
{
	switch(Resources::mSkillsSystem->GetDematerializeLevel())
	{
	case 1:
		mEnergyCostPerSecond = DEMATERIALIZE_ENERGY_COST_LV1;
		break;
	case 2:
		mEnergyCostPerSecond = DEMATERIALIZE_ENERGY_COST_LV2;
		break;
	case 3:
		mEnergyCostPerSecond = DEMATERIALIZE_ENERGY_COST_LV3;
		break;
	case 4:
		mEnergyCostPerSecond = DEMATERIALIZE_ENERGY_COST_LV4;
		break;
	case 5:
		mEnergyCostPerSecond = DEMATERIALIZE_ENERGY_COST_LV5;
		break;
	}

	if(newSkillDematerializeState == READY)
	{
		if(Resources::mSkillDematerializeEffect->IsPlaying())
			Resources::mSkillDematerializeEffect->Stop();

		mEnergyCost = 0;
		mDematerializeEffect->ResetAnimation();
	}

	if(newSkillDematerializeState == ACTIVE)
		if(!Resources::mSkillDematerializeEffect->IsPlaying())
			Resources::mSkillDematerializeEffect->PlayLooped();

	mSkillDematerializeState = newSkillDematerializeState;
}

SkillDematerialize::SkillDematerializeState SkillDematerialize::GetState()
{
	return mSkillDematerializeState;
}

bool SkillDematerialize::IsActive()
{
	if(GetState() == READY)
		return false;

	return true;
}

void SkillDematerialize::Evaluate()
{
	if(Resources::mController->IsPressed(Controller::CIRCLE) &&
	   GetState() == READY)
	{
		SetState(ACTIVE);
		return;
	}

	if(Resources::mController->IsHeld(Controller::CIRCLE) &&
	   GetState() == ACTIVE)
	{
		mEnergyCost += (float)mEnergyCostPerSecond / 60.0f;

		if(Resources::mSkillsSystem->DepleteEnergy(floor(mEnergyCost)))
			mEnergyCost -= floor(mEnergyCost);
		else
			SetState(READY);
	}
	else
		SetState(READY);
}

void SkillDematerialize::Render()
{
	if(Resources::mSkillsSystem->GetDematerializeLevel())
		Evaluate();
	else
		return;

	if(GetState() == ACTIVE)
	{
		mDematerializeEffect->SetPositionXY(Resources::mPlayer->GetPositionX() -
											(DEMATERIALIZE_EFFECT_FRAME_WIDTH_SIZE -
											PLAYER_SHIP_FRAME_WIDTH_SIZE) / 2,
											Resources::mPlayer->GetPositionY() -
											(DEMATERIALIZE_EFFECT_FRAME_HEIGHT_SIZE -
											PLAYER_SHIP_FRAME_HEIGHT_SIZE) / 2);
		mDematerializeEffect->Render();
	}
}
