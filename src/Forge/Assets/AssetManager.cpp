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

#include "AssetManager.hpp"
#include "LoaderInterface.hpp"
#include "Platform/DynamicLoader/DynamicLoader.hpp"
#include "Platform/FileSystem/Directory.hpp"
#include "Platform/FileSystem/File.hpp"
#include "Util/Log.h"
#include <memory>


namespace Forge {

AssetManager::AssetManager(std::string const& searchPath):
  mSearchPath(searchPath)
{
  // Register all found plugins
  FileSystem::Directory pluginDir(searchPath);
  for (std::string const& file : pluginDir.listFiles())
  {
    registerLoader(file);
  }
}

AssetManager::~AssetManager()
{
}

AssetHandle Forge::AssetManager::load(const std::string& file)
{
  AssetHandle handle = AssetHandle::create();
  std::size_t start = file.find_last_of('.');
  if (start == std::string::npos)
  {
    Log::error << "No extension, cannot load file '" << file << "'.\n";
    handle.id = AssetHandle::InvalidId;
  }
  else
  {
    std::string ext = file.substr(start+1);
    if (mLoaders.count(ext) > 0)
    {
      std::shared_ptr<void> data(mLoaders.at(ext)->load(file), mLoaders[ext]->getDeleter());
      mLoadedAssets[handle] = data;
      Log::info << "Loaded asset '" << file << "'\n";
    }
    else
    {
      Log::error << "No loader available for file of type '" << ext << "'\n";
    }
  }
  return handle;
}

std::shared_ptr<void> AssetManager::get(const Forge::AssetHandle& handle)
{
  return mLoadedAssets.count(handle) == 0 ? std::shared_ptr<void>() : mLoadedAssets.at(handle);
}

bool AssetManager::registerLoader(const std::string& lib)
{
  DynamicLoader dllLoader(mSearchPath);
  std::shared_ptr<DynamicLibrary> loaderLib(dllLoader.open(lib));

  if (!loaderLib || !loaderLib->isValid())
  {
    return false;
  }

  LoaderInterface::CreateFn createInterface =
      loaderLib->loadSymbol<LoaderInterface::CreateFn>(LoaderInterface::LoaderCreateInterfaceName);

  if (createInterface)
  {
    std::shared_ptr<LoaderInterface> loader(createInterface());

    if (!loader)
    {
      Log::error << "Plugin failed to create loader.\n";
      return false;
    }

    mLoadedPlugins.push_back(loaderLib);

    // Check that we actually support some extensions
    std::string extensions = loader->extensions();

    Log::info << "Loaded loader plugin '" << lib << "' [" << loader.get() << "]\n"
                 "* Supported extensions: " << extensions << "\n";

    if (extensions.length() == 0)
    {
      Log::error << "Library supports no extensions. Remember to add"
                    "extensions into LoaderInterface::extensions!\n";
      return false;
    }

    // Store a reference to the same loader for all the supported extensions
    std::string::size_type extStart = 0;
    std::string::size_type extEnd;
    do
    {
      extEnd = extensions.find_first_of(",;", extStart);
      std::string extension = extensions.substr(extStart, extEnd - extStart);
      extStart = extEnd + 1;

      mLoaders[extension] = loader;

    }
    while (extEnd != std::string::npos);

    return true;
  }
  else
  {
    Log::error << "Error loading loader symbols from plugin '" << lib << "'\n";
    return false;
  }
}

std::string const AssetManager::searchPath() const
{
  return mSearchPath;
}

}
