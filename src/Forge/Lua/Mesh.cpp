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

#include "Mesh.hpp"
#include "Graphics/Libraries/MaterialLibrary.hpp"
#include "Graphics/Libraries/MeshLibrary.hpp"
#include "Util/Log.h"
#include "lua.hpp"

Forge::Lua::Mesh::Mesh(const std::string& name):
  mName(name)
{
}

void Forge::Lua::Mesh::create(lua_State* state)
{
  lua_newtable(state);
  lua_pushstring(state, mName.c_str());
  lua_setfield(state, -2, "name");
  lua_pushcfunction(state, setMaterial);
  lua_setfield(state, -2, "setMaterial");
}

int Forge::Lua::Mesh::setMaterial(lua_State* state)
{
  // Get material name
  lua_getfield(state, -1, "name");
  if (!lua_isstring(state, -1))
  {
    lua_pushboolean(state, 0);
    return 1;
  }
  char const* materialName = lua_tostring(state, -1);
  lua_pop(state, 1);

  // Get mesh name
  lua_getfield(state, -2, "name");
  if (!lua_isstring(state, -1))
  {
    lua_pushboolean(state, 0);
    return 1;
  }

  char const* meshName = lua_tostring(state, -1);
  lua_pop(state, 3);

  MaterialPtr material = Graphics::MaterialLibrary::getSingleton().getAssetInfo(materialName).asset;

  if (!material)
  {
    Log::error << "Material '" << materialName << "' not loaded!\n";
    return 0;
  }

  MeshPtr mesh = Graphics::MeshLibrary::getSingleton().getAssetInfo(meshName).asset;

  if (!mesh)
  {
    Log::error << "Mesh '" << meshName << "' not loaded!\n";
    return 0;
  }

  material->useOn(mesh);

  return 0;
}

