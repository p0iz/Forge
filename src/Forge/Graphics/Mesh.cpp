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

#include "Mesh.h"
#include "Vertex.h"

#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace Forge {

Mesh::Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<GLuint>& elements)
	: mNumberOfVertices(elements.size()),
	  mVertexArrayId(0),
	  mVertexBufferId(0)
{
	const size_t vertexSize = sizeof(Vertex);

	// Generate vertex array and buffers
	glGenVertexArrays(1, &mVertexArrayId);
	glGenBuffers(1, &mVertexBufferId);

	glBindVertexArray(mVertexArrayId);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexSize*vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Positional attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glEnableVertexAttribArray(0);

	// Texture coordinate attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, &(((Vertex*)0)->texcoord));
	glEnableVertexAttribArray(1);

	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexSize, &(((Vertex*)0)->normal));
	glEnableVertexAttribArray(2);

	// Tangent attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertexSize, &(((Vertex*)0)->tangent));
	glEnableVertexAttribArray(3);

	// Bitangent attribute
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertexSize, &(((Vertex*)0)->bitangent));
	glEnableVertexAttribArray(4);

	glGenBuffers(1, &mElementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferId);

	glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				sizeof(elements[0])*elements.size(),
				&elements[0],
				GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, & mVertexBufferId);

	// Delete index buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &mElementBufferId);

	// Delete vertex array
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void Mesh::draw()
{
	glBindVertexArray(mVertexArrayId);

	glDrawElements(GL_TRIANGLES, mNumberOfVertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

} // namespace Forge
