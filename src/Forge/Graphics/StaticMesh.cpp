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
 * Copyright 2012 Tommi Martela
 *
 */

#include "StaticMesh.h"
#include "Vertex.h"

#include "Util/Log.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace Forge {

StaticMesh::StaticMesh():
  mNumberOfVertices(0),
  mVertexArrayId(0),
  mVertexBufferId(0)
{
}

StaticMesh::StaticMesh(
    const std::vector<Vertex>& vertices,
    const std::vector<GLuint>& elements)
  : mNumberOfVertices(elements.size()),
    mVertexArrayId(0),
    mVertexBufferId(0)
{
  // Generate vertex and element buffers
  glGenBuffers(1, &mVertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &mElementBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferId);
  glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(elements[0])*elements.size(),
      &elements[0],
      GL_STATIC_DRAW);

  glFlush();

  calculateBounds(vertices);
}

StaticMesh::~StaticMesh()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, & mVertexBufferId);

  // Delete index buffer object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &mElementBufferId);

  // Delete vertex array
  glDeleteVertexArrays(1, &mVertexArrayId);
}

void StaticMesh::draw()
{
  if (mNumberOfVertices == 0)
  {
    return;
  }

  if (mVertexArrayId == 0)
  {
    createVAO();
  }

  int currentVertexArray;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVertexArray);
  if (static_cast<unsigned int>(currentVertexArray) != mVertexArrayId) {
    glBindVertexArray(mVertexArrayId);
  }
  glDrawElements(GL_TRIANGLES, mNumberOfVertices, GL_UNSIGNED_INT, 0);
}

void StaticMesh::calculateBounds(const std::vector<Vertex>& vertices)
{
  mBounds = { 0, 0, 0, 0, 0, 0 };
  for (const Vertex& vertex : vertices)
  {
    mBounds.minX = vertex.position[0] < mBounds.minX ? vertex.position[0] : mBounds.minX;
    mBounds.maxX = vertex.position[0] > mBounds.maxX ? vertex.position[0] : mBounds.maxX;
    mBounds.minY = vertex.position[1] < mBounds.minY ? vertex.position[1] : mBounds.minY;
    mBounds.maxY = vertex.position[1] > mBounds.maxY ? vertex.position[1] : mBounds.maxY;
    mBounds.minZ = vertex.position[2] < mBounds.minZ ? vertex.position[2] : mBounds.minZ;
    mBounds.maxZ = vertex.position[2] > mBounds.maxZ ? vertex.position[2] : mBounds.maxZ;
  }
}

void StaticMesh::createVAO()
{
  glGenVertexArrays(1, &mVertexArrayId);
  glBindVertexArray(mVertexArrayId);

  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

  // Positional attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);

  // Texture coordinate attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(((Vertex*)0)->texcoord));
  glEnableVertexAttribArray(1);

  // Normal attribute
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(((Vertex*)0)->normal));
  glEnableVertexAttribArray(2);

  // Tangent attribute
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(((Vertex*)0)->tangent));
  glEnableVertexAttribArray(3);

  // Bitangent attribute
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(((Vertex*)0)->bitangent));
  glEnableVertexAttribArray(4);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferId);

  glBindVertexArray(0);
}

} // namespace Forge
