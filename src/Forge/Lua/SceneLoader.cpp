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

#include "SceneLoader.hpp"
#include "Lua/AssetLoader.hpp"
#include "Lua/Material.hpp"
#include "Lua/Utils.hpp"
#include "Util/Exceptions.hpp"
#include "Util/Log.h"

namespace Forge { namespace Lua {

luaL_Reg const SceneLoader::SceneLib[] =
{
  { "addDirectionalLight", SceneLoader::addDirectionalLight },
  { "addPointLight", SceneLoader::addPointLight },
  { "addSpotLight", SceneLoader::addSpotLight },
  { nullptr, nullptr }
};

SceneLoader::SceneLoader():
  mState(luaL_newstate())
{
  luaL_openlibs(mState);

  // Register Scene management functions into 'Scene' table
  luaL_newlib(mState, SceneLib);
  lua_setglobal(mState, "Scene");

  Lua::AssetLoader::import(mState);

  // Disable I/O library to reduce tampering
  lua_pushnil(mState);
  lua_setglobal(mState, "io");
}

SceneLoader::~SceneLoader()
{
  lua_close(mState);
}

bool SceneLoader::loadScene(const std::string& filename, SceneConfig& config)
{
  setSceneConfig(mState, config);

  int error = luaL_loadfile(mState, filename.c_str()) || lua_pcall(mState, 0, 0, 0);
  if (error) {
    Log::error << lua_tostring(mState, -1) << "\n";
    return false;
  }
  return true;
}

// Light functions
int SceneLoader::addDirectionalLight(lua_State* state)
{
  // This function takes two arguments (direction, color)
  if ((lua_gettop(state) != 2) || (!lua_istable(state, -2)) || (!lua_istable(state, -1)))
  {
    Log::error << "addDirectionalLight called with the wrong arguments\n";
    return luaL_error(state, " Usage: addDirectionalLight(direction[3], color[4])");
  }

  glm::vec4 color;
  Utils::parseVec(state, 4, &color[0]);
  lua_pop(state, 1);

  glm::vec3 direction;
  Utils::parseVec(state, 3, &direction[0]);
  lua_pop(state, 1);


  SceneConfig* sceneConfig = getSceneConfig(state);

  Light light;
  light.type = Light::DIRECTIONAL;
  light.position = glm::vec4(direction, 0.0f);
  light.getShaderData().color = color;
  sceneConfig->lights.push_back(light);

  return 0;
}

int SceneLoader::addPointLight(lua_State* state)
{
  // This function takes two arguments (position, color)
  if ((lua_gettop(state) != 2) || (!lua_istable(state, -2)) || (!lua_istable(state, -1)))
  {
    return luaL_error(state, " Usage: addPointLight(position[4], color[4])");
  }

  glm::vec4 color;
  Utils::parseVec(state, 4, &color[0]);
  lua_pop(state, 1);

  glm::vec4 position;
  Utils::parseVec(state, 4, &position[0]);
  lua_pop(state, 1);

  SceneConfig* sceneConfig = getSceneConfig(state);

  Light light;
  light.type = Light::POINT;
  light.position = position;
  light.getShaderData().color = color;
  sceneConfig->lights.push_back(light);

  return 0;
}

int SceneLoader::addSpotLight(lua_State* state)
{
  if ((lua_gettop(state) != 6) || (!lua_istable(state, -6)) || (!lua_istable(state, -5)) || (!lua_istable(state, -1)))
  {
    return luaL_error(state, " Usage: addSpotLight(position[4], direction[3], exponent, falloff, cutoff, color[4])");
  }

  glm::vec4 color;
  Utils::parseVec(state, 4, &color[0]);
  lua_pop(state, 1);

  float cutoff = lua_tonumber(state, -1);
  lua_pop(state, 1);

  float falloff = lua_tonumber(state, -1);
  lua_pop(state, 1);

  float exponent = lua_tonumber(state, -1);
  lua_pop(state, 1);

  glm::vec3 direction;
  Utils::parseVec(state, 3, &direction[0]);
  lua_pop(state, 1);

  glm::vec4 position;
  Utils::parseVec(state, 4, &position[0]);
  lua_pop(state, 1);

  SceneConfig* sceneConfig = getSceneConfig(state);

  Light light;
  light.type = Light::SPOT;
  light.position = position;
  light.spotDirection = direction;
  light.getShaderData().spotCutoff = cutoff;
  light.getShaderData().spotFalloff = falloff;
  light.getShaderData().spotExponent = exponent;
  light.getShaderData().color = color;
  sceneConfig->lights.push_back(light);

  return 0;
}

// Scene graph functions
int SceneLoader::getSceneNode(lua_State* state)
{
  switch (lua_gettop(state))
  {
    case 0: // Root scene node (no arguments)
      lua_pushinteger(state, 0);
      break;
    case 1: // Named scene node (one argument)
      {
        SceneConfig* sc = getSceneConfig(state);
        std::string nodeName = lua_tostring(state, -1);
        lua_pop(state, 1);
        try
        {
          lua_pushinteger(state, sc->getSceneNode(nodeName).mId);
        }
        catch (NotFoundException nfe)
        {
          return luaL_error(state, "A node with the name '%s' was not found!", nfe.missing.c_str());
        }
      }
      break;
    default:
      return luaL_error(state, "get_scene_node takes one or zero arguments of the type string");
  }

  return 1;
}

int SceneLoader::createSceneNode(lua_State* state)
{
  lua_pushinteger(state, 0);
  return 1;
}

// Scene loader functions
SceneConfig* SceneLoader::getSceneConfig(lua_State* state)
{
  lua_getglobal(state, "SceneConfig");
  SceneConfig* sc = static_cast<SceneConfig*>(lua_touserdata(state, -1));
  lua_pop(state, 1);
  return sc;
}

void SceneLoader::setSceneConfig(lua_State* state, SceneConfig& config)
{
  lua_pushlightuserdata(state, &config);
  lua_setglobal(state, "SceneConfig");
}

}}
