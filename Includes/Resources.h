/*
 * Resource.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "AnimatedSprite.h"
#include "Background.h"
#include "GameLogo.h"
#include "DropDownMenu.h"
#include "Controller.h"
#include "Font.h"
#include <string>
using namespace std;

class Resources	//holds string resources for easy editing
{
public:
	static void LoadResources();
	static void AssertResources();

	static string IMG_PRIMARY_BACKGROUND;
	static string IMG_PARALLAX_BACKGROUND;
	static string IMG_GAME_LOGO;
	static string IMG_PLAYER_SHIP;
	static string IMG_DROP_DOWN_MENU;
	static string IMG_UP_DOWN_BUTTONS;
	static string IMG_CROSS_BUTTON;

	static string FNT_PARAFONT;

	static string STR_PRESS_X_TO_START;
	static string STR_MENU_ITEMS[3];
	static int MENU_ITEMS_COUNT;

	static Font* mParafontFont;
	static Controller* mController;
	static Background* mGameBackground;
	static GameLogo* mGameLogo;
	static DropDownMenu* mDropDownMenu;
	static Drawable* mUpDownButtons;
	static Drawable* mCrossButton;
};

#endif /* RESOURCE_H_ */
