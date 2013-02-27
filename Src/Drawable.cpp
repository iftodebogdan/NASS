/*
 * Drawable.cpp
 *
 *  Created on: Feb 26, 2013
 *      Author: Bogdan
 */

#include "../Includes/Drawable.h"

Drawable::Drawable(string pathToImgFile)
{
	mDrawableImg = oslLoadImageFilePNG(
						(char*)pathToImgFile.c_str(),
						OSL_IN_RAM | OSL_SWIZZLED,
						OSL_PF_8888);
	oslAssert(mDrawableImg != NULL);

	mDrawableImg->x = 0;
	mDrawableImg->y = 0;
}

Drawable::~Drawable()
{
	if(mDrawableImg != NULL)
		oslDeleteImage(mDrawableImg);
}

int Drawable::GetPositionX()
{
	return mDrawableImg->x;
}

int Drawable::GetPositionY()
{
	return mDrawableImg->y;
}

int Drawable::GetWidth()
{
	return mDrawableImg->sizeX;
}

int Drawable::GetHeight()
{
	return mDrawableImg->sizeY;
}

void Drawable::SetPositionX(int coordX)
{
	mDrawableImg->x = coordX;
}

void Drawable::SetPositionY(int coordY)
{
	mDrawableImg->y = coordY;
}

void Drawable::SetPositionXY(int coordX, int coordY)
{
	mDrawableImg->x = coordX;
	mDrawableImg->y = coordY;
}

void Drawable::MoveX(int offsetX)
{
	mDrawableImg->x += offsetX;
}

void Drawable::MoveY(int offsetY)
{
	mDrawableImg->y += offsetY;
}

void Drawable::MoveXY(int offsetX, int offsetY)
{
	mDrawableImg->x += offsetX;
	mDrawableImg->y += offsetY;
}

void Drawable::Draw()
{
	oslDrawImage(mDrawableImg);
}

void Drawable::Draw(int coordX, int coordY)
{
	SetPositionXY(coordX, coordY);
	Draw();
}
