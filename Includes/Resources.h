/*
 * Resource.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "Audio.h"
#include "AnimatedSprite.h"
#include "Background.h"
#include "GameLogo.h"
#include "DropDownMenu.h"
#include "Controller.h"
#include "Font.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionDetection.h"
#include "SkillsSystem.h"
#include "SaveLoad.h"
#include "Screen.h"

#include <string>
using namespace std;

#define COLOR_RED RGB(255, 0, 0)
#define COLOR_BLUE RGB(0, 0, 255)
#define COLOR_GREEN RGB(0, 255, 0)
#define COLOR_WHITE RGB(255, 255, 255)
#define COLOR_BLACK RGB(0, 0, 0)
#define COLOR_TRANSPARENT RGB(255,0,255)

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

#define ASTEROID_EXPLOSION_FRAME_WIDTH_SIZE 77
#define ASTEROID_EXPLOSION_FREME_HEIGHT_SIZE 79
#define ASTEROID_EXPLOSION_FRAMERATE 15

#define WARP_CROSSHAIR_FRAME_WIDTH_SIZE 100
#define WARP_CROSSHAIR_FRAME_HEIGHT_SIZE 100
#define WARP_CROSSHAIR_FRAMERATE 10

#define WARP_EFFECT_FRAME_WIDTH_SIZE 100
#define WARP_EFFECT_FRAME_HEIGHT_SIZE 100
#define WARP_EFFECT_FRAMERATE 15

#define DEMATERIALIZE_EFFECT_FRAME_WIDTH_SIZE 68
#define DEMATERIALIZE_EFFECT_FRAME_HEIGHT_SIZE 64
#define DEMATERIALIZE_EFFECT_FRAMERATE 15

#define OVERDRIVE_EFFECT_FRAME_WIDTH_SIZE 92
#define OVERDRIVE_EFFECT_FRAME_HEIGHT_SIZE 40
#define OVERDRIVE_EFFECT_FRAMERATE 15

#define FORCE_FIELD_EFFECT_FRAME_WIDTH_SIZE 83
#define FORCE_FIELD_EFFECT_FRAME_HEIGHT_SIZE 80
#define FORCE_FIELD_EFFECT_FRAMERATE 15

#define MAX_ENERGY 1000

#define SCORE_TO_XP_RATIO 10

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
	static string IMG_CROSS_BUTTON_SMALL;
	static string IMG_CIRCLE_BUTTON;
	static string IMG_SQUARE_BUTTON_SMALL;
	static string IMG_TRIANGLE_BUTTON;
	static string IMG_TRIANGLE_BUTTON_SMALL;
	static string IMG_PSP_CONTROLS;
	static string IMG_ASTEROID_S;
	static string IMG_ASTEROID_M;
	static string IMG_ASTEROID_L;
	static string IMG_MOON_ROCK;
	static string IMG_ASTEROID_EXPLOSION;
	static string IMG_WARP_CROSSHAIR;
	static string IMG_WARP_EFFECT;
	static string IMG_DEMATERIALIZE_EFFECT;
	static string IMG_OVERDRIVE_EFFECT;
	static string IMG_FORCE_FIELD_EFFECT;

	static string SND_DROP_DOWN_MENU_SWEEP;
	static string SND_IN_GAME_BGM;
	static string SND_MAIN_MENU_BGM;
	static string SND_MENU_CANCEL;
	static string SND_MENU_NAVIGATE;
	static string SND_MENU_SELECT;
	static string SND_PLAYER_EXPLOSION;
	static string SND_SKILL_DEMATERIALIZE_EFFECT;
	static string SND_SKILL_FORCE_FIELD_EFFECT;
	static string SND_SKILL_FORCE_FIELD_IMPACT;
	static string SND_SKILL_OVERDRIVE_EFFECT;
	static string SND_WARP_EFFECT;
	static string SND_WARP_TARGETING;

	static string FNT_PARAFONT;
	static string FNT_SMALLSTONE;
	static string FNT_COPPERPLATE;

	static string STR_RETURN_TO_TITLE_SCREEN_TITLE;
	static string STR_RETURN_TO_TITLE_SCREEN_MESSAGE;
	static string STR_GAME_OVER_TITLE;
	static string STR_GAME_OVER_MESSAGE;
	static string STR_GAME_OVER_XP_EARNED_MESSAGE;
	static string STR_GAME_OVER_NEW_HI_SCORE_MESSAGE;
	static string STR_PRESS_X_TO_START;
	static string STR_PRESS_O_TO_GO_BACK;
	static string STR_PRESS_X_TO_CONTINUE;
	static string STR_SCORE_OSD;
	static string STR_XP_OSD;
	static string STR_HI_SCORE_OSD;
	static string STR_ENERGY_OSD;
	static string STR_WARP_SKILL;
	static string STR_DEMATERIALIZE_SKILL;
	static string STR_OVERDRIVE_SKILL;
	static string STR_FORCE_FIELD_SKILL;
	static string STR_SKILLS_SCREEN_XP_COST;
	static string STR_SKILLS_SCREEN_REFUND;
	static string STR_SKILLS_SCREEN_XP_COST_2;
	static string STR_SKILLS_SCREEN_REFUND_2;
	static string STR_DRIVE_CORE_LOAD;
	static string STR_SKILLS_SCREEN_AVAILABLE_XP;
	static string STR_SKILLS_SCREEN_INFO_BUTTON_LABEL;
	static string STR_DRIVE_CORE_OVERLOADED_MESSAGE;
	static string STR_DRIVE_CORE_OVERLOADED_TITLE;
	static string STR_SKILL_LEVEL_UP_CONFIRMATION_MESSAGE;
	static string STR_SKILL_LEVEL_UP_CONFIRMATION_TITLE;
	static string STR_SKILL_REFUND_CONFIRMATION_MESSAGE;
	static string STR_SKILL_REFUND_CONFIRMATION_TITLE;
	static string STR_SKILL_LEVEL_5_MESSAGE;
	static string STR_SKILL_LEVEL_5_TITLE;
	static string STR_SKILL_LEVEL_0_MESSAGE;
	static string STR_SKILL_LEVEL_0_TITLE;
	static string STR_SKILL_NO_XP_MESSAGE;
	static string STR_SKILL_NO_XP_TITLE;
	static string STR_RESET_PROGRESS_MESSAGE;
	static string STR_RESET_PROGRESS_TITLE;
	static string STR_QUIT_GAME_MESSAGE;
	static string STR_QUIT_GAME_TITLE;

	static string STR_WARP_INFO_MESSAGE;
	static string STR_DEMATERIALIZE_INFO_MESSAGE;
	static string STR_OVERDRIVE_INFO_MESSAGE;
	static string STR_FORCE_FIELD_INFO_MESSAGE;

	static string STR_MENU_ITEMS[4];
	static int MENU_ITEMS_COUNT;

	static Game* mGameApp;

	static Font* mParafontFont;
	static Font* mSmallStoneFont;
	static Font* mCopperPlateFont;

	static Controller* mController;

	static Background* mGameBackground;

	static GameLogo* mGameLogo;

	static DropDownMenu* mDropDownMenu;

	static Drawable* mUpDownButtons;
	static Drawable* mCrossButton;
	static Drawable* mCrossButton_small;
	static Drawable* mCircleButton;
	static Drawable* mSquareButton_small;
	static Drawable* mTriangleButton;
	static Drawable* mTriangleButton_small;
	static Drawable* mPSPControls;

	static Player* mPlayer;

	static AnimatedSprite* mMoonRock;
	static AnimatedSprite* mAsteroidL;
	static AnimatedSprite* mAsteroidM;
	static AnimatedSprite* mAsteroidS;
	static AnimatedSprite* mAsteroidExplosion;

	static Screen* mScreen;

	static Sound* mDropDownMenuSweep;
	static Sound* mInGameBGM;
	static Sound* mMainMenuBGM;
	static Sound* mMenuCancel;
	static Sound* mMenuNavigate;
	static Sound* mMenuSelect;
	static Sound* mPlayerExplosion;
	static Sound* mSkillDematerializeSFX;
	static Sound* mSkillForceFieldSFX;
	static Sound* mSkillForceFieldImpactSFX;
	static Sound* mSkillOverdriveSFX;
	static Sound* mSkillWarpSFX;
	static Sound* mSkillWarpTargetingSFX;

	static EnemyList* mEnemyList;

	static SkillsSystem* mSkillsSystem;

	static SaveLoad* mSaveLoad;
};

#endif /* RESOURCE_H_ */
