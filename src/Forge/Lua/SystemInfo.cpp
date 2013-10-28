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

#include "SystemInfo.hpp"
#include <GL/glew.h>
#include <lua.hpp>


namespace Forge { namespace Lua {

void ForgeInfo::create(lua_State* state)
{
  int major = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  int minor = 0;
  glGetIntegerv(GL_MINOR_VERSION, &minor);

  lua_newtable(state);
  lua_pushnumber(state, major + 0.1 * minor);
  lua_setfield(state, -2, "openGL");
  lua_setglobal(state, "Forge");
}

}}
