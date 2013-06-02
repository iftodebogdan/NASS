/*
 * Player.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Bogdan
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player : public AnimatedSprite
{
public:
	enum PlayerState
	{
		ALIVE,
		DEAD,
		SPAWNING,
		DYING
	};

	Player(									//creates an animated sprite
		string pathToShipImgFile,			//an image file in png format
		string pathToShipExplosionImgFile,
		int frameWidthSize,					//the width of a frame
		int frameHeigthSize,				//the height of a frame
		int framesPerSecond);				//animation speed in frames/second

	int GetWidth();
	int GetHeight();

	void Reset();
	void Render();
	PlayerState GetState();
	void SetState(PlayerState newState);

private:
	void EvaluateState();

	PlayerState mPlayerState;
	AnimatedSprite* mPlayerShipExplosion;
};

#endif /* PLAYER_H_ */
