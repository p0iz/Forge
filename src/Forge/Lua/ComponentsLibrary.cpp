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

#include "ComponentsLibrary.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Component/MeshComponent.hpp"
#include "Util/Internal/Keeper.hpp"
#include <lua.hpp>


namespace Forge {

class Mesh;

ComponentsLibrary::ComponentsLibrary()
{
}

void ComponentsLibrary::import(lua_State* state)
{
  lua_newtable(state);

  LIB_FUNC(state, mesh);

  lua_setglobal(state, "Components");
}

void ComponentsLibrary::remove(lua_State* state)
{
  lua_pushnil(state);
  lua_setglobal(state, "Components");
}

int ComponentsLibrary::mesh(lua_State* state)
{
  GameObject* owner = static_cast<GameObject*>(lua_touserdata(state, 1));
  Mesh* mesh = static_cast<Mesh*>(lua_touserdata(state, 2));
  if (owner && mesh)
  {
    MeshComponent* component = Keeper<MeshComponent>::instance().create(owner, mesh);
    lua_pushlightuserdata(state, component);
  }
  else
  {
    return luaL_error(state, "Usage: Components.mesh(owner, mesh)");
  }
  return 1;
}

}
