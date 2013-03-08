/*
 * Drawable.h
 *
 *  Created on: Feb 26, 2013
 *      Author: Bogdan
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <oslib/oslib.h>
#include <string>
using namespace std;

class Drawable {
public:
	Drawable(string pathToImgFile);	//creates a drawable using an image file in png format
	Drawable(const Drawable *drawableImg);
	~Drawable();	//destroys a drawable

	int GetPositionX();	//returns the position of the image on the Ox axis
	int GetPositionY();	//returns the position of the image on the Oy axis
	int GetWidth();	//returns the width of the image
	int GetHeight();	//returns the height of the image

	void SetPositionX(int coordX);	//sets the position of the image on the Ox axis
	void SetPositionY(int coordY);	//sets the position of the image on the Oy axis
	void SetPositionXY(int coordX, int coordY);	//sets the position of the image on screen

	void MoveX(int offsetX);	//moves the image on the Ox axis by the given number of pixels
	void MoveY(int offsetY);	//moves the image on the Oy axis by the given number of pixels
	void MoveXY(int offsetX, int offsetY);	//moves the image on screen by the given number of pixels

	void Draw();	//draws the image
	void Draw(int coordX, int coordY);	//draws the image at the given coordinates

protected:
	OSL_IMAGE *mDrawableImg;
};

#endif /* DRAWABLE_H_ */

