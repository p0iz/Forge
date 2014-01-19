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

#pragma once

#include "ForgeExport.h"
#include <iosfwd>

namespace Forge {

class LoaderInterface
{
  public:
    virtual ~LoaderInterface() { }

    virtual void* load(std::string const& filename) = 0;

    virtual void unload(void* asset) = 0;

    virtual char const* category() const = 0;
};

}

typedef Forge::LoaderInterface* (*LoaderCreateFn)();

typedef char const* (*LoaderInfoFn)();

/* Library interface definition */
extern "C"
{
  FORGE_EXPORT Forge::LoaderInterface* createInterface();

  FORGE_EXPORT const char* supportedExtensions();
}
