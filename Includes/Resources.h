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
#include "Player.h"
#include "Enemy.h"
#include "CollisionDetection.h"
#include "SkillsSystem.h"
#include "SaveLoad.h"
#include <string>
#include <list>
#include <time.h>
using namespace std;

#define PLAYER_SHIP_FRAME_WIDTH_SIZE 68
#define PLAYER_SHIP_FRAME_HEIGHT_SIZE 64
#define PLAYER_SHIP_FRAMERATE 15

#define ASTEROID_S_FRAME_WIDTH_SIZE 17
#define ASTEROID_S_FRAME_HEIGHT_SIZE 17
#define ASTEROID_S_FRAMERATE 8

#define ASTEROID_M_FRAME_WIDTH_SIZE 29
#define ASTEROID_M_FRAME_HEIGHT_SIZE 29
#define ASTEROID_M_FRAMERATE 8

#define ASTEROID_L_FRAME_WIDTH_SIZE 49
#define ASTEROID_L_FRAME_HEIGHT_SIZE 49
#define ASTEROID_L_FRAMERATE 8

#define MOON_ROCK_FRAME_WIDTH_SIZE 27
#define MOON_ROCK_FRAME_HEIGHT_SIZE 27
#define MOON_ROCK_FRAMERATE 8

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272

class Resources	//holds string resources for easy editing
{
public:
	static void LoadResources();
	static void AssertResources();

	static string IMG_PRIMARY_BACKGROUND;
	static string IMG_PARALLAX_BACKGROUND;
	static string IMG_GAME_LOGO;
	static string IMG_PLAYER_SHIP;
	static string IMG_PLAYER_SHIP_EXPLOSION;
	static string IMG_DROP_DOWN_MENU;
	static string IMG_UP_DOWN_BUTTONS;
	static string IMG_CROSS_BUTTON;
	static string IMG_ASTEROID_S;
	static string IMG_ASTEROID_M;
	static string IMG_ASTEROID_L;
	static string IMG_MOON_ROCK;

	static string FNT_PARAFONT;
	static string FNT_SMALLSTONE;
	static string FNT_COPPERPLATE;

	static string STR_QUIT_TITLE;
	static string STR_QUIT_MESSAGE;
	static string STR_GAME_OVER_TITLE;
	static string STR_GAME_OVER_MESSAGE;
	static string STR_PRESS_X_TO_START;
	static string STR_MENU_ITEMS[3];
	static string STR_SCORE_OSD;
	static string STR_XP_OSD;
	static string STR_ENERGY_OSD;
	static int MENU_ITEMS_COUNT;

	static Font* mParafontFont;
	static Font* mSmallStoneFont;
	static Font* mCopperPlateFont;
	static Controller* mController;
	static Background* mGameBackground;
	static GameLogo* mGameLogo;
	static DropDownMenu* mDropDownMenu;
	static Drawable* mUpDownButtons;
	static Drawable* mCrossButton;
	static Player* mPlayer;
	static AnimatedSprite* mMoonRock;
	static AnimatedSprite* mAsteroidL;
	static AnimatedSprite* mAsteroidM;
	static AnimatedSprite* mAsteroidS;
	static EnemyList* mEnemyList;
	static SkillsSystem* mSkillsSystem;
	static SaveLoad* mSaveLoad;
};

#endif /* RESOURCE_H_ */
