/*
 * Drawable.cpp
 *
 *  Created on: Feb 26, 2013
 *      Author: Bogdan
 */

#include "../Includes/Drawable.hpp"

Drawable::Drawable(string pathToImgFile)
{
	mDrawableImg = oslLoadImageFilePNG(
						(char*)pathToImgFile.c_str(),
						OSL_IN_RAM | OSL_SWIZZLED,
						OSL_PF_8888);
	oslAssert(mDrawableImg != NULL);

	SetPositionXY(0, 0);
}

Drawable::Drawable(const Drawable *drawableImg)
{
	mDrawableImg = new OSL_IMAGE(*drawableImg->mDrawableImg);
}

Drawable::~Drawable()
{
	delete mDrawableImg;

	//if(mDrawableImg != NULL)
		//oslDeleteImage(mDrawableImg);
		//^ this is breaking something in the memory resulting in a freeze
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

unsigned Drawable::GetPixel(int coordX, int coordY)
{
	if(coordX >= GetWidth() || coordY >= GetHeight())
		return 0;

	return oslGetImagePixel(mDrawableImg, coordX, coordY);
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
	SetPositionX(coordX);
	SetPositionY(coordY);
}

void Drawable::MoveX(int offsetX)
{
	SetPositionX(GetPositionX() + offsetX);
}

void Drawable::MoveY(int offsetY)
{
	SetPositionY(GetPositionY() + offsetY);
}

void Drawable::MoveXY(int offsetX, int offsetY)
{
	SetPositionXY(GetPositionX() + offsetX, GetPositionY() + offsetY);
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
