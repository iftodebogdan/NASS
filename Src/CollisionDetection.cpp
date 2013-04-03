/*
 * CollisionDetection.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: Bogdan
 */

#include "../Includes/CollisionDetection.h"

void CollisionDetection::CheckForCollisions(Player *playerObject, EnemyList *enemyListObject)
{
	float playerObjectRadius = (float)playerObject->GetWidth() / 2.0f;
	float playerObjectCenterX = (float)playerObject->GetPositionX() + (float)playerObject->GetWidth() / 2.0f;
	float playerObjectCenterY = (float)playerObject->GetPositionY() + (float)playerObject->GetHeight() / 2.0f;

	for(list<Enemy*>::iterator i = enemyListObject->mEnemyList.begin(); i != enemyListObject->mEnemyList.end(); i++)
	{
		float enemyObjectRadius = (float)(((Enemy*)(*i))->GetWidth()) / 2.0f;
		float enemyObjectCenterX = (float)(((Enemy*)(*i))->GetPositionX()) + (float)(((Enemy*)(*i))->GetWidth()) / 2.0f;
		float enemyObjectCenterY = (float)(((Enemy*)(*i))->GetPositionY()) + (float)(((Enemy*)(*i))->GetHeight()) / 2.0f;

		float distX = playerObjectCenterX - enemyObjectCenterX;
		float distY = playerObjectCenterY - enemyObjectCenterY;

		float squareDist = pow(distX, 2) + pow(distY, 2);

		if(squareDist <= pow(playerObjectRadius + enemyObjectRadius, 2))
			oslPrintf("Objects are colliding\n");
	}
}
