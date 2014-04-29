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

Transformation::Transformation(float x, float y, float z):
  mMatrix(glm::translate(glm::mat4(), glm::vec3(x,y,z)))
{
}

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

glm::vec3 Transformation::position() const
{
  return glm::vec3(mMatrix[3]);
}

Transformation& Transformation::scale(float size)
{
  mMatrix = glm::scale(mMatrix, glm::vec3(size));
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
}

Transformation& Transformation::applyMatrix(const glm::mat4& matrix)
{
  mMatrix = matrix * mMatrix;
  return *this;
}

glm::mat4 Transformation::getMatrix() const
{
  return mMatrix;
}

Transformation operator*(Transformation const& lhs, Transformation const& rhs)
{
  Transformation t;
  t.mMatrix = lhs.mMatrix * rhs.mMatrix;
  return t;
}

}
