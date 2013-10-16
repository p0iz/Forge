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

#pragma once

#include "Asset/AssetLibrary.hpp"
#include "Asset/AssetTraits.hpp"
#include <lua.hpp>


namespace Forge { namespace Lua {

// Reads the asset directories from a Lua state
template <class AssetType>
class AssetDir
{
  public:
    /* Returns the number of directory entries for a given asset tyoe */
    AssetDir(lua_State* state):
      mNumEntries(0)
    {
      // Load asset configuration
      lua_getglobal(state, AssetTraits<AssetType>::assetTypeStr);

      if (lua_istable(state, -1))
      {
        lua_len(state, -1);
        mNumEntries = lua_tointeger(state, -1);
        lua_pop(state, 1);
      }
      lua_pop(state, 1);
    }

    void load(lua_State* state)
    {
      lua_getglobal(state, AssetTraits<AssetType>::assetTypeStr);

      if (lua_isnil(state, -1))
      {
        lua_pop(state, 1);
        return;
      }

      if (mNumEntries == 0)
      {
        AssetLibrary<AssetType>::getSingleton().addDirectory(lua_tostring(state, -1));
      }
      else
      {
        for (int i = 0; i < mNumEntries; ++i)
        {
          lua_rawgeti(state, -1, i + 1);
          AssetLibrary<AssetType>::getSingleton().addDirectory(lua_tostring(state, -1));
          lua_pop(state, 1);
        }
      }
      AssetLibrary<AssetType>::getSingleton().loadAssetInfo();
      lua_pop(state, 1);
    }

  private:
    int mNumEntries;

};

}}
