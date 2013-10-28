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

#include "TechniqueLoader.hpp"
#include "Technique.hpp"
#include "Util/Log.h"
#include <lua.hpp>


namespace Forge { namespace Lua {

namespace {

void loadShader(
    lua_State* state,
    Technique* technique,
    Shader::ShaderType type,
    char const* shaderIdString
)
{
  lua_getfield(state, -1, shaderIdString);
  if (!lua_isnil(state, -1))
  {
    if (!lua_istable(state, -1))
    {
      char const* shaderFile = lua_tostring(state, -1);
      technique->addShader(type, shaderFile);
      Log::info << "Adding shader '" << shaderFile << "' of type " << shaderIdString << " to technique.\n";
    }
  }
  lua_pop(state, 1);
}

}

template <>
bool TechniqueLoader::handleLoadedLua(lua_State* state) const
{
  bool loaded = false;
  lua_getglobal(state, "technique");
  if (lua_istable(state, -1))
  {
    // Read shaders
    lua_getfield(state, -1, "shaders");

    loadShader(state, mTarget, Shader::VertexShader, "vertex");

    loadShader(state, mTarget, Shader::FragmentShader, "fragment");

    loadShader(state, mTarget, Shader::GeometryShader, "geometry");

    loadShader(state, mTarget, Shader::TessControlShader, "t_control");

    loadShader(state, mTarget, Shader::TessEvaluationShader, "t_eval");

    lua_pop(state, 1);

    // Create technique
    mTarget->create();

    loaded = true;
  }
  lua_pop(state, 1);
  return loaded;
}

}}
