/*
 * Font.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#include "../Includes/Font.h"

Font::Font(string fontFile)
{
	LoadFont(fontFile);
}

Font::~Font()
{
	oslDeleteSFont(mFont);
}

void Font::LoadFont(string fontFile)
{
	mFont = oslLoadSFontFile((char*)fontFile.c_str(), OSL_PF_8888);
	oslAssert(mFont != NULL);
}

void Font::DrawText(string text, int posX, int posY)
{
	oslSFontDrawText(mFont, posX, posY, (char*)text.c_str());
}

void Font::DrawTextCentered(string text, int posX, int posY)
{
	DrawText(text, posX - GetTextWidth(text) / 2, posY);
}

int Font::GetTextWidth(string text)
{
	return oslGetSFontTextWidth(mFont, (char*)text.c_str());
}
