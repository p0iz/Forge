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
#include "AssetPlugins/LoaderInterface.hpp"
#include "Util/Log.h"
#include "Platform/DynamicLoader/DynamicLoader.hpp"
#include "Platform/FileSystem/Directory.hpp"
#include "Platform/FileSystem/File.hpp"
#include <lua.hpp>
#include <unordered_map>


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
  if (!loaderLib->isValid())
  {
    Log::error << "Failed to load plugin '" << loader << "'\n";
  }
  LoaderCreateFn createInterface = loaderLib->loadSymbol<LoaderCreateFn>("createInterface");
  LoaderInfoFn category = loaderLib->loadSymbol<LoaderInfoFn>("category");
  LoaderInfoFn supportedExtensions = loaderLib->loadSymbol<LoaderInfoFn>("supportedExtensions");
  if (createInterface && category && supportedExtensions)
  {
    // Check that we actually support some extensions
    std::string extensions = supportedExtensions();
    if (extensions.length() == 0)
    {
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
    lua_pushstring(state, category());
    lua_setfield(state, -2, "category");

    // Set metatable
    luaL_getmetatable(state, "Assets.Loader");
    lua_setmetatable(state, -1);

    // Store a reference to the same loader for all the supported extensions
    int count = 0;
    std::string ext;
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

void AssetsLibrary::import(lua_State* state)
{
  lua_newtable(state);
  lua_pushstring(state, ".");
  lua_setfield(state, -2, "pluginPath");
  lua_pushcfunction(state, parsePath);
  lua_setfield(state, -2, "parse");
  lua_pushcfunction(state, setLoaderPath);
  lua_setfield(state, -2, "setLoaderPath");
  lua_pushcfunction(state, addLoader);
  lua_setfield(state, -2, "addLoader");
  lua_newtable(state);
  lua_setfield(state, -2, "loaders");
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

int AssetsLibrary::parsePath(lua_State* state)
{
  int found = 0;

  FileSystem::Directory directory(luaL_checkstring(state, 1));
  auto fileList = directory.listFiles();

  std::unordered_map<std::string, int> fileCounts;
  for (std::string& filename : fileList)
  {
    // Check if file is supported
    ++fileCounts[FileSystem::File::getExtension(filename)];
  }

  for (auto pair : fileCounts)
  {
    Log::info << "Got " << pair.second << " of type '" << pair.first << "'.\n";
  }

  lua_pushinteger(state, found);
  return 1;
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
