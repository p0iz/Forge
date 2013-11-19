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

#include "Graphics/Scene/SceneConfig.hpp"
#include "lua.hpp"
#include <string>


namespace Forge { namespace Lua {

/* First, load assets from predefined directories using AssetLoader.
 * Second, load scene from scene script
 */
class SceneLoader
{
  public:
    SceneLoader();
    ~SceneLoader();

    /* Loads a scene and stores the result in 'config' */
    bool loadScene(std::string const& filename, SceneConfig& config);

    /* Lua: addDirectionalLight(scene_config, direction[3], color[4]) -- add a directional light */
    static int addDirectionalLight(lua_State* state);

    /* Lua: addDirectionalLight(scene_config, position[4], color[4]) -- add a point light */
    static int addPointLight(lua_State* state);

    /* Lua: addSpotLight(scene_config, position[4], direction[3], expnent, falloff, cutoff, color[4]) -- add a point light */
    static int addSpotLight(lua_State* state);

    /* Lua: get_scene_node(name) -- return scene node id
     *   -- name parameter is optional; if left out, root scene node is returned */
    static int getSceneNode(lua_State* state);

    /* Lua: create_scene_node(parent_id) -- return new scene node id
     *   -- parent_id is optional; if left out, parent is root node */
    static int createSceneNode(lua_State* state);

    /* TODO:
     *
     * (add technique to library, implement technique DLL's)
     * -- add_technique(dllname)
     *
     * attach attachable to scene node
     * -- attach_to_node(node_id, attachable)
     *
     * create camera
     * -- create_camera(type, position, target)
     *
     * done loading
     *   (validate scene graph and calculate world transforms, could be done in loadScene)
     */

    /* Helper to get the global scene config userdata from the Lua state */
    static SceneConfig* getSceneConfig(lua_State* state);

  private:
    /* A table containing all the functions available to configure a scene in Lua */
    static luaL_Reg const SceneLib[];

    /* Helper to store the global scene config userdata to the Lua state */
    static void setSceneConfig(lua_State* state, SceneConfig& config);

    lua_State* mState;
};

}}
