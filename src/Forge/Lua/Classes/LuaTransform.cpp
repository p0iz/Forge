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

#include "LuaTransform.hpp"
#include "Application/Application.hpp"
#include "GameObject/Transformation.hpp"
#include "Util/Internal/Keeper.hpp"
#include <lua.hpp>


namespace Forge {

namespace {
Application* a;
}

LuaTransform::LuaTransform(Application& app):
  LuaClass("Transform")
{
  a = &app;
}

LuaCFunction LuaTransform::getCtorFn()
{
  return [](lua_State* state) -> int
  {
    /* Get the game object components and children */
    float x = luaL_checknumber(state, 2);
    float y = luaL_checknumber(state, 3);
    float z = luaL_checknumber(state, 4);

    /* check userdata of table members and add either components or children */

    Transformation* t = a->transforms().create(x,y,z);
    Transformation** userdata =
        static_cast<Transformation**>(lua_newuserdata(state, sizeof(Transformation**)));
    *userdata = t;

    luaL_getmetatable(state, "Transform");
    lua_setmetatable(state, -2);

    return 1;
  };
}

LuaCFunction LuaTransform::getDtorFn()
{
  return [](lua_State* state) -> int
  {
    Transformation* t = *static_cast<Transformation**>(luaL_checkudata(state, -1, "Transform"));
    a->transforms().destroy(t);
    return 0;
  };
}

void LuaTransform::addClassContent(lua_State* state)
{
}

}
