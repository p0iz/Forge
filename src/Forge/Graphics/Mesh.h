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

#ifndef VERTEXLISTDRAWABLE_H
#define VERTEXLISTDRAWABLE_H

#include "Vertex.h"

#include "Shader/ShaderProgram.h"
#include "Scene/Attachable.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

namespace Forge {

class Mesh : public Attachable
{
  public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& elements);
    ~Mesh();
    void draw();

    void setName(std::string const& name);
    std::string const& getName() const;

  private:
    typedef std::vector<Vertex> VertexList;
    typedef std::vector<GLuint> IndexList;

    VertexList _vertices;
    IndexList _indices;

    std::string mName;
    unsigned int mNumberOfVertices;
    GLuint mVertexArrayId;
    GLuint mVertexBufferId;
    GLuint mElementBufferId;

    void calculateBounds(const std::vector<Vertex>& vertices);

    void createBuffers();
    void destroyBuffers();

    void createVAO();
    void destroyVAO();


    struct Bounds
    {
        float minX;
        float maxX;
        float minY;
        float maxY;
        float minZ;
        float maxZ;
    };

    Bounds mBounds;
};

typedef std::shared_ptr<Mesh> MeshPtr;

} // namespace Forge

#endif // VERTEXLISTDRAWABLE_H
