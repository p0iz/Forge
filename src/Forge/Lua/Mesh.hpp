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
#include "ObjectCreator.hpp"
#include <string>


namespace Forge { namespace Lua {

class FORGE_EXPORT Mesh : public ObjectCreator
{
  public:
    Mesh(std::string const& name);

    void create(lua_State* state);

    /* Lua: setMaterial(material) -- Sets the material for this mesh */
    static int setMaterial(lua_State* state);

    /* Lua: attachTo(nodeId) -- Attaches this mesh to the requested node id */
    static int attachTo(lua_State* state);

  private:
    std::string mName;

};

}}
