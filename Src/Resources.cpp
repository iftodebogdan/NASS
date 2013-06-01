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
string Resources::IMG_PLAYER_SHIP_EXPLOSION = "Res/img/PlayerShipExplosion.png";
string Resources::IMG_DROP_DOWN_MENU = "Res/img/DropDownMenu.png";
string Resources::IMG_UP_DOWN_BUTTONS = "Res/img/UpDownButtons.png";
string Resources::IMG_CROSS_BUTTON = "Res/img/CrossButton.png";
string Resources::IMG_CROSS_BUTTON_SMALL = "Res/img/CrossButton_small.png";
string Resources::IMG_CIRCLE_BUTTON = "Res/img/CircleButton.png";
string Resources::IMG_SQUARE_BUTTON_SMALL = "Res/img/SquareButton_small.png";
string Resources::IMG_ASTEROID_S = "Res/img/AsteroidS.png";
string Resources::IMG_ASTEROID_M = "Res/img/AsteroidM.png";
string Resources::IMG_ASTEROID_L = "Res/img/AsteroidL.png";
string Resources::IMG_MOON_ROCK = "Res/img/MoonRock.png";

string Resources::FNT_PARAFONT = "Res/fnt/parafont.png";
string Resources::FNT_SMALLSTONE = "Res/fnt/smallstone.png";
string Resources::FNT_COPPERPLATE = "Res/fnt/copperplate.png";

string Resources::STR_QUIT_TITLE = "Quit?";
string Resources::STR_QUIT_MESSAGE = "Would you like to quit and return to the title screen?";
string Resources::STR_GAME_OVER_TITLE = "Game Over!";
string Resources::STR_GAME_OVER_MESSAGE = "Your ship has been destroyed!\nXP earned: ";
string Resources::STR_PRESS_X_TO_START = "Press       to start";
string Resources::STR_PRESS_O_TO_GO_BACK = "Back       ";
string Resources::STR_SCORE_OSD = "Score: ";
string Resources::STR_XP_OSD = "XP: ";
string Resources::STR_ENERGY_OSD = "Energy";
string Resources::STR_WARP_SKILL = "Warp";
string Resources::STR_DEMATERIALIZE_SKILL = "Dematerialize";
string Resources::STR_OVERDRIVE_SKILL = "Overdrive";
string Resources::STR_FORCE_FIELD_SKILL = "Force Field";
string Resources::STR_SKILLS_SCREEN_XP_COST = "Level Up: -";
string Resources::STR_SKILLS_SCREEN_REFUND = "Refund: +";
string Resources::STR_SKILLS_SCREEN_XP_COST_2 = "XP and +10% Drive Core load";
string Resources::STR_SKILLS_SCREEN_REFUND_2 = "XP and -10% Drive Core load";
string Resources::STR_DRIVE_CORE_LOAD = "Drive Core load: ";
string Resources::STR_SKILLS_SCREEN_AVAILABLE_XP = "Available XP: ";
string Resources::STR_DRIVE_CORE_OVERLOADED_MESSAGE = "The ship's Drive Core has a 100% load and cannot be upgraded any further.";
string Resources::STR_DRIVE_CORE_OVERLOADED_TITLE = "Drive Core Overloaded!";
string Resources::STR_SKILL_LEVEL_UP_CONFIRMATION_MESSAGE = "Are you sure you want to level up that skill?";
string Resources::STR_SKILL_LEVEL_UP_CONFIRMATION_TITLE = "Level up";
string Resources::STR_SKILL_REFUND_CONFIRMATION_MESSAGE = "Are you sure you want to refund that skill point?";
string Resources::STR_SKILL_REFUND_CONFIRMATION_TITLE = "Refund";
string Resources::STR_SKILL_LEVEL_5_MESSAGE = "This skill is already at its maximum level. It cannot be upgraded any further.";
string Resources::STR_SKILL_LEVEL_5_TITLE = "Cannot level up!";
string Resources::STR_SKILL_LEVEL_0_MESSAGE = "You haven't invested any points in this skill. It cannot be refunded.";
string Resources::STR_SKILL_LEVEL_0_TITLE = "Cannot refund!";
string Resources::STR_MENU_ITEMS[3] = {"Skills", "Quit"};
int Resources::MENU_ITEMS_COUNT = 2;

