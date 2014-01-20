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
#include "Graphics/RendererThread.hpp"
#include <iosfwd>


namespace Forge {

class FORGE_EXPORT RendererLibrary : public LuaLibrary
{
  public:
    explicit RendererLibrary();
    virtual ~RendererLibrary();

    virtual void import(lua_State* state);

    virtual void remove(lua_State* state);

    /* Lua: start()
     *
     * Description:
     *    starts the renderer thread
     *
     * Return values:
     *    Boolean describing whether or not the thread was started successfully.
     */
    static int start(lua_State* state);

    /* Lua: stop()
     *
     * Description:
     *    stops the renderer thread
     *
     * Return values:
     *    Nothing. (blocks until renderer thread is stopped)
     */
    static int stop(lua_State* state);

    RendererThread& thread();

private:
    RendererThread mThread;

    static RendererThread* getRendererThread(lua_State* state);
};

}
