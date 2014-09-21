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

#include "SDL2/SDL_image.h"

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
  SDL_Surface* surface = IMG_Load(imageFile.c_str());
  SDL_Surface* rgbaSurface = SDL_CreateRGBSurface(NULL, surface->w, surface->h, 24, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
  if (surface && rgbaSurface)
  {
    SDL_BlitSurface(surface, 0, rgbaSurface, 0);
    glGenTextures(1, &texHandle.handle);
    glBindTexture(GL_TEXTURE_2D, texHandle.handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RGBA,
      rgbaSurface->w,
      rgbaSurface->h,
      0,
      GL_BGRA,
      GL_UNSIGNED_BYTE,
      rgbaSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    texHandle.name = imageFile;
    texHandle.count = 1;
    mLoadedTextures[imageFile] = texHandle;
  }
  else
  {
    Log::LogStream& stream = Log::error << "Failed to read file '" << imageFile << "'\n";
  }
  SDL_FreeSurface(surface);
  SDL_FreeSurface(rgbaSurface);
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