Game* Resources::mGameApp = NULL;
Font* Resources::mParafontFont = NULL;
Font* Resources::mSmallStoneFont = NULL;
Font* Resources::mCopperPlateFont = NULL;
Controller* Resources::mController = NULL;
Background* Resources::mGameBackground = NULL;
GameLogo* Resources::mGameLogo = NULL;
Drawable* Resources::mUpDownButtons = NULL;
Drawable* Resources::mCrossButton = NULL;
Drawable* Resources::mCrossButton_small = NULL;
Drawable* Resources::mCircleButton = NULL;
Drawable* Resources::mSquareButton_small = NULL;
DropDownMenu* Resources::mDropDownMenu = NULL;
Player* Resources::mPlayer = NULL;
AnimatedSprite* Resources::mAsteroidL = NULL;
AnimatedSprite* Resources::mAsteroidM = NULL;
AnimatedSprite* Resources::mAsteroidS = NULL;
AnimatedSprite* Resources::mMoonRock = NULL;
EnemyList* Resources::mEnemyList = NULL;
SkillsSystem* Resources::mSkillsSystem = NULL;
SaveLoad* Resources::mSaveLoad = NULL;

void Resources::LoadResources()
{
	oslSrand(time(NULL));
	mParafontFont = new Font(FNT_PARAFONT);
	mSmallStoneFont = new Font(FNT_SMALLSTONE);
	mCopperPlateFont = new Font(FNT_COPPERPLATE);
	mController = new Controller();
	mGameBackground = new Background(IMG_PRIMARY_BACKGROUND, IMG_PARALLAX_BACKGROUND, -30, 0, -60, 0);
	mGameLogo = new GameLogo(IMG_GAME_LOGO, -200, 0);
	mDropDownMenu = new DropDownMenu(IMG_DROP_DOWN_MENU, 200, RETRACTED);
	mUpDownButtons = new Drawable(IMG_UP_DOWN_BUTTONS);
	mCrossButton = new Drawable(IMG_CROSS_BUTTON);
	mCrossButton_small = new Drawable(IMG_CROSS_BUTTON_SMALL);
	mCircleButton = new Drawable(IMG_CIRCLE_BUTTON);
	mSquareButton_small = new Drawable(IMG_SQUARE_BUTTON_SMALL);
	mPlayer = new Player(
					IMG_PLAYER_SHIP,
					IMG_PLAYER_SHIP_EXPLOSION,
					PLAYER_SHIP_FRAME_WIDTH_SIZE,
					PLAYER_SHIP_FRAME_HEIGHT_SIZE,
					PLAYER_SHIP_FRAMERATE);
	mMoonRock = new AnimatedSprite(
						IMG_MOON_ROCK,
						MOON_ROCK_FRAME_WIDTH_SIZE,
						MOON_ROCK_FRAME_HEIGHT_SIZE,
						MOON_ROCK_FRAMERATE);
	mAsteroidL = new AnimatedSprite(
						IMG_ASTEROID_L,
						ASTEROID_L_FRAME_WIDTH_SIZE,
						ASTEROID_L_FRAME_HEIGHT_SIZE,
						ASTEROID_L_FRAMERATE);
	mAsteroidM = new AnimatedSprite(
						IMG_ASTEROID_M,
						ASTEROID_M_FRAME_WIDTH_SIZE,
						ASTEROID_M_FRAME_HEIGHT_SIZE,
						ASTEROID_M_FRAMERATE);
	mAsteroidS = new AnimatedSprite(
						IMG_ASTEROID_S,
						ASTEROID_S_FRAME_WIDTH_SIZE,
						ASTEROID_S_FRAME_HEIGHT_SIZE,
						ASTEROID_S_FRAMERATE);
	mEnemyList = new EnemyList();
	mSkillsSystem = new SkillsSystem();
	mSaveLoad = new SaveLoad();
	mSaveLoad->LoadSaveGame();
}

void Resources::AssertResources()
{
	oslAssert(mParafontFont != NULL);
	oslAssert(mSmallStoneFont != NULL);
	oslAssert(mCopperPlateFont != NULL);
	oslAssert(mController != NULL);
	oslAssert(mGameBackground != NULL);
	oslAssert(mGameLogo != NULL);
	oslAssert(mDropDownMenu != NULL);
	oslAssert(mUpDownButtons != NULL);
	oslAssert(mCrossButton != NULL);
	oslAssert(mPlayer != NULL);
	oslAssert(mMoonRock != NULL);
	oslAssert(mAsteroidL != NULL);
	oslAssert(mAsteroidM != NULL);
	oslAssert(mAsteroidS != NULL);
	oslAssert(mEnemyList != NULL);
	oslAssert(mSkillsSystem != NULL);
}
