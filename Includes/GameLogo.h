/*
 * GameLogo.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef GAMELOGO_H_
#define GAMELOGO_H_

#include "ScrollDrawable.h"

enum GameLogoState
{
	ENTERING,
	EXITING,
	IDLE
};
class GameLogo : public ScrollDrawable
{
public:
	GameLogo(string pathToImgFile, int scrollSpeedX, int scrollSpeedY);
	void Reset();
	void SetState(GameLogoState newState);
	GameLogoState GetState();
	void Render();

private:
	void CheckState();

	GameLogoState mGameLogoState;
	int mScrollSpeedX_backup;
	int mScrollSpeedY_backup;
};

#endif /* GAMELOGO_H_ */
