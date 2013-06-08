/*
 * FileIO.h
 *
 *  Created on: Jun 9, 2013
 *      Author: Bogdan
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include <string>
#include <fstream>
using namespace std;

class BinaryFileIO
{
public:
	BinaryFileIO(string pathToFile);
	~BinaryFileIO();

	bool Write(const void* data, size_t size);
	bool Read(void* data, size_t size);
	bool IsFileOpen();

private:
	FILE* mFile;
};

#endif /* FILEIO_H_ */
