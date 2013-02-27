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
	Drawable(string pathToImgFile);
	~Drawable();

	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();

	void SetPositionX(int coordX);
	void SetPositionY(int coordY);
	void SetPositionXY(int coordX, int coordY);

	void MoveX(int offsetX);
	void MoveY(int offsetY);
	void MoveXY(int offsetX, int offsetY);

	void Draw();
	void Draw(int coordX, int coordY);

protected:
	OSL_IMAGE *mDrawableImg;
};

#endif /* DRAWABLE_H_ */

