/*
 * Enemy.h
 *
 *  Created on: Mar 7, 2013
 *      Author: Bogdan
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <list>
using namespace std;

enum EnemyState
{
	SPAWNED,
	DESTROYED,
	EXPLODING
};

class Enemy : public AnimatedSprite
{
public:
	Enemy(AnimatedSprite *enemySprite, int posY, int scrollSpeed);
	Enemy(AnimatedSprite *enemySprite, int posY, int scrollSpeed, int frameRate, bool invertedAnimation);

	int GetWidth();
	int GetHeight();

	void Reset();
	EnemyState GetState();
	void SetState(EnemyState newState);
	float GetScrollSpeed();
	void SetScrollSpeed(float newScrollSpeed);
	void Render();

private:
	void EvaluateState();

	EnemyState mEnemyState;
	int mScrollSpeed;
	float mPixelsToScroll;
};

class EnemyList
{
	friend class CollisionDetection;

public:
	EnemyList();

	void Reset();
	void Render();

	int GetEnemySpeedModifier();
	void SetEnemySpeedModifier(int newEnemySpeedModifier);
	int GetEnemyCount();

private:
	void EvaluateState();

	list<Enemy*> mEnemyList;
	int mEnemySpeedModifier;
};

#endif /* ENEMY_H_ */
