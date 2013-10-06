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

struct luaL_Reg;
struct lua_State;

namespace Forge { namespace Lua {

/* A Lua library class for loading assets */
class AssetLoader
{
  public:
    static void import(lua_State* state);

    /* Lua: loadMesh(assetName) -- loads the mesh for use in the current scene config */
    static int loadMesh(lua_State* state);

    /* Lua: loadMaterial(assetName) -- load material for use in the current scene config */
    static int loadMaterial(lua_State* state);

    /* TODO:
     *
     * (add technique to library, implement technique DLL's)
     * -- add_technique(dllname)
     *
     * attach attachable to scene node
     * -- attach_to_node(node_id, attachable)
     *
     * create camera
     * -- create_camera(type, position, target)
     *
     * done loading
     *   (validate scene graph and calculate world transforms, could be done in loadScene)
     */

  private:
    /* A table containing all the functions available to configure a scene in Lua */
    static luaL_Reg const AssetsLib[];

};

}}
