/*
 * Drawable.cpp
 *
 *  Created on: Feb 26, 2013
 *      Author: Bogdan
 */

#include "../Includes/Drawable.h"

Drawable::Drawable(string pathToFile)
{
	mDrawableImg = oslLoadImageFilePNG(
						(char*)pathToFile.c_str(),
						OSL_IN_RAM | OSL_SWIZZLED,
						OSL_PF_8888);
	oslAssert(mDrawableImg != NULL);

	mImgWidth = mDrawableImg->x;
	mImgHeight = mDrawableImg->y;

	mPosX = 0;
	mPosY = 0;
}

Drawable::~Drawable()
{
	if(mDrawableImg != NULL)
		oslDeleteImage(mDrawableImg);
}

int Drawable::GetPositionX()
{
	return mPosX;
}

int Drawable::GetPositionY()
{
	return mPosY;
}

int Drawable::GetWidth()
{
	return mImgWidth;
}

int Drawable::GetHeight()
{
	return mImgHeight;
}

void Drawable::SetPositionX(int coordX)
{
	mPosX = coordX;
}

void Drawable::SetPositionY(int coordY)
{
	mPosY = coordY;
}

void Drawable::SetPositionXY(int coordX, int coordY)
{
	mPosX = coordX;
	mPosY = coordY;
}

void Drawable::MoveX(int offsetX)
{
	mPosX += offsetX;
}

void Drawable::MoveY(int offsetY)
{
	mPosY += offsetY;
}

void Drawable::MoveXY(int offsetX, int offsetY)
{
	mPosX += offsetX;
	mPosY += offsetY;
}

void Drawable::Draw()
{
	oslDrawImageXY(mDrawableImg, mPosX, mPosY);
}
