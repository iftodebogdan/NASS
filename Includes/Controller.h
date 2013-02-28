/*
 * Controller.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

enum Keys
{
	DPAD_UP,
	DPAD_LEFT,
	DPAD_DOWN,
	DPAD_RIGHT,
	TRIANGLE,
	SQUARE,
	CROSS,
	CIRCLE,
	L,
	R,
	START,
	SELECT,
	HOLD
};

enum RemoteKeys
{
	PLAYPAUSE,
	FORWARD,
	BACK,
	VOL_UP,
	VOL_DOWN,
	RM_HOLD
};

class Controller
{
public:
	static bool IsPressed(Keys pressedKey);
	static bool IsPressedRemote(RemoteKeys pressedRemoteKey);
	static int AnalogX();
	static int AnalogY();
	static void WaitAnyKey();
};

#endif /* CONTROLLER_H_ */
