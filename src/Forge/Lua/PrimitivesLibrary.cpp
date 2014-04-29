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

#include "PrimitivesLibrary.hpp"
#include "Graphics/Mesh.h"
#include "Graphics/Vertex.h"
#include "Lua/UserdataMap.hpp"
#include "Util/Internal/SingleStorage.hpp"
#include <lua.hpp>
#include <vector>


namespace Forge {

PrimitivesLibrary::PrimitivesLibrary()
{
}

PrimitivesLibrary::~PrimitivesLibrary()
{
}

void PrimitivesLibrary::import(lua_State* state)
{
  lua_newtable(state);

  LIB_FUNC(state, createBox);

  std::vector<Mesh*>* meshes = new std::vector<Mesh*>;

  lua_pushlightuserdata(state, meshes);

  lua_setfield(state, -2, "meshes");

  lua_setglobal(state, "Primitives");
}

void PrimitivesLibrary::remove(lua_State* state)
{
  lua_pushnil(state);
  lua_setglobal(state, "Primitives");
}

int PrimitivesLibrary::createBox(lua_State* state)
{
  float width = luaL_checknumber(state, 1);
  float height = luaL_checknumber(state, 2);
  float depth = luaL_checknumber(state, 3);

  std::vector<Vertex> vertices;

  // Generate vertices for each side of the box

  // X
  for (int i = -1; i < 2; i += 2)
  {
    // Y
    for (int j = -1; j < 2; j += 2)
    {
      // Z
      for (int k = -1; k < 2; k += 2)
      {
        vertices.push_back(
          Vertex(
            glm::vec3(width/i, height/j, depth/k),
            glm::vec2(k + 1, j + 1),
            glm::vec3(i, 0, 0)
          )
        );
        vertices.push_back(
          Vertex(
            glm::vec3(width/i, height/j, depth/k),
            glm::vec2(i + 1, k + 1),
            glm::vec3(0, j, 0)
          )
        );
        vertices.push_back(
          Vertex(
            glm::vec3(width/i, height/j, depth/k),
            glm::vec2(i + 1, j + 1),
            glm::vec3(0, 0, k)
          )
        );
      }
    }
  }

  std::vector<GLuint> indices =
  {
    // Lower left back (0-2)
    // Lower left front (3-5)
    // Upper left back (6-8)
    // Upper left front (9-11)
    // Lower right back (12-14)
    // Lower right front (15-17)
    // Upper right back (18-20)
    // Upper right front (21-23)


    0, 3, 9, 9, 6, 0,
    // Bottom
    1, 13, 16, 16, 4, 1,
    // Back
    14, 2, 8, 8, 20, 14,
    // Right
    15, 12, 18, 18, 21, 15,
    // Top
    10, 22, 19, 19, 7, 10,
    // Front
    5, 17, 23, 23, 11, 5

  };

  auto meshes = SingleStorage<Mesh*>::instance();
  meshes.push_back(new Mesh(vertices, indices));
  lua_pushlightuserdata(state, meshes.back());

  return 1;
}

}
