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

Transformation::Transformation() : mScale(1.0f) { }

Transformation& Transformation::translate(float x, float y, float z)
{
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, z));
	return *this;
}

Transformation& Transformation::setPosition(float x, float y, float z)
{
	mMatrix[3] = glm::vec4(x, y, z, mMatrix[3][3]);
	return *this;
}

Transformation& Transformation::scale(float size)
{
	mScale *= size;
	return *this;
}

Transformation& Transformation::rotate(float angle, const glm::vec3 &axis)
{
	mMatrix = glm::rotate(mMatrix, angle, axis);
	return *this;
}

void Transformation::reset()
{
	mMatrix = glm::mat4();
	mScale = 1.0f;
}

Transformation& Transformation::applyMatrix(const glm::mat4& matrix)
{
	mMatrix = matrix * mMatrix;
	return *this;
}

glm::mat4 Transformation::getMatrix() const
{
	glm::mat4x4 result(mMatrix);
	result[0] *= mScale;
	result[1] *= mScale;
	result[2] *= mScale;
	return result;
}

}
