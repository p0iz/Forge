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

#pragma once

#include "lua.hpp"


namespace Forge { namespace Lua { namespace Utils {

// Parses a vector into an array and returns the number of values read
template <class DataType>
int parseVec(lua_State* state, int length, DataType* result)
{
  int idx = 0;

  if (!lua_istable(state, -1))
  {
    return idx;
  }

  while (!lua_isnil(state, idx) && (idx < length))
  {
    lua_rawgeti(state, -1, idx+1);
    result[idx] = lua_tonumber(state, -1);
    lua_pop(state, 1);
    ++idx;
  }

  return idx;
}

}}}
