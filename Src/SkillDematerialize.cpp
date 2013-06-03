/*
 * SkillDematerialize.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillDematerialize.h"
#include "../Includes/Resources.h"

#define DEMATERIALIZE_LV1 MAX_ENERGY * 100.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV2 MAX_ENERGY * 90.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV3 MAX_ENERGY * 80.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV4 MAX_ENERGY * 70.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV5 MAX_ENERGY * 60.0f / 100.0f / 60.0f

SkillDematerialize::SkillDematerialize()
{
	SetState(READY);

	mDematerializeEffect = new AnimatedSprite(Resources::IMG_DEMATERIALIZE_EFFECT,
											  DEMATERIALIZE_EFFECT_FRAME_WIDTH_SIZE,
											  DEMATERIALIZE_EFFECT_FRAME_HEIGHT_SIZE,
											  DEMATERIALIZE_EFFECT_FRAMERATE);
	oslAssert(mDematerializeEffect != NULL);
}

void SkillDematerialize::SetState(SkillDematerializeState newSkillDematerializeState)
{
	if(newSkillDematerializeState == READY)
		mEnergyCost = 0;

	mSkillDematerializeState = newSkillDematerializeState;
}

SkillDematerialize::SkillDematerializeState SkillDematerialize::GetState()
{
	return mSkillDematerializeState;
}

bool SkillDematerialize::IsActivated()
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
		switch(Resources::mSkillsSystem->GetDematerializeLevel())
		{
		case 1:
			mEnergyCost += DEMATERIALIZE_LV1;
			break;
		case 2:
			mEnergyCost += DEMATERIALIZE_LV2;
			break;
		case 3:
			mEnergyCost += DEMATERIALIZE_LV3;
			break;
		case 4:
			mEnergyCost += DEMATERIALIZE_LV4;
			break;
		case 5:
			mEnergyCost += DEMATERIALIZE_LV5;
			break;
		}

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
