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

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Forge {

Camera::Camera()
	: mDirtyViewProjection(true),
	  mProjectionMatrix(1.0f),
	  mViewProjectionMatrix(1.0f)
{
}

Camera::~Camera()
{
}

void Camera::setPerspectiveProjection(float fovy, int width, int height, float near, float far)
{
	mProjectionMatrix = glm::perspective(fovy, 1.0f*width / height, near, far);

	mDirtyViewProjection = true;
}

void Camera::setOrthogonalProjection(int width, int height, float near, float far)
{
	mProjectionMatrix = glm::mat4x4(1.0f);
	mProjectionMatrix[0][0] = 2.0f / width;
	mProjectionMatrix[1][1] = 2.0f / height;
	mProjectionMatrix[2][2] = 1.0f / (far - near);
	mProjectionMatrix[3][2] = -near / (far -near);

	mDirtyViewProjection = true;
}

void Camera::updateRotation(float yaw, float pitch, float roll)
{
	mRotation.x += glm::radians(yaw);
	mRotation.y -= glm::radians(pitch);
	mRotation.z += glm::radians(roll);
	mDirtyViewProjection = true;
}

void Camera::updatePosition(glm::vec3 translation)
{
	mPosition += translation;
	mDirtyViewProjection = true;
}

void Camera::updateViewProjectionMatrix()
{
	if (mDirtyViewProjection)
	{
		mViewProjectionMatrix = mProjectionMatrix * getViewMatrix();
		mDirtyViewProjection = false;
	}
}

} // namespace Forge
