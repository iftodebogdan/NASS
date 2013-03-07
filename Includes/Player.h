/*
 * Player.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Bogdan
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_SPEED 2

enum PlayerState
{
	ALIVE,
	DEAD,
	SPAWNING,
	DYING
};

class Player : public AnimatedSprite
{
public:
	Player(						//creates an animated sprite
		string pathToImgFile,	//an image file in png format
		int frameWidthSize,		//the width of a frame
		int frameHeigthSize,	//the height of a frame
		int framesPerSecond);	//animation speed in frames/second

	void Reset();
	void Render();
	void EvaluateState();
};

#endif /* PLAYER_H_ */
