/*
 * GameLogo.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef GAMELOGO_H_
#define GAMELOGO_H_

#include "ScrollingDrawable.h"

enum GameLogoState	//holds the possible states of the game logo
{
	ENTERING,	//the game logo in entering the screen
	EXITING,	//the game logo is exiting the screen
	ENTERED,	//the game logo is idle after entering the screen (centered on screen)
	EXITED	//the game logo is idle after exiting the screen (off-screen)
};
class GameLogo : public ScrollingDrawable
{
public:
	GameLogo(string pathToImgFile, int scrollSpeedX, int scrollSpeedY);	//creates a game logo using the supplied image file in png format and the scroll speed on the Ox and Oy axis in pixels/second
	void Reset();	//resets the game logo animation
	void SetState(GameLogoState newState); //sets a state for the game logo animation
	GameLogoState GetState();	//returns the current state of the game logo animation
	void Render();	//renders the game logo

private:
	void CheckState();

	GameLogoState mGameLogoState;
	int mScrollSpeedX_backup;
	int mScrollSpeedY_backup;
};

#endif /* GAMELOGO_H_ */
