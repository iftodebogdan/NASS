/*
 * SkillOverdrive.h
 *
 *  Created on: Jun 2, 2013
 *      Author: Bogdan
 */

#ifndef SKILLOVERDRIVE_H_
#define SKILLOVERDRIVE_H_

#include "AnimatedSprite.h"

class SkillOverdrive
{
public:
	enum SkillOverdriveState
	{
		ACTIVATED,
		READY
	};

	SkillOverdrive();

	void SetState(SkillOverdriveState newSkillOverdriveState);
	SkillOverdriveState GetState();
	bool IsActivated();
	float SpeedModifier();

	void Render();

private:
	void Evaluate();

	AnimatedSprite* mOverdriveEffect;

	SkillOverdriveState mSkillOverdriveState;
	float mEnergyCost;
};

#endif /* SKILLOVERDRIVE_H_ */
