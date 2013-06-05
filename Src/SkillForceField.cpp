/*
 * SkillForceField.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillForceField.h"
#include "../Includes/Resources.h"

#define FORCE_FIELD_DURATION_LV1 1
#define FORCE_FIELD_DURATION_LV2 2
#define FORCE_FIELD_DURATION_LV3 3
#define FORCE_FIELD_DURATION_LV4 4
#define FORCE_FIELD_DURATION_LV5 5

#define FORCE_FIELD_IMPACTS_LV1 1
#define FORCE_FIELD_IMPACTS_LV2 2
#define FORCE_FIELD_IMPACTS_LV3 3
#define FORCE_FIELD_IMPACTS_LV4 4
#define FORCE_FIELD_IMPACTS_LV5 5

#define FORCE_FIELD_ENERGY_COST_LV1 MAX_ENERGY * 50 / 100
#define FORCE_FIELD_ENERGY_COST_LV2 MAX_ENERGY * 55 / 100
#define FORCE_FIELD_ENERGY_COST_LV3 MAX_ENERGY * 60 / 100
#define FORCE_FIELD_ENERGY_COST_LV4 MAX_ENERGY * 65 / 100
#define FORCE_FIELD_ENERGY_COST_LV5 MAX_ENERGY * 70 / 100

#define FORCE_FIELD_ENERGY_REGEN_LV1 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV2 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV3 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV4 MAX_ENERGY * 10 / 100
#define FORCE_FIELD_ENERGY_REGEN_LV5 MAX_ENERGY * 10 / 100

SkillForceField::SkillForceField()
{
	mForceFieldEffect = new AnimatedSprite(Resources::IMG_FORCE_FIELD_EFFECT,
										   FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE,
										   FORCE_FIELD_EFFECT_FRAME_HEIGHT_SIZE,
										   FORCE_FIELD_EFFECT_FRAMERATE);
	oslAssert(mForceFieldEffect != NULL);

	mSkillForceFieldState = READY;
	mSkillDuration = 0;
	mEnergyCost = 0;
	mForceFieldImpacts = 0;
	mEnergyRegen = 0;
}

unsigned SkillForceField::GetSkillEnergyCost()
{
	switch(Resources::mSkillsSystem->GetForceFieldLevel())
	{
	case 1:
		return FORCE_FIELD_ENERGY_COST_LV1;
		break;
	case 2:
		return FORCE_FIELD_ENERGY_COST_LV2;
		break;
	case 3:
		return FORCE_FIELD_ENERGY_COST_LV3;
		break;
	case 4:
		return FORCE_FIELD_ENERGY_COST_LV4;
		break;
	case 5:
		return FORCE_FIELD_ENERGY_COST_LV5;
		break;
	}

	return 0;
}

void SkillForceField::SetState(SkillForceFieldState newSkillForceFieldState)
{
	switch(Resources::mSkillsSystem->GetForceFieldLevel())
	{
	case 1:
		mEnergyRegen = FORCE_FIELD_ENERGY_REGEN_LV1;
		break;
	case 2:
		mEnergyRegen = FORCE_FIELD_ENERGY_REGEN_LV2;
		break;
	case 3:
		mEnergyRegen = FORCE_FIELD_ENERGY_REGEN_LV3;
		break;
	case 4:
		mEnergyRegen = FORCE_FIELD_ENERGY_REGEN_LV4;
		break;
	case 5:
		mEnergyRegen = FORCE_FIELD_ENERGY_REGEN_LV5;
		break;
	}

	mEnergyCost = GetSkillEnergyCost();

	if(newSkillForceFieldState == ACTIVE)
	{
		Resources::mSkillForceFieldEffect->Play();

		mSkillDuration = GetSkillDuration();
		mForceFieldImpacts = GetForceFieldImpacts();

		mForceFieldEffect->ResetAnimation();
	}

	mSkillForceFieldState = newSkillForceFieldState;
}

SkillForceField::SkillForceFieldState SkillForceField::GetState()
{
	return mSkillForceFieldState;
}

bool SkillForceField::IsActive()
{
	if(GetState() != READY)
		return true;

	return false;
}

void SkillForceField::ForceFieldImpact()
{
	if(mForceFieldImpacts)
	{
		mForceFieldImpacts--;
		Resources::mSkillsSystem->RegenerateEnergy(mEnergyRegen);
	}
}

void SkillForceField::Evaluate()
{
	if(Resources::mController->IsPressed(Controller::CROSS) &&
	   GetState() == READY &&
	   Resources::mSkillsSystem->DepleteEnergy(mEnergyCost))
		SetState(ACTIVE);

	if(GetState() == ACTIVE)
	{
		if(mSkillDuration)
			mSkillDuration--;
		else
			SetState(READY);

		if(!mForceFieldImpacts)
			SetState(READY);
	}
}

unsigned SkillForceField::GetSkillDuration()
{
	switch(Resources::mSkillsSystem->GetForceFieldLevel())
	{
	case 1:
		return FORCE_FIELD_DURATION_LV1 * 60;
		break;
	case 2:
		return FORCE_FIELD_DURATION_LV2 * 60;
		break;
	case 3:
		return FORCE_FIELD_DURATION_LV3 * 60;
		break;
	case 4:
		return FORCE_FIELD_DURATION_LV4 * 60;
		break;
	case 5:
		return FORCE_FIELD_DURATION_LV5 * 60;
		break;
	}

	return 0;
}

int SkillForceField::GetForceFieldImpacts()
{
	switch(Resources::mSkillsSystem->GetForceFieldLevel())
	{
	case 1:
		return FORCE_FIELD_IMPACTS_LV1;
		break;
	case 2:
		return FORCE_FIELD_IMPACTS_LV2;
		break;
	case 3:
		return FORCE_FIELD_IMPACTS_LV3;
		break;
	case 4:
		return FORCE_FIELD_IMPACTS_LV4;
		break;
	case 5:
		return FORCE_FIELD_IMPACTS_LV5;
		break;
	}

	return 0;
}

void SkillForceField::RenderDurationBar()
{
	int durationBarX0 = mForceFieldEffect->GetPositionX();
	int durationBarY0 = mForceFieldEffect->GetPositionY() + FORCE_FIELD_EFFECT_FRAME_HEIGHT_SIZE;
	int durationBarX1;
	int durationBarY1 = durationBarY0 + 5;

	int hpBarX0 = mForceFieldEffect->GetPositionX();
	int hpBarY0 = durationBarY1 + 2;
	int hpBarX1;
	int hpBarY1 = hpBarY0 + 5;

	durationBarX1 = (float)durationBarX0 +
					(float)FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE *
					((float)mSkillDuration /
					GetSkillDuration());

	hpBarX1 = (float)hpBarX0 +
			  (float)FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE *
			  ((float)mForceFieldImpacts /
			  (float)GetForceFieldImpacts());

	oslDrawFillRect(durationBarX0,
					durationBarY0,
					durationBarX1,
					durationBarY1,
					COLOR_WHITE);
	oslDrawRect(durationBarX0,
				durationBarY0,
				durationBarX0 + FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE,
				durationBarY1,
				COLOR_WHITE);

	oslDrawFillRect(hpBarX0,
					hpBarY0,
					hpBarX1,
					hpBarY1,
					COLOR_WHITE);
	oslDrawRect(hpBarX0,
				hpBarY0,
				hpBarX0 + FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE,
				hpBarY1,
				COLOR_WHITE);
}

void SkillForceField::Render()
{
	if(Resources::mSkillsSystem->GetForceFieldLevel())
		Evaluate();
	else
		return;

	if(GetState() == ACTIVE)
	{
		mForceFieldEffect->SetPositionXY(Resources::mPlayer->GetPositionX() -
										 (FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE -
										 PLAYER_SHIP_FRAME_WIDTH_SIZE) / 2,
										 Resources::mPlayer->GetPositionY() -
										 (FORCE_FIELD_EFFECT_FRAME_HEIGHT_SIZE -
										 PLAYER_SHIP_FRAME_HEIGHT_SIZE) / 2);
		mForceFieldEffect->Render();
		RenderDurationBar();
	}
}
