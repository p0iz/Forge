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

#include "LuaMesh.hpp"
#include "Application/Application.hpp"
#include "GameObject/Component/MeshInstance.hpp"
#include "GameObject/Component/ComponentTypes.hpp"
#include "Util/Internal/Keeper.hpp"
#include <lua.hpp>


namespace Forge {

namespace {
  Application* a;
}

LuaMesh::LuaMesh(Application& app):
  LuaClass("Mesh")
{
  a = &app;
}

LuaCFunction LuaMesh::getCtorFn()
{
  return [](lua_State* state)
  {
    /* Get the game object components and children */
    char const* file = luaL_checkstring(state, -1);

    /* check userdata of table members and add either components or children */

    MeshInstance* m = a->meshes().create(file, *a);
    MeshInstance** userdata = static_cast<MeshInstance**>(lua_newuserdata(state, sizeof(MeshInstance**)));
    *userdata = m;

    luaL_getmetatable(state, "Mesh");
    lua_setmetatable(state, -2);

    return 1;
  };
}

LuaCFunction LuaMesh::getDtorFn()
{
  return [](lua_State* state)
  {
    MeshInstance* m = *static_cast<MeshInstance**>(luaL_checkudata(state, -1, "Mesh"));
    a->meshes().destroy(m);
    return 0;
  };
}

void LuaMesh::addClassContent(lua_State* state)
{
  lua_pushinteger(state, static_cast<int>(ComponentType::Mesh));
  lua_setfield(state, -2, "type");
}

}
