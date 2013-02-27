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
	//Show our splash screen
	oslShowSplashScreen(1);

	Drawable* Image = new Drawable("res/spritesheet.png");
	//main loop
		while (!osl_quit)
		{
			//allow to draw
			oslStartDrawing();

			Image->Draw();

			//end of the draw
			oslEndDrawing();

			//Synchronize the screen
			oslSyncFrame();
		}

	//Wait a keystroke
	oslWaitKey();
}
