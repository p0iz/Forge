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
#include "FreeImage.h"
#include <string>


namespace Forge {

void* ImageLoader::load(const std::string& filename)
{
  // Load image data
  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str());
  FIBITMAP* bitmap = FreeImage_Load(format, filename.c_str());
  if (bitmap)
  {
    bitmap = FreeImage_ConvertTo32Bits(bitmap);
  }
  return bitmap;
}

void ImageLoader::unload(void* asset)
{
  FreeImage_Unload(static_cast<FIBITMAP*>(asset));
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
