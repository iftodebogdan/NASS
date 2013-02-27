/*
 * ScrollDrawable.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Bogdan
 */

#ifndef SCROLLDRAWABLE_H_
#define SCROLLDRAWABLE_H_

#include "Drawable.h"
#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272

class ScrollDrawable : public Drawable
{
public:
	ScrollDrawable(string pathToImgFile);
	ScrollDrawable(
			string pathToImgFile,
			int scrollSpeedX,
			int scrollSpeedY);

	void SetScrollSpeed(int scrollSpeedX, int scrollSpeedY);
	int GetScrollSpeedX();
	int GetScrollSpeedY();

	void Reset();
	void Render();

private:
	int mScrollSpeedX;
	int mScrollSpeedY;
	float mPixelsToScrollX;
	float mPixelsToScrollY;
};

#endif /* SCROLLDRAWABLE_H_ */
