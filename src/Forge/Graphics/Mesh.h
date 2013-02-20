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

#include "DebugAxis.h"
#include "Vertex.h"

#include "Shader/ShaderProgram.h"

#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Forge {

class Mesh
{
public:
	Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<GLuint>& elements);
	~Mesh();
	void draw();
private:
	unsigned int mNumberOfVertices;
	GLuint mVertexArrayId;
	GLuint mVertexBufferId;
	GLuint mElementBufferId;
};

} // namespace Forge

#endif // VERTEXLISTDRAWABLE_H
