/*
 * Font.hpp
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
	Font(string fontFile);
	~Font();

	void LoadFont(string fontFile);
	void DrawText(string text, int posX, int posY);
	void DrawTextCentered(string text, int posY);
	void DrawTextAlignedRight(string text, int posY);
	int GetTextWidth(string text);

private:
	OSL_SFONT* mFont;
};

#endif /* FONT_H_ */
