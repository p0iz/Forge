#ifndef LUA_EVENTLIBRARY_HPP
#define LUA_EVENTLIBRARY_HPP

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

#include "LuaLibrary.hpp"
#include "ForgeExport.h"

namespace Forge {

class FORGE_EXPORT EventLibrary : public LuaLibrary
{
public:
  virtual void import(lua_State* state);

  virtual void remove(lua_State* state);

  virtual void frameUpdate();
};

}
#endif // LUA_EVENTLIBRARY_HPP