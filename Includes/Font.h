/*
 * Font.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef FONT_H_
#define FONT_H_

#include <oslib/oslib.h>
#include <string>
using namespace std;

class Font
{
public:
	static OSL_SFONT* mFont;

	static void LoadFont(string fontFile);
	static void DrawText(string text, int posX, int posY);
	static void DrawTextCentered(string text, int posX, int posY);
	static int GetTextWidth(string text);
};

#endif /* FONT_H_ */
