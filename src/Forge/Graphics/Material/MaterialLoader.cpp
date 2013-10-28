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
#include "Graphics/Libraries/TechniqueLibrary.hpp"
#include "Lua/Utils.hpp"
#include "Util/Log.h"
#include <lua.hpp>

namespace Forge { namespace Lua {

// Define helpers in anonymous namespace
namespace {

TechniquePtr loadTechnique(lua_State* state)
{
  TechniquePtr technique;
  lua_getfield(state, -1, "technique");
  if (lua_isstring(state, -1))
  {
    std::string techniqueName = lua_tostring(state, -1);
    Log::info << "Loading technique '" << techniqueName << "'...\n";
    technique = Graphics::TechniqueLibrary::instance().obtainAsset(techniqueName);
    if (technique)
    {
      technique->setName(techniqueName);
    }
  }
  lua_pop(state, 1);
  return technique;
}

void onNoSuchUniform(std::string const& name, TechniquePtr technique)
{
  Log::LogStream& stream = Log::error << "No uniforms called '" << name << "' in technique.\n"
                                         "Possible values are:\n";
  auto names = technique->getUniformNames();
  for (auto name : names)
  {
    stream << name << "\n";
  }
}

}

template <>
bool MaterialLoader::handleLoadedLua(lua_State* state) const
{
  bool loaded = false;
  lua_getglobal(state, "material");
  if (lua_istable(state, -1))
  {
    TechniquePtr technique = loadTechnique(state);
    if (technique)
    {
      mTarget->mTechnique = technique;
      loaded = true;
      // Read settings for the tecnique
      lua_getfield(state, -1, "properties");
      if (lua_istable(state, -1))
      {
        lua_pushnil(state);
        while (lua_next(state, -2))
        {
          std::string name = lua_tostring(state, -2);

          int length = 1;
          float values[4];
          if (lua_istable(state, -1))
          {
            lua_len(state, -1);
            length = lua_tonumber(state, -1);
            lua_pop(state, 1);
            Utils::parseVec(state, length, values);
          }
          else
          {
            values[0] = lua_tonumber(state, -1);
          }

          if (!technique->setUniform(name, length, values))
          {
            onNoSuchUniform(name, technique);
            loaded = false;
          }
          lua_pop(state, 1);
        }
      }
    }
  }
  lua_pop(state, 1);
  return loaded;
}

}}
