/*
 * Font.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/Font.h"

OSL_SFONT* Font::mFont = NULL;

void Font::LoadFont(string fontFile)
{
	mFont = oslLoadSFontFile((char*)fontFile.c_str(), OSL_PF_8888);
	oslAssert(mFont != NULL);
}

void Font::DrawText(string text, int posX, int posY)
{
	oslAssert(mFont != NULL);
	oslSFontDrawText(mFont, posX, posY, (char*)text.c_str());
}

void Font::DrawTextCentered(string text, int posX, int posY)
{
	oslAssert(mFont != NULL);
	DrawText(text, posX - GetTextWidth(text) / 2, posY);
}

int Font::GetTextWidth(string text)
{
	return oslGetSFontTextWidth(mFont, (char*)text.c_str());
}
