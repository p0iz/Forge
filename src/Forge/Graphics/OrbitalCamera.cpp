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

#include "OrbitalCamera.h"

#include <glm/gtx/vector_angle.hpp>

#include <iostream>

namespace Forge {

OrbitalCamera::OrbitalCamera(float radius)
	: mRadius(radius)
{
}

void OrbitalCamera::setRadius(float radius)
{
	mRadius = radius;
}

const glm::mat4x4 OrbitalCamera::getViewMatrix() const
{
	glm::vec3 rotation = getRotation();
	glm::vec3 target = getPosition();
	glm::vec3 camera(
		cos(rotation.x) * sin(rotation.y) * mRadius + target.x,
		cos(rotation.y) * mRadius + target.y,
		sin(rotation.x) * sin(rotation.y) * mRadius + target.z);

	glm::vec3 right(
		cos(rotation.x + glm::radians(90.0f)),
		0,
		sin(rotation.x + glm::radians(90.0f)));
	return glm::lookAt(camera, target, glm::cross(-camera, right));
}





} // namespace Forge
