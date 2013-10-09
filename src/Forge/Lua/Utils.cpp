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

#include "Utils.hpp"


namespace Forge { namespace Lua { namespace Utils {

glm::vec2 parseVec2(lua_State* state)
{
  glm::vec2 result;
  for (int i = 0; i < 2; ++i)
  {
    lua_rawgeti(state, -1, i+1);
    result[i] = lua_tonumber(state, -1);
    lua_pop(state, 1);
  }
  return result;
}


glm::vec3 parseVec3(lua_State* state)
{
  glm::vec3 result;
  for (int i = 0; i < 3; ++i)
  {
    lua_rawgeti(state, -1, i+1);
    result[i] = lua_tonumber(state, -1);
    lua_pop(state, 1);
  }
  return result;
}


glm::vec4 parseVec4(lua_State* state)
{
  glm::vec4 result;
  for (int i = 0; i < 4; ++i)
  {
    lua_rawgeti(state, -1, i+1);
    result[i] = lua_tonumber(state, -1);
    lua_pop(state, 1);
  }
  return result;
}

}}}
