/*
 * TitleScreen.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/TitleScreen.h"

TitleScreen::TitleScreen()
{
	mGameLogo = new GameLogo(Resources::IMG_GAME_LOGO, -200, 0);
	mDropDownMenu = new DropDownMenu(Resources::IMG_DROP_DOWN_MENU);
}

TitleScreen::~TitleScreen()
{
	delete mGameLogo;
}

void TitleScreen::Render()
{
	mGameLogo->Render();
	mDropDownMenu->Render();
	if(mDropDownMenu->GetState() != EXTENDED && mDropDownMenu->GetState() != EXTENDING)
		mDropDownMenu->SetState(EXTENDING);
}
