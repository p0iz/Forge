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
  LIB_FUNC(state, start);
  LIB_FUNC(state, stop);
  lua_setglobal(state, "Renderer");
}

void RendererLibrary::remove(lua_State* state)
{
  lua_pushnil(state);
  lua_setglobal(state, "Renderer");
}

int RendererLibrary::start(lua_State* state)
{
  lua_getglobal(state, "Renderer");
  lua_getfield(state, -1, "threadPtr");
  RendererThread* thread = static_cast<RendererThread*>(lua_touserdata(state, -1));
  lua_pushboolean(state, thread->start());
  return 1;
}

int RendererLibrary::stop(lua_State* state)
{
  lua_getglobal(state, "Renderer");
  lua_getfield(state, -1, "threadPtr");
  RendererThread* thread = static_cast<RendererThread*>(lua_touserdata(state, -1));
  thread->stop();
  return 0;
}

RendererThread& RendererLibrary::thread()
{
  return mThread;
}

}
