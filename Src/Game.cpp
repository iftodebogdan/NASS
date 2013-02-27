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

	AnimatedSprite* Image = new AnimatedSprite("res/spritesheet.png", 32, 32, 6);

	while (!osl_quit)
	{
		oslStartDrawing();
		oslClearScreen(RGB(0,0,0));
		Image->Render();
		oslSwapBuffers();
		oslEndDrawing();
		oslSyncFrame();
	}
}
