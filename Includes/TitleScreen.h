/*
 * TitleScreen.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef TITLESCREEN_H_
#define TITLESCREEN_H_

#include "GameLogo.h"
#include "DropDownMenu.h"
#include "Resources.h"

class TitleScreen
{
public:
	TitleScreen();
	~TitleScreen();

	void Render();

private:
	void RenderGameLogo();
	void RenderDropDownMenu();

	GameLogo* mGameLogo;
	DropDownMenu* mDropDownMenu;
};

#endif /* TITLESCREEN_H_ */
