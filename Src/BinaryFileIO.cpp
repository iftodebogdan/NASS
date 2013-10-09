/*
 * FileIO.cpp
 *
 *  Created on: Jun 9, 2013
 *      Author: Bogdan
 */

#include "../Includes/Resources.hpp"
#include "../Includes/BinaryFileIO.hpp"

BinaryFileIO::BinaryFileIO(string pathToFile)
{
	mFile = NULL;
	mFile = fopen(pathToFile.c_str(), "rb+");
}

BinaryFileIO::~BinaryFileIO()
{
	if(mFile != NULL)
		fclose(mFile);
}

bool BinaryFileIO::Write(const void* data, size_t size)
{
	if(mFile != NULL)
		if(fwrite(data, size, 1, mFile) == 1)
			return true;

	return false;
}

bool BinaryFileIO::Read(void* data, size_t size)
{
	if(mFile != NULL)
		if(fread(data, size, 1, mFile))
			return true;

	return false;
}

bool BinaryFileIO::IsFileOpen()
{
	if(mFile != NULL)
		return true;
	else
		return false;
}
