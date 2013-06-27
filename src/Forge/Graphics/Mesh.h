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

#include "OpenGL/Buffer.hpp"
#include "OpenGL/VertexArray.hpp"

#include "Scene/Attachable.hpp"

#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

namespace Forge {

class Mesh : public Attachable
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements);
	~Mesh();
	void draw();
private:
	const int mNumberOfVertices;
	VertexArray mVertexArray;
	Buffer mVertexBuffer;
	Buffer mElementBuffer;

	void calculateBounds(const std::vector<Vertex>& vertices);

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
