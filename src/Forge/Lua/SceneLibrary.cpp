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

#include "SceneLibrary.hpp"
#include "GameObject/GameObject.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Light/Light.hpp"
#include "UserdataMap.hpp"
#include "Util/Internal/Keeper.hpp"
#include "Util/Log.h"
#include "Utils.hpp"
#include <lua.hpp>
#include <vector>


namespace Forge {

SceneLibrary::SceneLibrary()
{
}

SceneLibrary::~SceneLibrary()
{
}

void SceneLibrary::import(lua_State* state)
{
  lua_newtable(state);
  lua_newtable(state);
  lua_pushunsigned(state, 5);
  lua_setfield(state, -2, "width");
  lua_pushunsigned(state, 5);
  lua_setfield(state, -2, "height");
  lua_setfield(state, -2, "grid");

  lua_newtable(state);
  lua_setfield(state, -2, "objects");

  lua_newtable(state);
  lua_setfield(state, -2, "cameras");

  LIB_FUNC(state, setGridSize);
  LIB_FUNC(state, createObject);
  LIB_FUNC(state, attach);
  LIB_FUNC(state, createCamera);
  LIB_FUNC(state, translate);
  LIB_FUNC(state, addDirectionalLight);
  LIB_FUNC(state, addPointLight);
  LIB_FUNC(state, addSpotLight);

  lua_setglobal(state, "Scene");

  // Create the loader metatable
  luaL_newmetatable(state, "Scene.GameObject");
  lua_pushcfunction(state, deleteObject);
  lua_setfield(state, -2, "__gc");
}

void SceneLibrary::remove(lua_State* state)
{
  lua_pushnil(state);
  lua_setglobal(state, "Scene");
}

int SceneLibrary::setGridSize(lua_State* state)
{
  unsigned int width = luaL_checkunsigned(state, 1);
  unsigned int height = luaL_checkunsigned(state, 2);

  lua_getglobal(state, "Scene");
  lua_getfield(state, -1, "grid");
  lua_pushunsigned(state, width);
  lua_setfield(state, -2, "width");
  lua_pushunsigned(state, height);
  lua_setfield(state, -2, "height");

  return 0;
}

int SceneLibrary::createObject(lua_State* state)
{
  char const* name = luaL_checkstring(state, 1);
  float x = 0, y = 0, z = 0;

  if (lua_gettop(state) == 4)
  {
    x = luaL_checknumber(state, 2);
    y = luaL_checknumber(state, 3);
    z = luaL_checknumber(state, 4);
  }
  Log::info << "Game object '" << name << "' created at point [" << x << "," << y << "," << z << "]\n";

  // Store game object in collection and set pointer to Scene.objects.<name>
  void* objectData = lua_newuserdata(state, sizeof(GameObject));
  luaL_getmetatable(state, "Scene.GameObject");
  lua_setmetatable(state, -2);
  if (objectData && new (objectData) GameObject(name))
  {
    lua_getglobal(state, "Scene");
    lua_getfield(state, -1, "objects");
    lua_pushvalue(state, -3);
    lua_setfield(state, -2, name);
    lua_pushvalue(state, -3);
  }
  else
  {
    lua_pushnil(state);
  }

  return 1;
}

int SceneLibrary::deleteObject(lua_State* state)
{
  GameObject* object = static_cast<GameObject*>(lua_touserdata(state, 1));
  object->~GameObject();
  return 0;
}

int SceneLibrary::attach(lua_State* state)
{
  GameObject* object = static_cast<GameObject*>(lua_touserdata(state, 1));
  Attachable* attachable = static_cast<Attachable*>(lua_touserdata(state, 2));
  if (object && attachable)
  {
    attachable->attach(object);
    Log::info << "Attached to game object '" << object->name() << "'\n";
  }
  return 0;
}

int SceneLibrary::createCamera(lua_State* state)
{
  char const* name = luaL_checkstring(state, 1);
  float fovY = luaL_checknumber(state, 2);
  float nearClip = luaL_checknumber(state, 3);
  float farClip = luaL_checknumber(state, 4);

  Camera* camera = new Camera(fovY, nearClip, farClip);

  Log::info << "Created camera '" << name << "'\n";

  lua_getglobal(state, "Scene");
  lua_getfield(state, -1, "cameras");
  lua_pushlightuserdata(state, camera);
  lua_setfield(state, -2, name);
  lua_pushlightuserdata(state, camera);
  return 1;
}

int SceneLibrary::translate(lua_State* state)
{
  GameObject* object = static_cast<GameObject*>(lua_touserdata(state, 1));
  float x = luaL_checknumber(state, 2);
  float y = luaL_checknumber(state, 3);
  float z = luaL_checknumber(state, 4);
  object->localTransform().translate(x, y, z);

  return 0;
}

int SceneLibrary::addDirectionalLight(lua_State* state)
{
  if ((lua_gettop(state) != 2) || (!lua_istable(state, -2)) || (!lua_istable(state, -1)))
  {
    Log::error << "addDirectionalLight called with the wrong arguments\n";
    return luaL_error(state, " Usage: addDirectionalLight(direction[3], color[4])");
  }

  glm::vec4 color;
  Lua::Utils::parseVec(state, 4, &color[0]);
  lua_pop(state, 1);

  glm::vec3 direction;
  Lua::Utils::parseVec(state, 3, &direction[0]);
  lua_pop(state, 1);

  Light* light = Keeper<Light>::instance().create();
  light->type = Light::DIRECTIONAL;
  light->position = glm::vec4(direction, 0.0f);
  light->getShaderData().color = color;

  return 0;
}

int SceneLibrary::addPointLight(lua_State* state)
{
  if ((lua_gettop(state) != 2) || (!lua_istable(state, -2)) || (!lua_istable(state, -1)))
  {
    return luaL_error(state, " Usage: addPointLight(position[4], color[4])");
  }

  glm::vec4 color;
  Lua::Utils::parseVec(state, 4, &color[0]);
  lua_pop(state, 1);

  glm::vec3 position;
  Lua::Utils::parseVec(state, 3, &position[0]);
  lua_pop(state, 1);

  Light* light = Keeper<Light>::instance().create();
  light->type = Light::POINT;
  light->position = glm::vec4(position, 1);
  light->getShaderData().color = color;

  return 0;
}

int SceneLibrary::addSpotLight(lua_State* state)
{
  if ((lua_gettop(state) != 6) || (!lua_istable(state, -6)) || (!lua_istable(state, -5)) || (!lua_istable(state, -1)))
  {
    return luaL_error(state, " Usage: addSpotLight(position[4], direction[3], exponent, falloff, cutoff, color[4])");
  }

  glm::vec4 color;
  Lua::Utils::parseVec(state, 4, &color[0]);
  lua_pop(state, 1);

  float cutoff = lua_tonumber(state, -1);
  lua_pop(state, 1);

  float falloff = lua_tonumber(state, -1);
  lua_pop(state, 1);

  float exponent = lua_tonumber(state, -1);
  lua_pop(state, 1);

  glm::vec3 direction;
  Lua::Utils::parseVec(state, 3, &direction[0]);
  lua_pop(state, 1);

  glm::vec3 position;
  Lua::Utils::parseVec(state, 3, &position[0]);
  lua_pop(state, 1);

  Light* light = Keeper<Light>::instance().create();
  light->type = Light::SPOT;
  light->position = glm::vec4(position, 1);
  light->spotDirection = direction;
  light->getShaderData().spotCutoff = cutoff;
  light->getShaderData().spotFalloff = falloff;
  light->getShaderData().spotExponent = exponent;
  light->getShaderData().color = color;

  return 0;
}

}
