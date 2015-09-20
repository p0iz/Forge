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

#include "AssetLoader.hpp"
#include "Graphics/Libraries/MaterialLibrary.hpp"
#include "Graphics/Libraries/MeshLibrary.hpp"
#include "Graphics/Material/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Scene/SceneConfig.hpp"
#include "Lua/Material.hpp"
#include "Lua/Mesh.hpp"
#include "Lua/SceneLoader.hpp"
#include "lua.hpp"


namespace Forge { namespace Lua {

luaL_Reg const AssetLoader::AssetsLib[] =
{
  { "loadMesh", AssetLoader::loadMesh },
  { "loadMaterial", AssetLoader::loadMaterial },
  { nullptr, nullptr }
};

void AssetLoader::import(lua_State* state)
{
  // Register asset management functions into 'Assets' table
  luaL_register(state, "Assets", AssetsLib);
}

int AssetLoader::loadMesh(lua_State* state)
{
  if (lua_gettop(state) != 1)
  {
    Log::error << "loadMesh called with the wrong arguments.\n";
    return luaL_error(state, "loadMesh takes only one argument, %d given", lua_gettop(state));
  }

  std::string meshName(lua_tolstring(state, -1, nullptr));
  lua_pop(state, 1);

  MeshPtr mesh = Graphics::MeshLibrary::instance().obtainAsset(meshName);

  if (mesh)
  {
    SceneConfig* sc = SceneLoader::getSceneConfig(state);
    if (sc)
    {
      sc->addUsedMesh(meshName);
    }
    else
    {
      Graphics::MeshLibrary::instance().releaseAsset(meshName);
    }
    Lua::Mesh(meshName).create(state);
  }
  else
  {
    Log::error << "Failed to load mesh asset '" << meshName << "'.\n";
    lua_pushnil(state);
  }

  return 1;
}

int AssetLoader::loadMaterial(lua_State* state)
{
  if (lua_gettop(state) != 1)
  {
    return luaL_error(
      state,
      "loadMaterial takes only one string argument, %d given",
      lua_gettop(state)
    );
  }

  std::string materialName(lua_tolstring(state, -1, nullptr));
  lua_pop(state, 1);

  MaterialPtr material = Graphics::MaterialLibrary::instance().obtainAsset(materialName);

  if (material)
  {
    SceneConfig* sc = SceneLoader::getSceneConfig(state);
    if (sc)
    {
      sc->addUsedMaterial(materialName);
    }
    else
    {
      Graphics::MaterialLibrary::instance().releaseAsset(materialName);
    }
    Material(materialName).create(state);
  }
  else
  {
    Log::error << "Failed to load material asset '" << materialName << "'.\n";
    lua_pushnil(state);
  }

  return 1;
}

}}
