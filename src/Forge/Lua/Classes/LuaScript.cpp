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

#include "LuaScript.hpp"
#include "Application/Application.hpp"
#include "GameObject/Component/Script.hpp"
#include "Util/Internal/Keeper.hpp"
#include <lua.hpp>


namespace Forge {

namespace {
Application* a = nullptr;
}

LuaScript::LuaScript(Application& app):
  LuaClass("Script")
{
  a = &app;
}

LuaCFunction LuaScript::getCtorFn()
{
  return [](lua_State* state) -> int
  {
    char const* file = luaL_checkstring(state, -1);

    /* check userdata of table members and add either components or children */
    Script* s = a->scripts().create(file, *a);
    Script** userdata =
        static_cast<Script**>(lua_newuserdata(state, sizeof(Script**)));
    *userdata = s;

    luaL_getmetatable(state, "Script");
    lua_setmetatable(state, -2);

    return 1;
  };
}

LuaCFunction LuaScript::getDtorFn()
{
  return [](lua_State* state) -> int
  {
    Script* s = *static_cast<Script**>(luaL_checkudata(state, -1, "Script"));
    a->scripts().destroy(s);
    return 0;
  };
}

void LuaScript::addClassContent(lua_State* state)
{
  lua_pushinteger(state, static_cast<int>(ComponentType::Script));
  lua_setfield(state, -2, "type");
}

}
