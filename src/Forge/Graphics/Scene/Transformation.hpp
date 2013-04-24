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

#pragma once

#include <glm/glm.hpp>

namespace Forge {

// A struct that contains a single transformation (translation, scaling and rotation)
// from one space to another.
struct Transformation {
	void translate(float x, float y, float z);
	void scale(float size); // Only allow uniform scaling
	void rotate(float angle, const glm::vec3& axis);
	void reset();
	void applyMatrix(const glm::mat4& matrix);
	const glm::mat4& getMatrix() const;
private:
	glm::mat4 mMatrix;
};

}
