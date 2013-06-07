/*
 * CollisionDetection.h
 *
 *  Created on: Mar 8, 2013
 *      Author: Bogdan
 */

#ifndef COLLISIONDETECTION_H_
#define COLLISIONDETECTION_H_

#include "Player.h"
#include "Enemy.h"

class CollisionDetection
{
public:
	static bool CheckForCollisions(Player* playerObject, EnemyList* enemyListObject);
	static bool CheckForPixelPerfectCollisions(Player* playerObject, EnemyList* enemyListObject);
};

#endif /* COLLISIONDETECTION_H_ */
