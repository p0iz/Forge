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

namespace Forge {

class Viewport;

class FORGE_EXPORT RendererLibrary : public LuaLibrary
{
  public:
    explicit RendererLibrary();
    virtual ~RendererLibrary();

    virtual void import(lua_State* state);

    virtual void remove(lua_State* state);

    virtual void frameUpdate();

    /* Lua: start()
     *
     * Description:
     *    starts the renderer thread
     */
    static int start(lua_State* state);

    /* Lua: stop()
     *
     * Description:
     *    stops the renderer thread
     */
    static int stop(lua_State* state);

    /* Lua: createViewport(name, [x, y, width, height])
     *
     * Description:
     *    Creates a viewport in the render window. If no options are given, the viewport covers the
     *    entire window.
     *
     * Return values:
     *    Nothing.
     */
    static int createViewport(lua_State* state);

    /* Lua: bindCamera(viewport, camera)
     *
     * Description:
     *    Binds the given camera to a viewport in the render window.
     *
     * Return values:
     *    Nothing.
     */
    static int bindCamera(lua_State* state);

private:
  /* Lua: findMeshAssets()
   *
   * Description:
   *    Finds the mesh asset map for rendering. Requires the Assets library
   *    and a loader for mesh assets to be loaded. Used internally.
   *
   * Return values:
   *    Nothing.
   */
  static int findMeshAssets(lua_State* state);

  /* Lua: findLights()
   *
   * Description:
   *    Finds the light vector for rendering. Requires the Scene library to be loaded.
   *    Used internally.
   *
   * Return values:
   *    Nothing.
   */
  static int findLights(lua_State* state);
};

}
