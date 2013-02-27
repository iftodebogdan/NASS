/*
 * Game.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#include "../Includes/Game.h"

Game::Game()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	oslSetTransparentColor(RGB(255,0,255));
	oslSetQuitOnLoadFailure(1);
	oslSetKeyAutorepeatInit(40);
	oslSetKeyAutorepeatInterval(10);
}

Game::~Game()
{
	oslEndGfx();
	oslQuit();
}

void Game::Run()
{
	oslShowSplashScreen(1);

	AnimatedSprite* AnimSpr = new AnimatedSprite("Res/spritesheet.png", 68, 64, 15);
	Background* BgImg = new Background(
								"Res/PrimaryBackground.png",
								"Res/ParallaxBackground.png",
								-60, 0, -90, 0);

	while (!osl_quit)
	{
		oslStartDrawing();
		oslCls();

		BgImg->Render();
		AnimSpr->Render();

		oslEndDrawing();
		oslSyncFrame();
		//oslSwapBuffers();
	}
}
