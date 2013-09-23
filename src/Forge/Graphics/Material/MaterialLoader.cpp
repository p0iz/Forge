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

#include "MaterialLoader.hpp"
#include "Material.h"
#include "Technique/LuaProperties.hpp"
#include "Technique/TechniqueLibrary.h"
#include "Util/Log.h"

#include "lua.hpp"

namespace Forge { namespace Lua {

// Define helpers in anonymous namespace
namespace {

TechniquePtr loadTechnique(lua_State* state)
{
  TechniquePtr technique;
  lua_getfield(state, -1, "technique");
  if (lua_isstring(state, -1)) {
    std::string techniqueName = lua_tostring(state, -1);
    Log::info << "Loading technique '" << techniqueName << "'...\n";
    technique = TechniqueLibrary::getSingleton().get(techniqueName);
  }
  lua_pop(state, 1);
  return technique;
}

bool loadProperties(lua_State* state, TechniquePtr technique)
{
  lua_getfield(state, -1, "properties");
  bool loaded = lua_istable(state, -1);
  if (loaded) {
    // Update technique properties using Lua state with properties table on top
    LuaProperties properties(state);
    technique->updateProperties(properties);
  } else {
    Log::error << "Failed to load material properties.\n"
           << "Ensure that material has a subtable called 'properties'\n";
  }
  lua_pop(state, 1);
  return loaded;
}

}

template <>
bool MaterialLoader::handleLoadedLua(lua_State* state) const
{
  bool loaded = false;
  lua_getglobal(state, "material");
  if (lua_istable(state, -1)) {
    TechniquePtr technique = loadTechnique(state);
    if (technique) {
      technique->create();
      mTarget->mTechnique = technique;
      loaded = loadProperties(state, technique);
    }
  }
  return loaded;
}

}}
