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

#include "LuaClass.hpp"
#include <lua.hpp>


namespace Forge {

LuaClass::LuaClass(std::string const&& name):
  mName(name)
{
}

void LuaClass::add(lua_State* state)
{
  luaL_newmetatable(state, mName.c_str());

  // When the class table is used as a metatable for instances, index into it
  lua_pushvalue(state, -1);
  lua_setfield(state, -2, "__index");

  // Add the destructor (called when the instance is collected)
  lua_pushcfunction(state, getDtorFn());
  lua_setfield(state, -2, "__gc");

  // Add constructor to class table metatable
  std::string metaTableName = mName + ".meta";
  luaL_newmetatable(state, metaTableName.c_str());
  lua_pushcfunction(state, getCtorFn());
  lua_setfield(state, -2, "__call");
  lua_setmetatable(state, -2);

  addClassContent(state);

  lua_setglobal(state, mName.c_str());
}

}
