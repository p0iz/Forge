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

#include "Lua/LuaForwardDeclarations.hpp"
#include <string>


namespace Forge {

// Base class for Lua C classes
class LuaClass
{
  public:
    explicit LuaClass(std::string const&& name);
    virtual ~LuaClass() {}

    void add(lua_State* state);

  private:
    std::string const mName;

    virtual LuaCFunction getCtorFn() = 0;
    virtual LuaCFunction getDtorFn() = 0;

    // Override this function to insert key-values into class table
    virtual void addClassContent(lua_State* state) = 0;
};

}
