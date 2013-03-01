/*
 * Controller.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <oslib/oslib.h>

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
	Controller();

	void ReadKeys();
	void ReadRemoteKeys();
	bool IsPressed(Keys pressedKey);
	bool IsPressedRemote(RemoteKeys pressedRemoteKey);
	int AnalogX();
	int AnalogY();
	void WaitAnyKey();
};

#endif /* CONTROLLER_H_ */
