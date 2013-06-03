/*
 * SkillWarp.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#include "../Includes/SkillWarp.h"
#include "../Includes/Resources.h"

#define WARP_LV1 50
#define WARP_LV2 70
#define WARP_LV3 100
#define WARP_LV4 140
#define WARP_LV5 190

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

	SetState(READY);
}

void SkillWarp::SetState(SkillWarpState newSkillWarpState)
{
	mSkillWarpState = newSkillWarpState;
}

SkillWarp::SkillWarpState SkillWarp::GetState()
{
	return mSkillWarpState;
}

bool SkillWarp::IsActivated()
{
	if(GetState() == READY)
		return false;
	else
		return true;
}

void SkillWarp::Evaluate()
{
	if(Resources::mController->IsPressed(Controller::TRIANGLE) &&
	   GetState() == ACTIVATED)
	{
		Resources::mSkillsSystem->SetEnergy(0);

		mWarpEffect->ResetAnimation();
		mWarpEffect->SetPositionXY(Resources::mPlayer->GetPositionX() - (WARP_EFFECT_FRAME_WIDTH_SIZE - PLAYER_SHIP_FRAME_WIDTH_SIZE) / 2,
								   Resources::mPlayer->GetPositionY() - (WARP_EFFECT_FRAME_HEIGHT_SIZE - PLAYER_SHIP_FRAME_HEIGHT_SIZE) / 2);

		switch(Resources::mSkillsSystem->GetWarpLevel())
		{
		case 1:
			Resources::mPlayer->MoveX(WARP_LV1 + PLAYER_SHIP_FRAME_WIDTH_SIZE);
			break;
		case 2:
			Resources::mPlayer->MoveX(WARP_LV2 + PLAYER_SHIP_FRAME_WIDTH_SIZE);
			break;
		case 3:
			Resources::mPlayer->MoveX(WARP_LV3 + PLAYER_SHIP_FRAME_WIDTH_SIZE);
			break;
		case 4:
			Resources::mPlayer->MoveX(WARP_LV4 + PLAYER_SHIP_FRAME_WIDTH_SIZE);
			break;
		case 5:
			Resources::mPlayer->MoveX(WARP_LV5 + PLAYER_SHIP_FRAME_WIDTH_SIZE);
			break;
		}

		if(Resources::mPlayer->GetPositionX() > PSP_SCREEN_WIDTH - Resources::mPlayer->GetFrameWidth())
			Resources::mPlayer->SetPositionX(PSP_SCREEN_WIDTH - Resources::mPlayer->GetFrameWidth());

		SetState(WARPING);
	}

	if(Resources::mController->IsPressed(Controller::TRIANGLE) &&
	   Resources::mSkillsSystem->GetEnergy() == MAX_ENERGY &&
	   Resources::mSkillsSystem->DepleteEnergy(MAX_ENERGY / 2) &&
	   GetState() == READY)
	{
		SetState(ACTIVATED);
		mWarpCrosshair->ResetAnimation();
	}

	if(GetState() == ACTIVATED)
	{
		unsigned warpCrosshairXOffset = 0;
		switch(Resources::mSkillsSystem->GetWarpLevel())
		{
		case 1:
			warpCrosshairXOffset = WARP_LV1;
			break;
		case 2:
			warpCrosshairXOffset = WARP_LV2;
			break;
		case 3:
			warpCrosshairXOffset = WARP_LV3;
			break;
		case 4:
			warpCrosshairXOffset = WARP_LV4;
			break;
		case 5:
			warpCrosshairXOffset = WARP_LV5;
			break;
		}

		mWarpCrosshair->SetPositionXY(Resources::mPlayer->GetPositionX() + PLAYER_SHIP_FRAME_WIDTH_SIZE + warpCrosshairXOffset -
										(WARP_CROSSHAIR_FRAME_WIDTH_SIZE - PLAYER_SHIP_FRAME_WIDTH_SIZE) / 2,
									  Resources::mPlayer->GetPositionY() - (WARP_CROSSHAIR_FRAME_HEIGHT_SIZE - PLAYER_SHIP_FRAME_HEIGHT_SIZE) / 2);
	}

	if(GetState() == ACTIVATED && mWarpCrosshair->GetCurrentFrame() == mWarpCrosshair->GetFrameCount())
		SetState(READY);

	if(GetState() == WARPING && mWarpEffect->GetCurrentFrame() == mWarpEffect->GetFrameCount())
		SetState(READY);
}

void SkillWarp::Render()
{
	if(Resources::mSkillsSystem->GetWarpLevel())
		Evaluate();
	else
		return;

	if(GetState() == ACTIVATED)
		mWarpCrosshair->Render();

	if(GetState() == WARPING)
		mWarpEffect->Render();
}
