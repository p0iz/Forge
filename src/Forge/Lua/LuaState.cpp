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

#include "LuaState.hpp"
#include "Application/Application.hpp"
#include "Lua/AssetsLibrary.hpp"
#include "Lua/InputLibrary.hpp"
#include "Lua/RendererLibrary.hpp"
#include "Lua/Classes/LuaGameObject.hpp"
#include "Lua/Classes/LuaMesh.hpp"
#include "Lua/Classes/LuaScript.hpp"
#include "Lua/Classes/LuaTransform.hpp"
#include "LuaLibrary.hpp"
#include "Util/Log.h"
#include <lua.hpp>
#include <iostream>
#include <string>


namespace Forge {

LuaState::LuaState(Application& app):
  mApp(app),
  mState(nullptr)
{
}

LuaState::~LuaState()
{
  if (mState != nullptr)
  {
    lua_close(mState);
    mState = nullptr;
  }
}

bool LuaState::initialize()
{
  mState = luaL_newstate();

  if (mState)
  {
    luaL_openlibs(mState);

    importLibrary(RendererLibrary(mApp.rendererThread()));
    importLibrary(InputLibrary());

    addClass(LuaGameObject(mApp));
    addClass(LuaMesh(mApp));
    addClass(LuaTransform(mApp));
    addClass(LuaScript(mApp));
  }

  return mState != nullptr;
}

bool LuaState::isInitialized() const
{
  return mState != nullptr;
}

void LuaState::addClass(LuaClass&& klass)
{
  klass.add(mState);
}

void LuaState::importLibrary(LuaLibrary&& library)
{
  library.import(mState);
}

void LuaState::removeLibrary(LuaLibrary&& library)
{
  library.remove(mState);
}

bool LuaState::runScript(std::string const& scriptFile)
{
  if (luaL_dofile(mState, scriptFile.c_str()))
  {
    Log::error << "Lua error: " << lua_tostring(mState, -1) << "\n";
    return false;
  }
  return true;
}

bool LuaState::isIncompleteChunk(const std::string& chunk)
{
  int previousStackPos = lua_gettop(mState);
  int status = luaL_loadbuffer(mState, chunk.data(), chunk.length(), nullptr);
  bool incomplete = false;
  if (status == LUA_ERRSYNTAX)
  {
    const char* msg = lua_tostring(mState, -1);
    std::string msgStr(msg);
    incomplete = (msgStr.find("eof") != std::string::npos);
  }
  lua_settop(mState, previousStackPos);
  return incomplete;
}

bool LuaState::runChunk(std::string const& programName, std::string const& chunk)
{
  int status = luaL_loadbuffer(mState, chunk.data(), chunk.length(), programName.data());
  if (status == LUA_OK)
  {
    lua_getglobal(mState, "print");
    lua_insert(mState, 1);
    lua_pcall(mState, 0, LUA_MULTRET, 1);
  }

  if (status != LUA_OK && !lua_isnil(mState, -1))
  {
    const char* msg = lua_tostring(mState, -1);
    if (msg)
    {
      std::cout << "Error: " << msg << "\n";
    }
    else
    {
      std::cerr << "Failed to get Lua error string, but something bad\n"
                   "did indeed happen while making the protected call.\n";
    }
    lua_pop(mState, 1);
  }
  lua_settop(mState, 0);
  return status == LUA_OK;
}

bool LuaState::hasGlobal(std::string const& name) const
{
  bool exists = false;
  lua_getglobal(mState, name.c_str());
  exists = !lua_isnil(mState, -1);
  lua_pop(mState, 1);
  return exists;
}

}
