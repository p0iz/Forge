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

#include "ForgeExport.h"
#include "LuaLibrary.hpp"
#include <iosfwd>


namespace Forge {

class FORGE_EXPORT AssetsLibrary : public LuaLibrary
{
  public:
    AssetsLibrary();
    virtual ~AssetsLibrary();

    virtual void import(lua_State* state);

    virtual void remove(lua_State* state);

    /* Lua: parse(path)
     *
     * Description:
     *    parses the contents of a path and stores recognized assets in
     *    a global table.
     *
     * Parameter(s):
     *    path: The path to parse
     *
     * Return values:
     *    The number of assets found
     */
    static int parsePath(lua_State* state);

    /* Lua: setLoaderPath(path)
     *
     * Description:
     *    Sets the search path for loading asset loader plugins.
     *
     * Parameter(s):
     *    path: The path to search for plugins in.
     *
     * Return values:
     *    Nothing.
     */
    static int setLoaderPath(lua_State* state);

    /* Lua: addLoader(loader)
     *
     * Description:
     *    loads a plugin from the search path and stores a loader interface
     *
     * Parameter(s):
     *    loader: Name of the loader library (e.g. ObjLoader)
     *
     * Return values:
     *    The loader userdata or nil if loading failed
     */
    static int addLoader(lua_State* state);

    /* Lua: deleteLoader(loader)
     *
     * Description:
     *    frees the memory associated with a plugin when the object is collected
     *
     * Parameter(s):
     *    loader: Name of the loader library (e.g. ObjLoader)
     *
     * Return values:
     *    Nothing
     */
    static int deleteLoader(lua_State* state);
};

}
