/*
 * DropDownMenu.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef DROPDOWNMENU_H_
#define DROPDOWNMENU_H_

#include "Controller.h"
#include "Font.h"
#include "ScrollingDrawable.h"
//#include "Resources.h" //->Moved to DropDownMenu.cpp

#define POS_Y_RETRACTED -GetHeight() + 16 -1

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
	DropDownMenu(
			string pathToImgFile,
			unsigned scrollSpeed,
			DropDownMenuState dropDownMenuState);

	void Reset();

	void SetState(DropDownMenuState newState);
	DropDownMenuState GetState();

	void SetScrollSpeed(unsigned scrollSpeed);
	unsigned GetScrollSpeed();

	void Render();

private:
	void CheckState();
	void RenderMenuItems(string* menuItems);

	DropDownMenuState mDropDownMenuState;
	unsigned mScrollSpeed;
	int mMenuItemIndex;
};

#endif /* DROPDOWNMENU_H_ */
