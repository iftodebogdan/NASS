/*
 * SkillDematerialize.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Bogdan
 */

#ifndef SKILLDEMATERIALIZE_H_
#define SKILLDEMATERIALIZE_H_

#include "Drawable.h"
#include <math.h>

class SkillDematerialize
{
	enum SkillDematerializeState
	{
		ACTIVATED,
		READY
	};

public:
	SkillDematerialize();

	void SetState(SkillDematerializeState newSkillDematerializeState);
	SkillDematerializeState GetState();
	bool IsActivated();

	void Render();

private:
	void Evaluate();

	Drawable* mPlayerShip_dematerialized;

	SkillDematerializeState mSkillDematerializeState;
	float mEnergyCost;
};

#endif /* SKILLDEMATERIALIZE_H_ */
