/*
 * Player.cpp
 *
 *  Created on: Mar 6, 2013
 *      Author: Bogdan
 */

#include "../Includes/Player.hpp"

#include "../Includes/Resources.hpp"

#define PLAYER_SPEED 2

Player::Player(
		string pathToShipImgFile,
		string pathToShipExplosionImgFile,
		int frameWidthSize,
		int frameHeigthSize,
		int framesPerSecond)
			:AnimatedSprite(
					pathToShipImgFile,
					frameWidthSize,
					frameHeigthSize,
					framesPerSecond)
{
	mPlayerShipExplosion = new AnimatedSprite(
									pathToShipExplosionImgFile,
									frameWidthSize,
									frameHeigthSize,
									framesPerSecond
									);

	Reset();
}

int Player::GetWidth()
{
	return GetFrameWidth();
}

int Player::GetHeight()
{
	return GetFrameHeight();
}

void Player::Reset()
{
	SetState(SPAWNING);
	SetPositionXY( -GetFrameWidth(), (PSP_SCREEN_HEIGHT - GetFrameHeight()) / 2 );
}

void Player::Render()
{
	EvaluateState();
}

Player::PlayerState Player::GetState()
{
	return mPlayerState;
}

void Player::SetState(PlayerState newState)
{
	mPlayerState = newState;

	if(newState == DYING)
	{
		if(Resources::mSkillsSystem->mSkillWarp->IsActive() &&
		   Resources::mSkillWarpTargetingSFX->IsPlaying())
			Resources::mSkillWarpTargetingSFX->Stop();
		if(Resources::mSkillsSystem->mSkillOverdrive->IsActive() &&
				   Resources::mSkillOverdriveSFX->IsPlaying())
					Resources::mSkillOverdriveSFX->Stop();
	}
}

void Player::EvaluateState()
{
	if(GetState() == SPAWNING && GetPositionX() < 0)
	{
		MoveX(1);
		if(GetPositionX() >= 0)
			SetState(ALIVE);
	}

	if(GetState() == ALIVE)
	{
		if(Resources::mController->IsHeld(Controller::DPAD_UP))
		{
			MoveY(-PLAYER_SPEED * Resources::mSkillsSystem->mSkillOverdrive->SpeedModifier());
			if(GetPositionY() < 0)
				SetPositionY(0);
		}
		else
			if(Resources::mController->IsHeld(Controller::DPAD_DOWN))
			{
				MoveY(PLAYER_SPEED * Resources::mSkillsSystem->mSkillOverdrive->SpeedModifier());
				if(GetPositionY() > PSP_SCREEN_HEIGHT - GetFrameHeight())
					SetPositionY(PSP_SCREEN_HEIGHT - GetFrameHeight());
			}

		if(Resources::mController->IsHeld(Controller::DPAD_LEFT))
		{
			MoveX(-PLAYER_SPEED * Resources::mSkillsSystem->mSkillOverdrive->SpeedModifier());
			if(GetPositionX() < 0)
				SetPositionX(0);
		}
		else
			if(Resources::mController->IsHeld(Controller::DPAD_RIGHT))
			{
				MoveX(PLAYER_SPEED * Resources::mSkillsSystem->mSkillOverdrive->SpeedModifier());
				if(GetPositionX() > PSP_SCREEN_WIDTH - GetFrameWidth())
					SetPositionX(PSP_SCREEN_WIDTH - GetFrameWidth());
			}
	}

	if(GetState() == DYING)
	{
		mPlayerShipExplosion->SetPositionXY(GetPositionX(), GetPositionY());
		mPlayerShipExplosion->Render();

		if(mPlayerShipExplosion->GetCurrentFrame() == mPlayerShipExplosion->GetFrameCount())
		{
			SetState(DEAD);
			mPlayerShipExplosion->ResetAnimation();
		}

		return;
	}

	if(GetState() == DEAD)
		return;

	AnimatedSprite::Render();
}
