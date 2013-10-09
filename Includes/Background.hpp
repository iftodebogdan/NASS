/*
 * Background.hpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Bogdan
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "ScrollingDrawable.hpp"

class Background
{
public:
	Background(string pathToPrimaryBgImgFile); 	//creates a single-layered background with no scrolling effect

	Background(string pathToPrimaryBgImgFile,
			   string pathToParallaxBgImgFile); //creates a double-layered background with no scrolling effect

	Background(									//creates a double-layered background with scrolling effect
			string pathToPrimaryBgImgFile,		//an image file in png format for the bottom layer
			string pathToParallaxBgImgFile,		//an image file in png format for the top layer
			int primaryBgScrollSpeedX,			//the bottom layer's scroll speed on the Ox axis in pixels/second
			int primaryBgScrollSpeedY,			//the bottom layer's scroll speed on the Oy axis in pixels/second
			int parallaxBgScrollSpeedX,			//the top layer's scroll speed on the Ox axis in pixels/second
			int parallaxBgScrollSpeedY);		//the top layer's scroll speed on the Oy axis in pixels/second

	~Background();								//destroys the background

	void SetBackgroundScrollSpeed(				//sets the background scroll speed
				int primaryBgScrollSpeedX,		//the bottom layer's scroll speed on the Ox axis in pixels/second
				int primaryBgScrollSpeedY,		//the bottom layer's scroll speed on the Oy axis in pixels/second
				int parallaxBgScrollSpeedX,		//the top layer's scroll speed on the Ox axis in pixels/second
				int parallaxBgScrollSpeedY);	//the top layer's scroll speed on the Oy axis in pixels/second

	int GetPrimaryBackgroundScrollSpeedX();		//returns the bottom layer's scroll speed on the Ox axis in pixels/second
	int GetPrimaryBackgroundScrollSpeedY();		//returns the bottom layer's scroll speed on the Oy axis in pixels/second
	int GetParallaxBackgroundScrollSpeedX();	//returns the top layer's scroll speed on the Ox axis in pixels/second
	int GetParallaxBackgroundScrollSpeedY();	//returns the top layer's scroll speed on the Oy axis in pixels/second

	void ShowParallaxBackground(bool isShown);	//sets whether the top layer is visible
	bool IsParallaxBackgroundShown();			//returns true or false in accordance to the visibility of the top layer
	void ResetBackground();						//resets the background
	void Render();								//renders the background

private:
	void RenderBackground(ScrollingDrawable* background);

	ScrollingDrawable* mPrimaryBackground;
	ScrollingDrawable* mParallaxBackground;

	bool mParallaxBgIsShown;
};

#endif /* BACKGROUND_H_ */
