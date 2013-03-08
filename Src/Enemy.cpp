/*
 * Enemy.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: Bogdan
 */

#include "../Includes/Resources.h"
#include "../Includes/Enemy.h"

Enemy::Enemy(AnimatedSprite *enemySprite, int posY, int scrollSpeed)
				: AnimatedSprite(enemySprite)
{
	SetPositionY(posY);
	SetScrollSpeed(scrollSpeed);
	Reset();
}

Enemy::Enemy(AnimatedSprite *enemySprite, int posY, int scrollSpeed, int frameRate, bool invertedAnimation)
				: AnimatedSprite(enemySprite)
{
	SetPositionY(posY);
	SetScrollSpeed(scrollSpeed);
	SetAnimationSpeed(frameRate);
	InvertAnimation(invertedAnimation);
	Reset();
}

void Enemy::Reset()
{
	SetPositionX(PSP_SCREEN_WIDTH);
	SetState(SPAWNED);
}

EnemyState Enemy::GetState()
{
	return mEnemyState;
}

void Enemy::SetState(EnemyState newState)
{
	mEnemyState = newState;
}

float Enemy::GetScrollSpeed()
{
	return mScrollSpeed;
}

void Enemy::SetScrollSpeed(float newScrollSpeed)
{
	mScrollSpeed = newScrollSpeed;
	mPixelsToScroll = 0;
}

void Enemy::Render()
{
	mPixelsToScroll += GetScrollSpeed() / 60.0f;
	if(abs(mPixelsToScroll) >= 1)
	{
		MoveX(-mPixelsToScroll);
		mPixelsToScroll -= (int)mPixelsToScroll;
	}

	AnimatedSprite::Render();
}

void Enemy::EvaluateState()
{

}

EnemyList::EnemyList()
{
	Reset();
}

void EnemyList::Reset()
{
	SetEnemySpeedModifier(0);
	mEnemyList.clear();
}

int EnemyList::GetEnemySpeedModifier()
{
	return mEnemySpeedModifier;
}

void EnemyList::SetEnemySpeedModifier(int newEnemySpeedModifier)
{
	if(newEnemySpeedModifier >= 0)
		mEnemySpeedModifier = newEnemySpeedModifier;
}

int EnemyList::GetEnemyCount()
{
	return mEnemyList.size();
}

void EnemyList::Render()
{
	EvaluateState();

	for(list<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
		((Enemy*)(*i))->Render();
}

void EnemyList::EvaluateState()
{
	if( !(int)(oslRandf(0, 100 - mEnemySpeedModifier / 5)) )
	{
		AnimatedSprite* newEnemySprite = NULL;
		int newEnemyPosY = NULL;

		switch((int)oslRandf(1, 100) % 10)
		{
		case 0:
		case 1:
		case 2:
			newEnemySprite = Resources::mAsteroidL;
			newEnemyPosY = oslRandf(0, PSP_SCREEN_HEIGHT-Resources::mAsteroidL->GetFrameHeight());
			break;

		case 3:
		case 4:
		case 5:
			newEnemySprite = Resources::mAsteroidM;
			newEnemyPosY = oslRandf(0, PSP_SCREEN_HEIGHT-Resources::mAsteroidM->GetFrameHeight());
			break;

		case 6:
		case 7:
		case 8:
			newEnemySprite = Resources::mAsteroidS;
			newEnemyPosY = oslRandf(0, PSP_SCREEN_HEIGHT-Resources::mAsteroidS->GetFrameHeight());
			break;

		case 9:
			newEnemySprite = Resources::mMoonRock;
			newEnemyPosY = oslRandf(0, PSP_SCREEN_HEIGHT-Resources::mMoonRock->GetFrameHeight());
			break;
		}

		mEnemyList.push_back(
					new Enemy(
							newEnemySprite,
							newEnemyPosY,
							oslRandf(25, 100) + mEnemySpeedModifier,
							(int)oslRandf(
									newEnemySprite->GetAnimationSpeed(),
									newEnemySprite->GetAnimationSpeed() * 2
									),
							(int)oslRandf(0, 2)
					)
		);

		mEnemySpeedModifier += 2;
		if(mEnemySpeedModifier >= 500)
			mEnemySpeedModifier = 500;
	}

	for(list<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
		if( ((Enemy*)(*i))->GetPositionX() <= -((Enemy*)(*i))->GetFrameWidth())
		{
			delete ((Enemy*)(*i));
			i = mEnemyList.erase(i);
		}
}
