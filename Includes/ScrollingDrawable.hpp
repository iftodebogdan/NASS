/*
 * ScrollDrawable.hpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef SCROLLDRAWABLE_H_
#define SCROLLDRAWABLE_H_

#include "Drawable.hpp"

class ScrollingDrawable : public Drawable
{
public:
	ScrollingDrawable(string pathToImgFile);	//creates a tiling scrolling image using the given image file in png format
	ScrollingDrawable(	//creates a tiling scrolling image
			string pathToImgFile,	//an image file in png format
			int scrollSpeedX,	//the scroll speed on the Ox axis in pixels/second
			int scrollSpeedY);	//the scroll speed on the Oy axis in pixels/second

	void SetScrollSpeed(int scrollSpeedX, int scrollSpeedY);	//sets the scroll speed of the image on the Ox and Oy axis
	void SetScrollSpeedX(int scrollSpeedX);	//sets the scroll speed of the image on the Ox axis in pixels/second
	void SetScrollSpeedY(int scrollSpeedY);	//sets the scroll speed of the image on the Oy axis in pixels/second
	int GetScrollSpeedX();	//returns the scroll speed on the Ox axis in pixels/second
	int GetScrollSpeedY();	//returns the scroll speed on the Oy axis in pixels/second

	void Reset(); //resets the animation of the scrolling image

	void Render();	//renders the scrolling image

private:
	int mScrollSpeedX;
	int mScrollSpeedY;
	float mPixelsToScrollX;
	float mPixelsToScrollY;
};

#endif /* SCROLLDRAWABLE_H_ */
