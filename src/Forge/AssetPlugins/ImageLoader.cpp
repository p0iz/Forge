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
 * Copyright 2013 Tommi Martela
 *
 */

#include "ImageLoader.hpp"
#include <string>
#include <SDL2/SDL_image.h>


namespace Forge {

void* ImageLoader::load(const std::string& filename)
{
  // Load image data
  SDL_Surface* surface = IMG_Load(filename.c_str());
  SDL_Surface* bitmap = SDL_CreateRGBSurface(NULL, surface->w, surface->h, 24, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
  if (surface && bitmap)
  {
    SDL_BlitSurface(surface, 0, bitmap, 0);
  }
  SDL_FreeSurface(surface);
  return bitmap;
}

void ImageLoader::unload(void* asset)
{
  SDL_FreeSurface(static_cast<SDL_Surface*>(asset));
}

const char*ImageLoader::category() const
{
  return "images";
}

}

/* Library interface definition */
Forge::LoaderInterface* createInterface()
{
  return new Forge::ImageLoader;
}

const char* supportedExtensions()
{
  return "bmp,dds,exr,gif,hdr,ico,iff,jbig,jng,jpeg,jpg,mng,pcx,pbm,pgm,ppm,pfm,png,pict,psd,raw,ras,sgi,tga,tiff,wbmp,xbm,xpm";
}

const char* category()
{
  return "images";
}
