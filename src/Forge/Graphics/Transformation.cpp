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

#include "Transformation.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Forge {

const glm::mat4x4 Transformation::getWorldMatrix() const
{
	return modelMatrix * rotationMatrix;
}

void Transformation::translate(float x, float y, float z)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}

void Transformation::scale(float size)
{
	modelMatrix = glm::scale(modelMatrix, glm::vec3(size, size, size));
}

void Transformation::rotate(float angle, const glm::vec3 &axis)
{
	rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
}

void Transformation::reset()
{
	modelMatrix = glm::mat4x4();
	rotationMatrix = glm::mat4x4();
}

}
