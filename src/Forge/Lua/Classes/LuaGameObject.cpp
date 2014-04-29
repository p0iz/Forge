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

#include "LuaGameObject.hpp"
#include "Application/Application.hpp"
#include "GameObject/GameObject.hpp"
#include "Util/Internal/Keeper.hpp"
#include <lua.hpp>


namespace Forge {

namespace {
  Application* a;
}

LuaGameObject::LuaGameObject(Application& app):
  LuaClass("GameObject")
{
  // This should not change during the program execution
  a = &app;
}

LuaCFunction LuaGameObject::getCtorFn()
{
  return [](lua_State* state) mutable -> int
  {
    GameObject* go = a->objects().create();

    /* Get the game object components and children */
    luaL_checktype(state, 1, LUA_TTABLE);
    lua_pushnil(state);
    while (lua_next(state, -2))
    {
      /* Unnamed values are components */
      switch (lua_type(state, -1))
      {
        case LUA_TUSERDATA:
        {
          if (luaL_testudata(state, -1, "Transform.meta"))
          {
            go->localTransform() = **static_cast<Transformation**>(lua_touserdata(state, -1));
          }
          else if (luaL_testudata(state, -1, "GameObject.meta"))
          {
            return luaL_error(state, "Child game objects must be defined within a table!");
          }
          else
          {
            Component* c = *static_cast<Component**>(lua_touserdata(state, -1));
            go->addComponent(c);
          }
          break;
        }
        case LUA_TTABLE:
        {
          lua_pushnil(state);
          while (lua_next(state, -2))
          {
            if (luaL_testudata(state, -1, "GameObject.meta"))
            {
              lua_getmetatable(state, -1);
              return luaL_error(state, "A non-GameObject was found within a child table!");
            }
            GameObject* child =
                *static_cast<GameObject**>(luaL_checkudata(state, -1, "GameObject"));
            lua_pop(state, 1);
            go->addChild(child);
          }
          break;
        }
      }
      lua_pop(state, 1);
    }
    lua_pop(state, 1);

    GameObject** userdata = static_cast<GameObject**>(lua_newuserdata(state, sizeof(GameObject**)));
    *userdata = go;

    luaL_getmetatable(state, "GameObject");
    lua_setmetatable(state, -2);

    return 1;
  };
}

LuaCFunction LuaGameObject::getDtorFn()
{
  return [](lua_State* state) mutable -> int
  {
    //GameObject* go = *static_cast<GameObject**>(luaL_checkudata(state, -1, "GameObject"));
    return 0;
  };
}

void LuaGameObject::addClassContent(lua_State* state)
{
}

}
