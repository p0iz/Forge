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

#pragma once

#include "../../Util/Singleton.hpp"
#include <string>
#include <unordered_map>


/* Image file library. Return OpenGL names for the allocated resources. */
namespace Forge { namespace Graphics {

/* Used to access a texture */
struct TextureHandle
{
  TextureHandle():
    name(""),
    count(0),
    handle(0)
  {
  }

  std::string name;
  unsigned int count;
  unsigned int handle;
};

class TextureLibrary : public Singleton<TextureLibrary> {
  public:
    TextureLibrary();
    virtual ~TextureLibrary();

    TextureHandle const& loadTexture(std::string const& imageFile);
    void unloadTexture(TextureHandle const& texture);

  private:
    std::unordered_map<std::string, TextureHandle> mLoadedTextures;
};

}}
