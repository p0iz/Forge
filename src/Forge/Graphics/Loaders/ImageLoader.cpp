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

#include "Util/Log.h"

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include "FreeImage.h"

namespace Forge { namespace ImageLoader {

unsigned int loadAsTexture(const char* imageFile)
{
	unsigned int textureId = 0;

	// Load image data
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFile);
	FIBITMAP* bitmap = FreeImage_Load(format, imageFile);
	if (bitmap)
	{
		bitmap = FreeImage_ConvertTo32Bits(bitmap);
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RGBA,
					FreeImage_GetWidth(bitmap),
					FreeImage_GetHeight(bitmap),
					0,
					GL_BGRA,
					GL_UNSIGNED_BYTE,
					bitmap->data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		FreeImage_Unload(bitmap);
	}
	else
	{
		const char* formatStr = FreeImage_GetFormatFromFIF(format);
		Log::LogStream& stream = Log::error << "Failed to read file '" << imageFile << "'";
		if (formatStr) {
			stream << " of type " << formatStr << '\n';
		} else {
			stream << '\n';
		}
	}
	return textureId;
}

}}
