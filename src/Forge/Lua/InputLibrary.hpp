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

class FORGE_EXPORT InputLibrary : public LuaLibrary
{
  public:
    InputLibrary();
    virtual ~InputLibrary();

    virtual void import(lua_State* state);
    virtual void remove(lua_State* state);

  private:
    static int isKeyDown(lua_State* state);

    // Pushes a key code table on the Lua stack
    void pushKeyCodeTable(lua_State* state);
};

}
