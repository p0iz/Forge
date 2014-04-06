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

#include "AssetsLibrary.hpp"
#include "Assets/LoaderInterface.hpp"
#include "Platform/DynamicLoader/DynamicLoader.hpp"
#include "Platform/FileSystem/Directory.hpp"
#include "Platform/FileSystem/File.hpp"
#include "UserdataMap.hpp"
#include "Util/Log.h"
#include <lua.hpp>



namespace Forge {

AssetsLibrary::AssetsLibrary()
{
}

AssetsLibrary::~AssetsLibrary()
{
}

int AssetsLibrary::addLoader(lua_State* state)
{
  std::string loader = luaL_checkstring(state, 1);

  lua_getglobal(state, "Assets");
  lua_getfield(state, -1, "pluginPath");

  DynamicLoader dllLoader(luaL_checkstring(state, -1));

  lua_pop(state, 1);

  DynamicLibrary* loaderLib = dllLoader.open(loader);
  if (!loaderLib || !loaderLib->isValid())
  {
    Log::error << "Failed to load plugin '" << loader << "'\n";
    return luaL_error(state, "Error loading loader plugin '%s'", loader.c_str());
  }
  LoaderCreateFn createInterface = loaderLib->loadSymbol<LoaderCreateFn>("createInterface");
  LoaderInfoFn supportedExtensions = loaderLib->loadSymbol<LoaderInfoFn>("supportedExtensions");
  if (createInterface && supportedExtensions)
  {
    // Check that we actually support some extensions
    std::string extensions = supportedExtensions();
    if (extensions.length() == 0)
    {
      delete loaderLib;
      return luaL_error(state, "Loader says that it does not support any extensions");
    }

    lua_getfield(state, -1, "loaders");

    LoaderInterface* loaderInterface = createInterface();
    Log::info << "Loaded loader plugin '" << loader << "' [" << loaderInterface << "]\n"
                 "* Supported extensions: " << extensions << "\n";
    lua_newtable(state);
    lua_pushlightuserdata(state, loaderInterface);
    lua_setfield(state, -2, "loaderPtr");
    lua_pushlightuserdata(state, loaderLib);
    lua_setfield(state, -2, "libraryPtr");

    // Set metatable
    luaL_getmetatable(state, "Assets.Loader");
    lua_setmetatable(state, -2);

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

    lua_pop(state, 1);

    char const* category = loaderInterface->category();
    lua_getfield(state, -2, category);
    if (lua_isnil(state, -1))
    {
      Log::info << "Adding asset map for category '" << category << "'\n";
      lua_getglobal(state, "Assets");
      void* assetmapData = lua_newuserdata(state, sizeof(UserdataMap));
      if (assetmapData && new (assetmapData) UserdataMap())
      {
        lua_setfield(state, -2, category);
      }
      else
      {
        return luaL_error(state, "Failed to allocate asset map for '%s'", category);
      }
    }

    lua_pushnumber(state, count);

    return 1;
  }
  else
  {
    return luaL_error(state, "Error loading loader symbols from plugin '%s'", loader.c_str());
  }
}

int AssetsLibrary::deleteLoader(lua_State* state)
{
  lua_getfield(state, -1, "loaderPtr");
  LoaderInterface* loader = static_cast<LoaderInterface*>(lua_touserdata(state, -1));
  delete loader;
  lua_getfield(state, -1, "libraryPtr");
  DynamicLibrary* libraryPtr = static_cast<DynamicLibrary*>(lua_touserdata(state, -1));
  delete libraryPtr;
  return 0;
}

int AssetsLibrary::load(lua_State* state)
{
  std::string filename = luaL_checkstring(state, 1);
  std::string extension = FileSystem::File::getExtension(filename);
  lua_getglobal(state, "Assets");
  lua_getfield(state, -1, "loaders");
  lua_getfield(state, -1, extension.c_str());
  if (lua_isnil(state, -1) == false)
  {
    lua_getfield(state, -1, "loaderPtr");
    LoaderInterface* loader = static_cast<LoaderInterface*>(lua_touserdata(state, -1));
    if (loader)
    {
      // Get the asset map for assets of the loader's category
      lua_getfield(state, -4, loader->category());
      UserdataMap* assetmap = static_cast<UserdataMap*>(lua_touserdata(state, -1));
      if (!assetmap)
      {
        return luaL_error(state, "Asset map for category '%s' not found.", loader->category());
      }
      else if (assetmap->count(filename) > 0)
      {
        lua_pushlightuserdata(state, assetmap->at(filename));
      }
      else if(void* asset = loader->load(filename))
      {
        (*assetmap)[filename] = asset;
        lua_pushlightuserdata(state, asset);
      }
      else
      {
        lua_pushnil(state);
      }
      return 1;
    }
    else
    {
      return luaL_error(state, "Null pointer loader for extension '%s' ", extension.c_str());
    }
  }
  else
  {
    return luaL_error(state, "No loader found for extension '%s'", extension.c_str());
  }
}

void AssetsLibrary::import(lua_State* state)
{
  lua_newtable(state);
  lua_pushstring(state, ".");
  lua_setfield(state, -2, "pluginPath");
  lua_newtable(state);
  lua_setfield(state, -2, "loaders");
  LIB_FUNC(state, setLoaderPath);
  LIB_FUNC(state, addLoader);
  LIB_FUNC(state, load);
  lua_setglobal(state, "Assets");

  // Create the loader metatable
  luaL_newmetatable(state, "Assets.Loader");
  lua_pushcfunction(state, deleteLoader);
  lua_setfield(state, -2, "__gc");
}

void AssetsLibrary::remove(lua_State* state)
{
  lua_pushnil(state);
  lua_setglobal(state, "Assets");
}

int AssetsLibrary::setLoaderPath(lua_State* state)
{
  luaL_checkstring(state, -1);
  lua_getglobal(state, "Assets");
  lua_insert(state, -2);
  lua_setfield(state, -2, "pluginPath");
  return 0;
}

}
