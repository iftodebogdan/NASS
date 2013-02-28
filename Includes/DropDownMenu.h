/*
 * DropDownMenu.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef DROPDOWNMENU_H_
#define DROPDOWNMENU_H_

#include "ScrollingDrawable.h"

enum DropDownMenuState
{
	EXTENDING,
	EXTENDED,
	RETRACTING,
	RETRACTED
};

class DropDownMenu : public ScrollingDrawable
{
public:
	DropDownMenu(string pathToImgFile);
	DropDownMenu(string pathToImgFile, unsigned scrollSpeed);

	void SetState(DropDownMenuState newState);
	DropDownMenuState GetState();

	void SetScrollSpeed(unsigned scrollSpeed);
	unsigned GetScrollSpeed();

	void Render();

private:
	void CheckState();

	DropDownMenuState mDropDownMenuState;
	unsigned mScrollSpeed;
};

#endif /* DROPDOWNMENU_H_ */
