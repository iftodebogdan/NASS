/*
 * Background.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "Drawable.h"

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

	void SetBackgroundScrollSpeed(
				int primaryBgScrollSpeedX,
				int primaryBgScrollSpeedY,
				int parallaxBgScrollSpeedX,
				int parallaxBgScrollSpeedY);
	void ShowParallaxBackground(bool isShown);
	bool IsParallaxBackgroundShown();
	void ResetBackground();
	void Render();

private:
	void RenderBackground(
				Drawable* backgroundImg,
				int bgScrollSpeedX,
				int bgScrollSpeedY,
				float &bgPixelsToScrollX,
				float &bgPixelsToScrollsY);

	Drawable* mPrimaryBackground;
	Drawable* mParallaxBackground;

	int mPrimaryBgScrollSpeedX;
	int mPrimaryBgScrollSpeedY;
	float mPrimaryBgPixelsToScrollX;
	float mPrimaryBgPixelsToScrollY;

	int mParallaxBgScrollSpeedX;
	int mParallaxBgScrollSpeedY;
	float mParallaxBgPixelsToScrollX;
	float mParallaxBgPixelsToScrollY;
	bool mParallaxBgIsShown;
};

#endif /* BACKGROUND_H_ */
