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

#include "RendererLibrary.hpp"
#include "Graphics/RendererThread.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Viewport.hpp"
#include "UserdataMap.hpp"
#include "Util/Log.h"
#include <lua.hpp>


namespace Forge {

RendererLibrary::RendererLibrary():
  mThread()
{
}

RendererLibrary::~RendererLibrary()
{
  mThread.stop();
}

void RendererLibrary::import(lua_State* state)
{
  lua_newtable(state);
  lua_pushlightuserdata(state, &mThread);
  lua_setfield(state, -2, "threadPtr");

  // Add table for viewports
  lua_pushlightuserdata(state, new UserdataMap);
  lua_setfield(state, -2, "viewports");

  LIB_FUNC(state, start);
  LIB_FUNC(state, stop);
  LIB_FUNC(state, bindCamera);
  LIB_FUNC(state, createViewport);

  lua_setglobal(state, "Renderer");
}

void RendererLibrary::remove(lua_State* state)
{
  lua_pushnil(state);
  lua_setglobal(state, "Renderer");
}

int RendererLibrary::start(lua_State* state)
{
  findMeshAssets(state);
  RendererThread* thread = getRendererThread(state);
  lua_pushboolean(state, thread->start());
  return 1;
}

int RendererLibrary::stop(lua_State* state)
{
  RendererThread* thread = getRendererThread(state);
  thread->stop();
  return 0;
}

int RendererLibrary::findMeshAssets(lua_State* state)
{
  lua_getglobal(state, "Assets");
  if (lua_istable(state, -1))
  {
    lua_getfield(state, -1, "meshes");
    UserdataMap* meshmap = static_cast<UserdataMap*>(lua_touserdata(state, -1));
    if (!meshmap)
    {
      return luaL_error(state, "No asset map found for category 'meshes'");
    }
    RendererThread* thread = getRendererThread(state);
    thread->setMeshAssets(meshmap);
  }
  else
  {
    return luaL_error(state, "Assets library is not loaded. It is required for this function.");
  }
  return 0;
}

int RendererLibrary::createViewport(lua_State* state)
{
  Viewport* viewport = nullptr;
  switch (lua_gettop(state))
  {
    case 1:
    {
      viewport = new Viewport(getRendererThread(state)->window());
    }
    break;
    case 5:
    {
      float x = luaL_checknumber(state, 2);
      float y = luaL_checknumber(state, 3);
      float width = luaL_checknumber(state, 4);
      float height = luaL_checknumber(state, 5);
      viewport = new Viewport(getRendererThread(state)->window(), x, y, width, height);
    }
    break;
    default:
      return
        luaL_error(state, "createViewport takes 1 (name) or 5 (name,x,y,width,height) parameters");
  }
  std::string name = luaL_checkstring(state, 1);
  getRendererThread(state)->addViewport(name, viewport);

  return 0;
}

int RendererLibrary::bindCamera(lua_State* state)
{
  std::string name = luaL_checkstring(state, 1);
  Camera* camera = static_cast<Camera*>(lua_touserdata(state, 2));
  Viewport* viewport = getRendererThread(state)->getViewport(name);
  if (viewport)
  {
    viewport->setCamera(camera);
  }
  return 0;
}

RendererThread& RendererLibrary::thread()
{
  return mThread;
}

RendererThread* RendererLibrary::getRendererThread(lua_State* state)
{
  lua_getglobal(state, "Renderer");
  lua_getfield(state, -1, "threadPtr");
  return static_cast<RendererThread*>(lua_touserdata(state, -1));
}

}
