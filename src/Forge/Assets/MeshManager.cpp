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

#include "MeshManager.hpp"
#include "Platform/DynamicLoader/DynamicLoader.hpp"
#include "Platform/FileSystem/Directory.hpp"
#include "Platform/FileSystem/File.hpp"
#include "Util/Log.h"


namespace Forge {

MeshManager::MeshManager(std::string const& searchPath):
  AssetManager(searchPath)
{
}

AssetHandle MeshManager::load(const std::string& file)
{
}

bool MeshManager::registerLoader(const std::string& lib)
{
  DynamicLoader dllLoader(getSearchPath());
  DynamicLibrary* loaderLib = dllLoader.open(lib);

  if (!loaderLib || !loaderLib->isValid())
  {
    Log::error << "Failed to load plugin '" << loader << "'\n";
    return false;
  }

  LoaderCreateFn createInterface = loaderLib->loadSymbol<LoaderCreateFn>("initialize");
  LoaderInfoFn supportedExtensions = loaderLib->loadSymbol<LoaderInfoFn>("supportedExtensions");
  if (createInterface && supportedExtensions)
  {
    // Check that we actually support some extensions
    std::string extensions = supportedExtensions();
    if (extensions.length() == 0)
    {
      delete loaderLib;
      return false;
    }

    LoaderInterface<StaticMesh>* loaderInterface = createInterface();
    Log::info << "Loaded loader plugin '" << loader << "' [" << loaderInterface << "]\n"
                 "* Supported extensions: " << extensions << "\n";

    // Store a reference to the same loader for all the supported extensions
    int count = 0;
    std::string::size_type extStart = 0;
    std::string::size_type extEnd;
    do
    {
      extEnd = extensions.find_first_of(",;", extStart);
      std::string extension = extensions.substr(extStart, extEnd - extStart);
      extStart = extEnd + 1;

      lua_setfield(state, -2, extension.c_str());
      lua_getfield(state, -1, extension.c_str());

      ++count;
    }
    while (extEnd != std::string::npos);

    return true;
  }
  else
  {
    Log::error << "Error loading loader symbols from plugin '" << loader << "'\n";
    return false;
  }
}

}
