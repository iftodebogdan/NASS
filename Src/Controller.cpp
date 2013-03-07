/*
 * Controller.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/Controller.h"

Controller::Controller()
{
	oslSetKeyAutorepeatInit(40);
	oslSetKeyAutorepeatInterval(10);
}

void Controller::ReadKeys()
{
	oslReadKeys();
}

void Controller::ReadRemoteKeys()
{
	oslReadRemoteKeys();
}

bool Controller::IsPressed(Keys pressedKey)
{
	switch(pressedKey)
	{
	case DPAD_UP:
		return osl_keys->pressed.up;
	case DPAD_LEFT:
		return osl_keys->pressed.left;
	case DPAD_DOWN:
		return osl_keys->pressed.down;
	case DPAD_RIGHT:
		return osl_keys->pressed.right;
	case TRIANGLE:
		return osl_keys->pressed.triangle;
	case SQUARE:
		return osl_keys->pressed.square;
	case CROSS:
		return osl_keys->pressed.cross;
	case CIRCLE:
		return osl_keys->pressed.circle;
	case L:
		return osl_keys->pressed.L;
	case R:
		return osl_keys->pressed.R;
	case START:
		return osl_keys->pressed.start;
	case SELECT:
		return osl_keys->pressed.select;
	case HOLD:
		return osl_keys->pressed.hold;
	default:
		return false;
	}
}

bool Controller::IsHeld(Keys heldKey)
{
	switch(heldKey)
	{
	case DPAD_UP:
		return osl_keys->held.up;
	case DPAD_LEFT:
		return osl_keys->held.left;
	case DPAD_DOWN:
		return osl_keys->held.down;
	case DPAD_RIGHT:
		return osl_keys->held.right;
	case TRIANGLE:
		return osl_keys->held.triangle;
	case SQUARE:
		return osl_keys->held.square;
	case CROSS:
		return osl_keys->held.cross;
	case CIRCLE:
		return osl_keys->held.circle;
	case L:
		return osl_keys->held.L;
	case R:
		return osl_keys->held.R;
	case START:
		return osl_keys->held.start;
	case SELECT:
		return osl_keys->held.select;
	case HOLD:
		return osl_keys->held.hold;
	default:
		return false;
	}
}

bool Controller::IsPressedRemote(RemoteKeys pressedRemoteKey)
{
	switch(pressedRemoteKey)
	{
	case PLAYPAUSE:
		return osl_remotekeys->pressed.rmplaypause;
	case FORWARD:
		return osl_remotekeys->pressed.rmforward;
	case BACK:
		return osl_remotekeys->pressed.rmback;
	case VOL_UP:
		return osl_remotekeys->pressed.rmvolup;
	case VOL_DOWN:
		return osl_remotekeys->pressed.rmvoldown;
	case RM_HOLD:
		return osl_remotekeys->pressed.rmhold;
	default:
		return false;
	}
}

bool Controller::IsHeldRemote(RemoteKeys heldRemoteKey)
{
	switch(heldRemoteKey)
	{
	case PLAYPAUSE:
		return osl_remotekeys->held.rmplaypause;
	case FORWARD:
		return osl_remotekeys->held.rmforward;
	case BACK:
		return osl_remotekeys->held.rmback;
	case VOL_UP:
		return osl_remotekeys->held.rmvolup;
	case VOL_DOWN:
		return osl_remotekeys->held.rmvoldown;
	case RM_HOLD:
		return osl_remotekeys->held.rmhold;
	default:
		return false;
	}
}

int Controller::AnalogX()
{
	if(abs(osl_keys->analogX) >= ANALOG_SENSITIVITY)
		return osl_keys->analogX;
	else
		return 0;
}

int Controller::AnalogY()
{
	if(abs(osl_keys->analogY) >= ANALOG_SENSITIVITY)
		return osl_keys->analogY;
	else return 0;
}

void Controller::WaitAnyKey()
{
	oslWaitKey();
}

