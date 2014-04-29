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

#pragma once

#include "ForgeExport.h"
#include "LuaLibrary.hpp"


namespace Forge {

class FORGE_EXPORT PrimitivesLibrary : public LuaLibrary
{
  public:
    PrimitivesLibrary();
    virtual ~PrimitivesLibrary();

    virtual void import(lua_State* state);

    virtual void remove(lua_State* state);

    /* Lua: box(width, height, depth)
     *
     * Description:
     *    Creates a box with the given dimensions
     *
     * Parameters:
     *    width: The width of ther box (X-axis)
     *    height: The height of the box (Y-axis)
     *    depth: The depth of the box (Z-axis)
     *
     * Return values:
     *    A userdatum representing the mesh or nil if it could not be added to the mesh map.
     */
    static int createBox(lua_State* state);

};

}
