/*
 * Enemy.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: Bogdan
 */

#include "../Includes/Resources.hpp"
#include "../Includes/Enemy.hpp"

Enemy::Enemy(AnimatedSprite *enemySprite, int posY, int scrollSpeed)
				: AnimatedSprite(enemySprite)
{
	mAsteroidExplosion = new AnimatedSprite(Resources::mAsteroidExplosion);

	SetPositionY(posY);
	SetScrollSpeed(scrollSpeed);
	Reset();
}

Enemy::Enemy(AnimatedSprite *enemySprite, int posY, int scrollSpeed, int frameRate, bool invertedAnimation)
				: AnimatedSprite(enemySprite)
{
	mAsteroidExplosion = new AnimatedSprite(Resources::mAsteroidExplosion);

	SetPositionY(posY);
	SetScrollSpeed(scrollSpeed);
	SetAnimationSpeed(frameRate);
	InvertAnimation(invertedAnimation);
	Reset();
}

Enemy::~Enemy()
{
	delete mAsteroidExplosion;
}

int Enemy::GetWidth()
{
	return GetFrameWidth();
}

int Enemy::GetHeight()
{
	return GetFrameHeight();
}

void Enemy::Reset()
{
	SetPositionX(PSP_SCREEN_WIDTH);
	SetState(SPAWNED);
}

Enemy::EnemyState Enemy::GetState()
{
	return mEnemyState;
}

void Enemy::SetState(EnemyState newState)
{
	if(newState == EXPLODING)
	{
		mAsteroidExplosion->ResetAnimation();
		mAsteroidExplosion->SetPositionXY(GetPositionX() -
										  (mAsteroidExplosion->GetFrameWidth() -
										  GetFrameWidth()) / 2,
										  GetPositionY() -
										  (mAsteroidExplosion->GetFrameHeight() -
										  GetFrameHeight()) / 2);
	}

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
	if(GetState() == EXPLODING)
	{
		mAsteroidExplosion->Render();

		if(mAsteroidExplosion->GetCurrentFrame() == mAsteroidExplosion->GetFrameCount())
			SetState(DESTROYED);
	}

	mPixelsToScroll += GetScrollSpeed() / 60.0f;
	if(abs(mPixelsToScroll) >= 1)
	{
		MoveX(-mPixelsToScroll);
		mPixelsToScroll -= (int)mPixelsToScroll;
	}

	if(GetState() == SPAWNED)
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
	for(list<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
	{
		delete ((Enemy*)(*i));
		i = mEnemyList.erase(i);
	}
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
	for(list<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
		((Enemy*)(*i))->Render();

	EvaluateState();
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

		if(Resources::mPlayer->GetState() == Player::ALIVE)
			mEnemySpeedModifier += 2;
		if(mEnemySpeedModifier >= 500)
			mEnemySpeedModifier = 500;
	}

	//for(list<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); ++i)
	list<Enemy*>::iterator i = mEnemyList.begin();
	while(i != mEnemyList.end())
	{
		if( ((Enemy*)(*i))->GetPositionX() <= -((Enemy*)(*i))->GetFrameWidth())
		{
			delete ((Enemy*)(*i));
			i = mEnemyList.erase(i);
			continue;
		}

		++i;
	}
}
