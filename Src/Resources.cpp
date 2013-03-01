/*
 * Resource.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/Resources.h"

string Resources::IMG_PRIMARY_BACKGROUND = "Res/img/PrimaryBackground.png";
string Resources::IMG_PARALLAX_BACKGROUND = "Res/img/ParallaxBackground.png";
string Resources::IMG_GAME_LOGO = "Res/img/GameLogo.png";
string Resources::IMG_PLAYER_SHIP = "Res/img/PlayerShip.png";
string Resources::IMG_DROP_DOWN_MENU = "Res/img/DropDownMenu.png";
string Resources::IMG_UP_DOWN_BUTTONS = "Res/img/UpDownButtons.png";
string Resources::IMG_CROSS_BUTTON = "Res/img/CrossButton.png";

string Resources::FNT_PARAFONT = "Res/fnt/parafont.png";

string Resources::STR_PRESS_X_TO_START = "Press       to start";
string Resources::STR_MENU_ITEMS[3] = {"Item1", "Item2", "Item3"};
int Resources::MENU_ITEMS_COUNT = 3;

Font* Resources::mParafontFont = NULL;
Controller* Resources::mController = NULL;
Background* Resources::mGameBackground = NULL;
GameLogo* Resources::mGameLogo = NULL;
Drawable* Resources::mUpDownButtons = NULL;
Drawable* Resources::mCrossButton = NULL;
DropDownMenu* Resources::mDropDownMenu = NULL;

void Resources::LoadResources()
{
	mParafontFont = new Font(Resources::FNT_PARAFONT);
	mController = new Controller();
	mGameBackground = new Background(Resources::IMG_PRIMARY_BACKGROUND, Resources::IMG_PARALLAX_BACKGROUND, -30, 0, -60, 0);
	mGameLogo = new GameLogo(Resources::IMG_GAME_LOGO, -200, 0);
	mDropDownMenu = new DropDownMenu(Resources::IMG_DROP_DOWN_MENU, 200, RETRACTED);
	mUpDownButtons = new Drawable(Resources::IMG_UP_DOWN_BUTTONS);
	mCrossButton = new Drawable(Resources::IMG_CROSS_BUTTON);
}

void Resources::AssertResources()
{
	oslAssert(mParafontFont != NULL);
	oslAssert(mController != NULL);
	oslAssert(mGameBackground != NULL);
	oslAssert(mGameLogo != NULL);
	oslAssert(mDropDownMenu != NULL);
	oslAssert(mUpDownButtons != NULL);
	oslAssert(mCrossButton != NULL);
}
