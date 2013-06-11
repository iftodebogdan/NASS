/*
 * SkillWarp.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillWarp.h"
#include "../Includes/Resources.h"

SkillWarp::SkillWarp()
{
	mWarpCrosshair = new AnimatedSprite(
							Resources::IMG_WARP_CROSSHAIR,
							WARP_CROSSHAIR_FRAME_WIDTH_SIZE,
							WARP_CROSSHAIR_FRAME_HEIGHT_SIZE,
							WARP_CROSSHAIR_FRAMERATE);
	mWarpEffect = new AnimatedSprite(
						Resources::IMG_WARP_EFFECT,
						WARP_EFFECT_FRAME_WIDTH_SIZE,
						WARP_EFFECT_FRAME_HEIGHT_SIZE,
						WARP_EFFECT_FRAMERATE);

	oslAssert(mWarpCrosshair != NULL);
	oslAssert(mWarpEffect != NULL);

	mSkillWarpState = READY;
	mEnergyCost = 0;
	mWarpCrosshairXOffset = 0;
}

void SkillWarp::SetState(SkillWarpState newSkillWarpState)
{
	switch(Resources::mSkillsSystem->GetWarpLevel())
	{
	case 1:
		mWarpCrosshairXOffset = WARP_DISTANCE_LV1;
		break;
	case 2:
		mWarpCrosshairXOffset = WARP_DISTANCE_LV2;
		break;
	case 3:
		mWarpCrosshairXOffset = WARP_DISTANCE_LV3;
		break;
	case 4:
		mWarpCrosshairXOffset = WARP_DISTANCE_LV4;
		break;
	case 5:
		mWarpCrosshairXOffset = WARP_DISTANCE_LV5;
		break;
	}

	switch(Resources::mSkillsSystem->GetWarpLevel())
	{
	case 1:
		mEnergyCost = WARP_ACTIVATION_ENERGY_COST_LV1;
		break;
	case 2:
		mEnergyCost = WARP_ACTIVATION_ENERGY_COST_LV2;
		break;
	case 3:
		mEnergyCost = WARP_ACTIVATION_ENERGY_COST_LV3;
		break;
	case 4:
		mEnergyCost = WARP_ACTIVATION_ENERGY_COST_LV4;
		break;
	case 5:
		mEnergyCost = WARP_ACTIVATION_ENERGY_COST_LV5;
		break;
	}

	if(newSkillWarpState == READY)
		if(Resources::mSkillWarpTargetingSFX->IsPlaying())
			Resources::mSkillWarpTargetingSFX->Stop();

	if(newSkillWarpState == ACTIVE)
		if(!Resources::mSkillWarpTargetingSFX->IsPlaying())
			Resources::mSkillWarpTargetingSFX->PlayLooped();

	if(newSkillWarpState == WARPING)
	{
		if(Resources::mSkillWarpTargetingSFX->IsPlaying())
			Resources::mSkillWarpTargetingSFX->Stop();
		if(!Resources::mSkillWarpSFX->IsPlaying())
			Resources::mSkillWarpSFX->Play();
	}

	mSkillWarpState = newSkillWarpState;
}

SkillWarp::SkillWarpState SkillWarp::GetState()
{
	return mSkillWarpState;
}

bool SkillWarp::IsActive()
{
	if(GetState() == READY)
		return false;
	else
		return true;
}

void SkillWarp::Evaluate()
{
	if(Resources::mController->IsPressed(Controller::TRIANGLE) &&
	   GetState() == ACTIVE)
	{
		Resources::mSkillsSystem->SetEnergy(0);

		mWarpEffect->ResetAnimation();
		mWarpEffect->SetPositionXY(Resources::mPlayer->GetPositionX() - (WARP_EFFECT_FRAME_WIDTH_SIZE - PLAYER_SHIP_FRAME_WIDTH_SIZE) / 2,
								   Resources::mPlayer->GetPositionY() - (WARP_EFFECT_FRAME_HEIGHT_SIZE - PLAYER_SHIP_FRAME_HEIGHT_SIZE) / 2);

		switch(Resources::mSkillsSystem->GetWarpLevel())
		{
		case 1:
			Resources::mPlayer->MoveX(WARP_DISTANCE_LV1);
			break;
		case 2:
			Resources::mPlayer->MoveX(WARP_DISTANCE_LV2);
			break;
		case 3:
			Resources::mPlayer->MoveX(WARP_DISTANCE_LV3);
			break;
		case 4:
			Resources::mPlayer->MoveX(WARP_DISTANCE_LV4);
			break;
		case 5:
			Resources::mPlayer->MoveX(WARP_DISTANCE_LV5);
			break;
		}

		if(Resources::mPlayer->GetPositionX() > PSP_SCREEN_WIDTH - Resources::mPlayer->GetFrameWidth())
			Resources::mPlayer->SetPositionX(PSP_SCREEN_WIDTH - Resources::mPlayer->GetFrameWidth());

		SetState(WARPING);
	}

	if(Resources::mController->IsPressed(Controller::TRIANGLE) &&
	   Resources::mSkillsSystem->GetEnergy() == MAX_ENERGY &&
	   Resources::mSkillsSystem->DepleteEnergy(mEnergyCost) &&
	   GetState() == READY)
	{
		SetState(ACTIVE);
		mWarpCrosshair->ResetAnimation();
	}

	if(GetState() == ACTIVE)
		mWarpCrosshair->SetPositionXY(Resources::mPlayer->GetPositionX() + mWarpCrosshairXOffset -
										(WARP_CROSSHAIR_FRAME_WIDTH_SIZE - PLAYER_SHIP_FRAME_WIDTH_SIZE) / 2,
									  Resources::mPlayer->GetPositionY() - (WARP_CROSSHAIR_FRAME_HEIGHT_SIZE - PLAYER_SHIP_FRAME_HEIGHT_SIZE) / 2);

	if(GetState() == ACTIVE && mWarpCrosshair->GetCurrentFrame() == mWarpCrosshair->GetFrameCount())
		SetState(READY);

	if(GetState() == WARPING && mWarpEffect->GetCurrentFrame() == mWarpEffect->GetFrameCount())
		SetState(READY);
}

void SkillWarp::RenderDurationBar()
{
	int durationBarX0 = mWarpCrosshair->GetPositionX();
	int durationBarY0 = mWarpCrosshair->GetPositionY() + WARP_CROSSHAIR_FRAME_HEIGHT_SIZE;
	int durationBarX1;
	int durationBarY1 = durationBarY0 + 5;

	durationBarX1 = (float)durationBarX0 +
					(float)WARP_CROSSHAIR_FRAME_WIDTH_SIZE *
					(((float)mWarpCrosshair->GetFrameCount() -
					(float)mWarpCrosshair->GetCurrentFrame() - 1) /
					(float)mWarpCrosshair->GetFrameCount());

	oslDrawFillRect(durationBarX0,
					durationBarY0,
					durationBarX1,
					durationBarY1,
					COLOR_WHITE);
	oslDrawRect(durationBarX0,
				durationBarY0,
				durationBarX0 + WARP_CROSSHAIR_FRAME_WIDTH_SIZE,
				durationBarY1,
				COLOR_WHITE);
}

void SkillWarp::Render()
{
	if(Resources::mSkillsSystem->GetWarpLevel())
		Evaluate();
	else
		return;

	if(GetState() == ACTIVE)
	{
		RenderDurationBar();
		mWarpCrosshair->Render();
	}

	if(GetState() == WARPING)
		mWarpEffect->Render();
}
