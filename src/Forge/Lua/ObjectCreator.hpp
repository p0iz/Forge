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

// Forward declaration
struct lua_State;

namespace Forge { namespace Lua {

/* This class provides an interface for creating objects to a valid Lua stack.
 * It is up to the user of this interface to define a valid Lua object/table.
 */
class ObjectCreator
{
  public:
    virtual ~ObjectCreator() { }

    /* Creates an object at the top of the Lua stack */
    virtual void create(lua_State* state) = 0;
};

}}
