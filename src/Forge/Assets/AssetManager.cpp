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
#include "Util/Log.h"
#include <SDL2/SDL_loadso.h>
#include <memory>


namespace Forge {

AssetManager::AssetManager():
  _loadedPlugins(),
  _loaders(),
  _assetData()
{
}

AssetManager::~AssetManager()
{
  for (void* handle : _loadedPlugins)
  {
    SDL_UnloadObject(handle);
  }
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
    if (_loaders.count(ext) > 0)
    {
      std::shared_ptr<void> data(_loaders.at(ext)->load(file), _loaders[ext]->getDeleter());
      _assetData[handle] = data;
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
  return _assetData.count(handle) == 0 ? std::shared_ptr<void>() : _assetData.at(handle);
}

bool AssetManager::registerLoader(const std::string& lib)
{
  bool loaded = false;

  void* handle = SDL_LoadObject(lib.c_str());
  LoaderInterface::CreateFn createInterface = nullptr;

  if (handle)
  {
    createInterface =
      reinterpret_cast<LoaderInterface::CreateFn>(
        SDL_LoadFunction(handle, LoaderInterface::LoaderCreateInterfaceName));
  }

  if (createInterface)
  {
    std::shared_ptr<LoaderInterface> loader(createInterface());

    if (loader)
    {
      _loadedPlugins.push_back(handle);
      loaded = true;

      // Check that we actually support some extensions
      std::string extensions = loader->extensions();

      Log::info << "Loaded loader plugin '" << lib << "' [" << loader.get() << "]\n"
                   "* Supported extensions: " << extensions << "\n";

      if (extensions.length() == 0)
      {
        Log::error << "Library supports no extensions. Remember to add"
                      "extensions into LoaderInterface::extensions!\n";
      }
      else
      {
        // Store a reference to the same loader for all the supported extensions
        std::string::size_type extStart = 0;
        std::string::size_type extEnd;

        do
        {
          extEnd = extensions.find_first_of(",;", extStart);
          std::string extension = extensions.substr(extStart, extEnd - extStart);
          extStart = extEnd + 1;
          _loaders[extension] = loader;
        }
        while (extEnd != std::string::npos);
      }
    }
    else
    {
      Log::error << "Failed to create asset loader from plugin '" << lib << "'\n";
    }
  }

  if (!loaded)
  {
    Log::error << "Error loading loader symbols from plugin '" << lib << "'\n";
    SDL_UnloadObject(handle);
  }

  return loaded;
}

}
