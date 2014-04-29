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
#include "AssetTypes.hpp"
#include <functional>
#include <iosfwd>

namespace Forge {

class AssetManager;

class FORGE_EXPORT LoaderInterface
{
  public:
    typedef LoaderInterface* (*CreateFn)();
    static constexpr char const* LoaderCreateInterfaceName = "createInterface";

    virtual char const* extensions() const = 0;

    virtual Asset type() const = 0;

    virtual void* load(std::string const& filename) = 0;

    virtual std::function<void(void*)> getDeleter() = 0;
};

}

typedef Forge::LoaderInterface* (*LoaderCreateInterfaceFn)();

/* Interface function for loading plugin */
extern "C"
{

// Adds the loader to an asset manager
FORGE_EXPORT Forge::LoaderInterface* createInterface();

}
