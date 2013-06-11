/*
 * CollisionDetection.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: Bogdan
 */

#include "../Includes/CollisionDetection.h"

#include "../Includes/Resources.h"
#include <list>
using namespace std;

bool CollisionDetection::CheckForCollisions(Player *playerObject, EnemyList *enemyListObject)
{
	if(Resources::mSkillsSystem->mSkillDematerialize->IsActive() &&
	   !Resources::mSkillsSystem->mSkillForceField->IsActive())
		return false;

	float playerObjectRadius;
	if(!Resources::mSkillsSystem->mSkillForceField->IsActive())
		playerObjectRadius = (float)(playerObject->GetWidth()) / 2.0f;
	else
		playerObjectRadius = (float)(FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE) / 2.0f;
	float playerObjectCenterX = (float)playerObject->GetPositionX() + (float)playerObject->GetWidth() / 2.0f;
	float playerObjectCenterY = (float)playerObject->GetPositionY() + (float)playerObject->GetHeight() / 2.0f;

	for(list<Enemy*>::iterator i = enemyListObject->mEnemyList.begin(); i != enemyListObject->mEnemyList.end(); i++)
	{
		if(((Enemy*)(*i))->GetState() == Enemy::DESTROYED)
		{
			delete ((Enemy*)(*i));
			i = enemyListObject->mEnemyList.erase(i);
			continue;
		}

		if(((Enemy*)(*i))->GetState() == Enemy::EXPLODING)
			continue;

		float enemyObjectRadius = (float)(((Enemy*)(*i))->GetWidth()) / 2.0f;
		float enemyObjectCenterX = (float)(((Enemy*)(*i))->GetPositionX()) + (float)(((Enemy*)(*i))->GetWidth()) / 2.0f;
		float enemyObjectCenterY = (float)(((Enemy*)(*i))->GetPositionY()) + (float)(((Enemy*)(*i))->GetHeight()) / 2.0f;

		float distX = playerObjectCenterX - enemyObjectCenterX;
		float distY = playerObjectCenterY - enemyObjectCenterY;

		float squareDist = pow(distX, 2) + pow(distY, 2);

		if(squareDist <= pow(playerObjectRadius + enemyObjectRadius, 2))
		{
			if(Resources::mDebug->GetDebugModeNoCollision())
				return false;

			if(((Enemy*)(*i))->GetState() == Enemy::SPAWNED)
				((Enemy*)(*i))->SetState(Enemy::EXPLODING);

			if(Resources::mSkillsSystem->mSkillForceField->IsActive())
			{
				Resources::mSkillsSystem->mSkillForceField->ForceFieldImpact();
				return false;
			}

			return true;	//oslPrintf("Objects are colliding\n");
		}
	}

	return false;
}

bool CollisionDetection::CheckForPixelPerfectCollisions(Player* playerObject, EnemyList* enemyListObject)
{
	if(Resources::mSkillsSystem->mSkillDematerialize->IsActive() &&
	   !Resources::mSkillsSystem->mSkillForceField->IsActive())
		return false;

	if(Resources::mSkillsSystem->mSkillForceField->IsActive())
		return CheckForCollisions(playerObject, enemyListObject);

	for(list<Enemy*>::iterator i = enemyListObject->mEnemyList.begin(); i != enemyListObject->mEnemyList.end(); i++)
	{
		if(((Enemy*)(*i))->GetState() == Enemy::DESTROYED)
		{
			delete ((Enemy*)(*i));
			i = enemyListObject->mEnemyList.erase(i);
			continue;
		}

		if(((Enemy*)(*i))->GetState() == Enemy::EXPLODING)
			continue;

		if(playerObject->GetPositionX() + playerObject->GetWidth() >= ((Enemy*)(*i))->GetPositionX() &&
		   playerObject->GetPositionX() <= ((Enemy*)(*i))->GetPositionX() + ((Enemy*)(*i))->GetWidth() &&
		   playerObject->GetPositionY() + playerObject->GetHeight() >= ((Enemy*)(*i))->GetPositionY() &&
		   playerObject->GetPositionY() <= ((Enemy*)(*i))->GetPositionY() + ((Enemy*)(*i))->GetHeight())
		{
			int boxXBegin = max(playerObject->GetPositionX(), ((Enemy*)(*i))->GetPositionX());
			int boxXEnd = min(playerObject->GetPositionX() + playerObject->GetWidth(),
							  ((Enemy*)(*i))->GetPositionX() + ((Enemy*)(*i))->GetWidth());
			int boxYBegin = max(playerObject->GetPositionY(), ((Enemy*)(*i))->GetPositionY());
			int boxYEnd = min(playerObject->GetPositionY() + playerObject->GetHeight(),
							  ((Enemy*)(*i))->GetPositionY() + ((Enemy*)(*i))->GetHeight());

			if(Resources::mDebug->GetDebugModeCollisionTest())
			{
				oslDrawFillRect(playerObject->GetPositionX(),
								playerObject->GetPositionY(),
								playerObject->GetPositionX() + playerObject->GetFrameWidth(),
								playerObject->GetPositionY() + playerObject->GetFrameHeight(),
								RGBA(255, 255, 255, 128));
				oslDrawFillRect(((Enemy*)(*i))->GetPositionX(),
								((Enemy*)(*i))->GetPositionY(),
								((Enemy*)(*i))->GetPositionX() + ((Enemy*)(*i))->GetFrameWidth(),
								((Enemy*)(*i))->GetPositionY() + ((Enemy*)(*i))->GetFrameHeight(),
								RGBA(255, 255, 255, 128));
				oslDrawFillRect(boxXBegin, boxYBegin, boxXEnd, boxYEnd, RGBA(0, 0, 0, 128));
			}

			for(int boxX = boxXBegin; boxX <= boxXEnd; boxX++)
				for(int boxY = boxYBegin; boxY <= boxYEnd; boxY++)
					if((playerObject->GetFramePixel(abs(boxX - playerObject->GetPositionX() - 1), abs(boxY - playerObject->GetPositionY() - 1)) >> 24) != 0 &&
					   (((Enemy*)(*i))->GetFramePixel(abs(boxX - ((Enemy*)(*i))->GetPositionX() - 1), abs(boxY - ((Enemy*)(*i))->GetPositionY() - 1)) >> 24) != 0)
					{
						if(Resources::mDebug->GetDebugModeCollisionTest())
						{
							oslDrawLine(PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT, boxX, boxY, COLOR_WHITE);
							oslWaitKey();
							return false;
						}

						if(Resources::mDebug->GetDebugModeNoCollision())
							return false;

						if(((Enemy*)(*i))->GetState() == Enemy::SPAWNED)
							((Enemy*)(*i))->SetState(Enemy::EXPLODING);

						if(Resources::mSkillsSystem->mSkillForceField->IsActive())
						{
							Resources::mSkillsSystem->mSkillForceField->ForceFieldImpact();
							return false;
						}

						return true;
					}
		}
	}

	return false;
}
