/*
 * Resource.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
using namespace std;

class Resources	//holds string resources for easy editing
{
public:
	static string IMG_PRIMARY_BACKGROUND;
	static string IMG_PARALLAX_BACKGROUND;
	static string IMG_GAME_LOGO;
	static string IMG_PLAYER_SHIP;
	static string IMG_DROP_DOWN_MENU;
	static string IMG_UP_DOWN_BUTTONS;
	static string IMG_CROSS_BUTTON;

	static string FNT_PARAFONT;

	static string STR_MENU_ITEMS[3];
	static int MENU_ITEMS_COUNT;
};

#endif /* RESOURCE_H_ */
