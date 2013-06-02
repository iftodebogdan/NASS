/*
 * Controller.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <oslib/oslib.h>

class Controller
{
public:
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

	Controller();

	void ReadKeys();
	void ReadRemoteKeys();
	bool IsPressed(Keys pressedKey);
	bool IsHeld(Keys heldKey);
	bool IsPressedRemote(RemoteKeys pressedRemoteKey);
	bool IsHeldRemote(RemoteKeys heldRemoteKey);
	int AnalogX();
	int AnalogY();
	void WaitAnyKey();
};

#endif /* CONTROLLER_H_ */
