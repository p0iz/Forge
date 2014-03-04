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
#include "Lua/LuaLibrary.hpp"


namespace Forge {

class FORGE_EXPORT ComponentsLibrary : public LuaLibrary
{
  public:
    ComponentsLibrary();

    virtual void import(lua_State* state);
    virtual void remove(lua_State* state);

    /* Lua: Mesh(owner, mesh)
     *
     * Description:
     *    Creates a component with the given mesh asset.
     *
     * Parameter:
     *    owner: The game object that owns this component.
     *    mesh: The loaded mesh asset this component uses.
     *
     * Return values:
     *    The created component or nil if creation failed.
     */
    static int mesh(lua_State* state);

};

}
