/*
 * Player.cpp
 *
 *  Created on: Mar 6, 2013
 *      Author: Bogdan
 */

#include "../Includes/Resources.h"
#include "../Includes/Player.h"

Player::Player(
		string pathToImgFile,
		int frameWidthSize,
		int frameHeigthSize,
		int framesPerSecond)
			:AnimatedSprite(
					pathToImgFile,
					frameWidthSize,
					frameHeigthSize,
					framesPerSecond)
{

}

void Player::Reset()
{
	SetPositionXY( 0, (PSP_SCREEN_HEIGHT - GetFrameHeight()) / 2 );
}

void Player::Render()
{
	EvaluateState();
	AnimatedSprite::Render();
}

void Player::EvaluateState()
{
	if(Resources::mController->IsHeld(DPAD_UP))
	{
		MoveY(-PLAYER_SPEED);
		if(GetPositionY() < 0)
			SetPositionY(0);
	}
	else
		if(Resources::mController->IsHeld(DPAD_DOWN))
		{
			MoveY(PLAYER_SPEED);
			if(GetPositionY() > PSP_SCREEN_HEIGHT - GetFrameHeight())
				SetPositionY(PSP_SCREEN_HEIGHT - GetFrameHeight());
		}

	if(Resources::mController->IsHeld(DPAD_LEFT))
	{
		MoveX(-PLAYER_SPEED);
		if(GetPositionX() < 0)
			SetPositionX(0);
	}
	else
		if(Resources::mController->IsHeld(DPAD_RIGHT))
		{
			MoveX(PLAYER_SPEED);
			if(GetPositionX() > PSP_SCREEN_WIDTH - GetFrameWidth())
				SetPositionX(PSP_SCREEN_WIDTH - GetFrameWidth());
		}
}
