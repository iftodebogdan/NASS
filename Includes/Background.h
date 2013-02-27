/*
 * Background.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "ScrollDrawable.h"

class Background
{
public:
	Background(string pathToPrimaryBgImgFile);
	Background(string pathToPrimaryBgImgFile, string pathToParallaxBgImgFile);
	Background(
			string pathToPrimaryBgImgFile,
			string pathToParallaxBgImgFile,
			int primaryBgScrollSpeedX,
			int primaryBgScrollSpeedY,
			int parallaxBgScrollSpeedX,
			int parallaxBgScrollSpeedY);
	~Background();

	void SetBackgroundScrollSpeed(
				int primaryBgScrollSpeedX,
				int primaryBgScrollSpeedY,
				int parallaxBgScrollSpeedX,
				int parallaxBgScrollSpeedY);
	int GetPrimaryBackgroundScrollSpeedX();
	int GetPrimaryBackgroundScrollSpeedY();
	int GetParallaxBackgroundScrollSpeedX();
	int GetParallaxBackgroundScrollSpeedY();

	void ShowParallaxBackground(bool isShown);
	bool IsParallaxBackgroundShown();
	void ResetBackground();
	void Render();

private:
	ScrollDrawable* mPrimaryBackground;
	ScrollDrawable* mParallaxBackground;

	bool mParallaxBgIsShown;
};

#endif /* BACKGROUND_H_ */
