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
	ScrollDrawable(
				string pathToImgFile,
				int scrollSpeedX,
				int scrollSpeedY,
				bool isTileable);

	void SetScrollSpeed(int scrollSpeedX, int scrollSpeedY);
	void SetScrollSpeedX(int scrollSpeedX);
	void SetScrollSpeedY(int scrollSpeedY);
	int GetScrollSpeedX();
	int GetScrollSpeedY();

	bool IsTileable();
	void SetTileable(bool isTileable);
	void Reset();

	void Render();

private:
	bool mIsTileable;
	int mScrollSpeedX;
	int mScrollSpeedY;
	float mPixelsToScrollX;
	float mPixelsToScrollY;
};

#endif /* SCROLLDRAWABLE_H_ */
