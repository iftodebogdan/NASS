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

#define COLOR_RED RGB(255, 0, 0)
#define COLOR_BLUE RGB(0, 0, 255)
#define COLOR_GREEN RGB(0, 255, 0)
#define COLOR_WHITE RGB(255, 255, 255)
#define COLOR_BLACK RGB(0, 0, 0)

class Font
{
public:
	Font(string fontFile);
	~Font();

	void LoadFont(string fontFile);
	void DrawText(string text, int posX, int posY);
	void DrawTextCentered(string text, int posX, int posY);
	int GetTextWidth(string text);

	OSL_SFONT* mFont;
};

#endif /* FONT_H_ */
