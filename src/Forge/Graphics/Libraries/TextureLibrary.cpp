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

#include "TextureLibrary.hpp"

#include "Util/Log.h"

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "FreeImage.h"

namespace Forge { namespace Graphics {

TextureLibrary::TextureLibrary():
  mLoadedTextures()
{
}

TextureLibrary::~TextureLibrary()
{
  // Delete any textures left in the library
  for (auto handle : mLoadedTextures)
  {
    glDeleteTextures(1, &handle.second.handle);
  }
}

TextureHandle const& TextureLibrary::loadTexture(const std::string& imageFile)
{
  TextureHandle texHandle;

  if (mLoadedTextures.count(imageFile) > 0)
  {
    ++mLoadedTextures[imageFile].count;
    return mLoadedTextures[imageFile];
  }

  // Load image data
  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFile.c_str());
  FIBITMAP* bitmap = FreeImage_Load(format, imageFile.c_str());
  if (bitmap)
  {
    bitmap = FreeImage_ConvertTo32Bits(bitmap);
    glGenTextures(1, &texHandle.handle);
    glBindTexture(GL_TEXTURE_2D, texHandle.handle);
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

    texHandle.name = imageFile;
    texHandle.count = 1;
    mLoadedTextures[imageFile] = texHandle;
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
  return mLoadedTextures[imageFile];
}

void TextureLibrary::unloadTexture(TextureHandle const& texture)
{
  TextureHandle& texHandle = mLoadedTextures[texture.name];
  if (texHandle.count > 0)
  {
    --texHandle.count;
  }
  else
  {
    mLoadedTextures.erase(texture.name);
  }
}

}}
