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

#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace Forge {

struct Vertex
{
	Vertex(const glm::vec3& p, const glm::vec2& u, const glm::vec3& n)
	{
		position[0] = p[0];
		position[1] = p[1];
		position[2] = p[2];
		uv[0] = u[0];
		uv[1] = u[1];
		normal[0] = n[0];
		normal[1] = n[1];
		normal[2] = n[2];
	}

	glm::float_t position[3];
	glm::float_t uv[2];
	glm::float_t normal[3];
	glm::float_t tangent[3];
	glm::float_t bitangent[3];
};

} // namespace Forge

#endif // VERTEX_H
