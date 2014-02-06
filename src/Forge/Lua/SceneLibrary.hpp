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
#include <vector>


namespace Forge {

class Light;

class Camera;

class SceneNode;

class FORGE_EXPORT SceneLibrary : public LuaLibrary
{
  public:
    SceneLibrary();
    virtual ~SceneLibrary();

    virtual void import(lua_State* state);

    virtual void remove(lua_State* state);

    /* Lua: setGridSize(width, height)
     *
     * Description:
     *    Sets the grid size of the node containers in the world.
     *    The values are stored in Scene.grid.width and Scene.grid.height.
     *
     *    Any previously stored scene nodes will be moved to the new grid cells.
     *
     * Parameters:
     *    width: The width of the grid cells
     *    height: The height of the grid cells
     *
     * Return values:
     *    Nothing.
     */
    static int setGridSize(lua_State* state);

    /* Lua: createSceneNode(name [, x, y, z])
     *
     * Description:
     *    Creates a scene node at the given position with a default transformation.
     *
     * Parameters:
     *    x: The node's position on the x axis
     *    y: The node's position on the y axis
     *    z: The node's position on the z axis
     *
     * Return values:
     *    The created scene node.
     */
    static int createNode(lua_State* state);

    /* Lua: attach(node, attachable)
     *
     * Description:
     *    Attaches the asset
     *
     * Parameters:
     *    node: The scene node to attach to
     *    attachable: The attachable object
     *
     * Return values:
     *    Nothing.
     */
    static int attach(lua_State* state);

    /* Lua: createCamera(name, fovY, near, far)
     *
     * Description:
     *    Creates a camera with the given field of view and clip distances.
     *
     * Parameters:
     *    fovY: The camera' Y-axis field of view
     *    near: The camera's near clip distance.
     *    far: The camera's far clip distance.
     *
     * Return values:
     *    The created camera.
     */
    static int createCamera(lua_State* state);

    /* Lua: translate(node, x, y, z)
     *
     * Description:
     *    Translates a node by x, y, z
     *
     * Parameters:
     *    node: The scene node to translate
     *    x: Translate by 'x' on X-axis
     *    y: Translate by 'y' on Y-axis
     *    z: Translate by 'z' on Z-axis
     *
     * Return values:
     *    Nothing.
     */
    static int translate(lua_State* state);

    /* Lua: addDirectionalLight(direction, color)
     *
     * Description:
     *    Adds a directional light to the scene with direction and color.
     *
     * Parameters:
     *    direction: Vec3, direction of light
     *    color: Vec4, color of light (4th component denotes intensity)
     *
     * Return values:
     *    Nothing.
     */
    static int addDirectionalLight(lua_State* state);

    /* Lua: addPointLight(position, color)
     *
     * Description:
     *    Adds a point light to the scene with position and color.
     *
     * Parameters:
     *    direction: Vec3, position of light
     *    color: Vec4, color of light (4th component denotes intensity)
     *
     * Return values:
     *    Nothing.
     */
    static int addPointLight(lua_State* state);

    /* Lua: addDirectionalLight(direction, color)
     *
     * Description:
     *    Adds a directional light to the scene with direction and color.
     *
     * Parameters:
     *    position: Vec3, light's origin
     *    direction: Vec3, direction of light
     *    exponent: Light falloff exponent
     *    falloff: Light falloff angle
     *    cutoff: Light cutoff angle
     *    color: Vec4, color of light (4th component denotes intensity)
     *
     * Return values:
     *    Nothing.
     */
    static int addSpotLight(lua_State* state);

  private:
    static void addLightToScene(lua_State* state, Light&& light);

    std::vector<Light> mLights;
};

}
