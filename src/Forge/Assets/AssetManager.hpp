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
 * Copyright 2014 Tommi Martela
 *
 */

#pragma once

#include "ForgeExport.h"
#include "AssetHandle.hpp"
#include <memory>
#include <unordered_map>


namespace Forge {

class DynamicLibrary;

class LoaderInterface;

class FORGE_EXPORT AssetManager
{
  public:
    AssetManager(std::string const& searchPath);
    ~AssetManager();

    AssetHandle load(std::string const& file);

    std::shared_ptr<void> get(AssetHandle const& handle);

    void unload(std::string const& file);

    bool registerLoader(std::string const& lib);

    std::string const searchPath() const;

  private:
    // DLL search path
    std::string mSearchPath;

    std::vector<std::shared_ptr<DynamicLibrary>> mLoadedPlugins;
    std::unordered_map<std::string, std::shared_ptr<LoaderInterface>> mLoaders;
    std::unordered_map<AssetHandle, std::shared_ptr<void>> mLoadedAssets;
};

}
