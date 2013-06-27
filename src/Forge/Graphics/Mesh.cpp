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

Mesh::Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& elements)
	: mNumberOfVertices(static_cast<int>(elements.size()))
{
	const size_t vertexSize = sizeof(Vertex);

	// Generate vertex array and buffers
	mVertexArray.create();
	mVertexBuffer.create(Buffer::Target::VERTEX_BUFFER);

	mVertexArray.bind();

	mVertexBuffer.bind();
	mVertexBuffer.setData(vertexSize*vertices.size(), &vertices[0], Buffer::Usage::STATIC_DRAW);

	// Positional attribute
	mVertexArray.setAttribute(0, 3, VertexArray::ElementType::FLOAT, false, vertexSize, 0);
	mVertexArray.enableAttribute(0);

	// Texture coordinate attribute
	mVertexArray.setAttribute(1,
							  3,
							  VertexArray::ElementType::FLOAT,
							  false,
							  vertexSize,
							  (void*)offsetof(Vertex, texcoord));
	mVertexArray.enableAttribute(1);

	// Normal attribute
	mVertexArray.setAttribute(2,
							  3,
							  VertexArray::ElementType::FLOAT,
							  false,
							  vertexSize,
							  (void*)offsetof(Vertex, normal));
	mVertexArray.enableAttribute(2);

	// Tangent attribute
	mVertexArray.setAttribute(3,
							  3,
							  VertexArray::ElementType::FLOAT,
							  false,
							  vertexSize,
							  (void*)offsetof(Vertex, tangent));
	mVertexArray.enableAttribute(3);

	// Bitangent attribute
	mVertexArray.setAttribute(4,
							  3,
							  VertexArray::ElementType::FLOAT,
							  false,
							  vertexSize,
							  (void*)offsetof(Vertex, bitangent));
	mVertexArray.enableAttribute(4);

	mElementBuffer.create(Buffer::Target::ELEMENT_BUFFER);
	mElementBuffer.bind();
	mElementBuffer.setData(sizeof(elements[0])*elements.size(),
			&elements[0],
			Buffer::Usage::STATIC_DRAW);

	mVertexArray.release();

	calculateBounds(vertices);
}

Mesh::~Mesh()
{
	mVertexArray.destroy();
	mVertexBuffer.destroy();
	mElementBuffer.destroy();
}

void Mesh::draw()
{
	mVertexArray.bind();
	glDrawElements(GL_TRIANGLES, mNumberOfVertices, GL_UNSIGNED_INT, 0);
}

void Mesh::calculateBounds(const std::vector<Vertex>& vertices)
{
	mBounds.minX = 0;
	mBounds.maxX = 0;
	mBounds.minY = 0;
	mBounds.maxY = 0;
	mBounds.minZ = 0;
	mBounds.maxZ = 0;

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

} // namespace Forge
