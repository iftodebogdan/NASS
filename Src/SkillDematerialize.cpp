/*
 * SkillDematerialize.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillDematerialize.h"
#include "../Includes/Resources.h"

#define DEMATERIALIZE_LV1 MAX_ENERGY * 100.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV2 MAX_ENERGY * 85.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV3 MAX_ENERGY * 70.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV4 MAX_ENERGY * 50.0f / 100.0f / 60.0f
#define DEMATERIALIZE_LV5 MAX_ENERGY * 30.0f / 100.0f / 60.0f

SkillDematerialize::SkillDematerialize()
{
	SetState(READY);

	mPlayerShip_dematerialized = new Drawable(Resources::IMG_PLAYER_SHIP_DEMATERIALIZED);

	oslAssert(mPlayerShip_dematerialized != NULL);
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
	if(Resources::mController->IsPressed(CIRCLE) &&
	   GetState() == READY)
	{
		SetState(ACTIVATED);
		return;
	}

	if(Resources::mController->IsHeld(CIRCLE) &&
	   GetState() == ACTIVATED)
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
		{
			mEnergyCost -= floor(mEnergyCost);
			mPlayerShip_dematerialized->Draw(Resources::mPlayer->GetPositionX(), Resources::mPlayer->GetPositionY());
		}
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
}
