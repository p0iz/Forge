/* This file is part of Forge.
 *
 * Forge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Forge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with Forge.  If not, see
 * <http://www.gnu.org/licenses/>. 
 * 
 * Copyright 2012 Tommi Martela
 *
 */

#include "ImageLoader.h"

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

unsigned int ImageLoader::loadBmp(const char* imageFile)
{
	FILE* file = fopen(imageFile, "rb");
	if (!file)
	{
		std::cerr << "Could not load image: " << imageFile << "\n";
		return 0;
	}

	unsigned char header[54];

	if (fread(header, 1, 54, file) != 54)
	{
		// If not 54 bytes read : problem
		std::cerr << "Not a correct BMP file. :(\n";
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cerr << "Not a correct BMP file. :(\n";
		return 0;
	}

	GLenum pixelMode = GL_BGR;
	int pixelSize = 3;
	switch (*(int*)&header[0x1C])
	{
	case 24:
		pixelMode = GL_BGR; // no alpha
		pixelSize = 3;
		break;
	case 32:
		pixelMode = GL_BGRA; // alpha
		pixelSize = 4;
	}

	unsigned int dataStartPos(*(int*)&(header[0x0A]));
	unsigned int imageSize(*(int*)&(header[0x22]));
	unsigned int width(*(int*)&(header[0x12]));
	unsigned int height(*(int*)&(header[0x16]));

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*pixelSize; // 4 : one byte for each Red, Green, Blue and Alpha component
	if (dataStartPos==0)      dataStartPos=54; // The BMP header is done that way

	// Create a buffer
	std::vector<GLubyte> imageData(imageSize);

	// Read the actual data from the file into the buffer
	for (unsigned int i=0; i < imageSize ; ++i)
		fread(&imageData[i],1,1,file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	GLuint textureId(0);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixelMode, GL_UNSIGNED_BYTE, &imageData[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureId;
}
