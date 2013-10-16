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

#include "ConfigLoader.hpp"

#include "Asset/AssetTraits.hpp"
#include "Asset/AssetLibrary.hpp"
#include "Graphics/Libraries/MeshTraits.hpp"
#include "Graphics/Libraries/MaterialTraits.hpp"
#include "Lua/AssetDir.hpp"
#include "Lua/Utils.hpp"
#include "Configuration.hpp"
#include "Util/Log.h"

#include "lua.hpp"


namespace Forge { namespace Lua {

template <>
bool ConfigLoader::handleLoadedLua(lua_State* state) const
{
  bool loaded = false;

  // Load window configuration
  lua_getglobal(state, "width");
  lua_getglobal(state, "height");
  if (lua_isnumber(state, -2) && lua_isnumber(state, -1)) {
    mTarget->display.width = lua_tonumber(state, -2);
    mTarget->display.height = lua_tonumber(state, -1);
    loaded = true;
  } else {
    Log::error << "Config error: display parameters should be numbers!\n";
  }

  AssetDir<Mesh> meshDirs(state);
  AssetDir<Material> materialDirs(state);
  meshDirs.load(state);
  materialDirs.load(state);

  return loaded;
}

}}
