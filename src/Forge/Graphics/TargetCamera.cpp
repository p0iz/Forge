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

#include "TargetCamera.h"

#include <glm/gtx/vector_angle.hpp>

namespace Forge {

void Forge::TargetCamera::setPosition(float x, float y, float z)
{
	mPosition[0] = x;
	mPosition[1] = y;
	mPosition[2] = z;
}


void Forge::TargetCamera::setTarget(float x, float y, float z)
{
	mTarget[0] = x;
	mTarget[1] = y;
	mTarget[2] = z;
}

const glm::mat4x4 TargetCamera::getViewMatrix() const
{
	return glm::lookAt(glm::vec3(mPosition[0], mPosition[1], mPosition[2]),
			glm::vec3(mTarget[0], mTarget[1], mTarget[2]),
			glm::vec3(0, 1, 0));
}

}
