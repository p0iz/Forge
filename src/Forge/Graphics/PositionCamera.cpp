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

#include "PositionCamera.h"

#include "Util/Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Forge {

PositionCamera::PositionCamera()
  : mFovY(45.0f),
    mNearClip(1.0f),
    mFarClip(100.0f),
    mDirtyViewProjection(true),
    mProjectionMatrix(1.0f),
    mViewProjectionMatrix(1.0f)
{
}

PositionCamera::~PositionCamera()
{
}

void PositionCamera::setPerspectiveProjection(int width, int height)
{
  mWidth = width;
  mHeight = height;
  mProjectionMatrix = glm::perspective(mFovY, static_cast<float>(width) / height, mNearClip, mFarClip);
}

void PositionCamera::setOrthogonalProjection(int width, int height)
{
  mWidth = width;
  mHeight = height;
  mProjectionMatrix = glm::mat4x4(1.0f);
  mProjectionMatrix[0][0] = 2.0f / width;
  mProjectionMatrix[1][1] = 2.0f / height;
  mProjectionMatrix[2][2] = 1.0f / (mFarClip - mNearClip);
  mProjectionMatrix[3][2] = -mNearClip / (mFarClip - mNearClip);
}

void PositionCamera::setClipDistances(float near, float far) {
  mNearClip = near;
  mFarClip = far;
}

float PositionCamera::getAspectRatio() const
{
  return static_cast<float>(mWidth) / mHeight;
}

const glm::mat4x4& PositionCamera::getProjectionMatrix() const
{
  return mProjectionMatrix;
}

void PositionCamera::setFovY(float fov)
{
  mFovY = fov;
}

float PositionCamera::getFovY() const
{
  return mFovY;
}

void PositionCamera::updateRotation(float yaw, float pitch, float roll)
{
  mRotation.x += glm::radians(yaw);
  mRotation.y -= glm::radians(pitch);
  mRotation.z += glm::radians(roll);
}

const glm::vec3 PositionCamera::getRotation() const
{
  return mRotation;
}

void PositionCamera::setPosition(float x, float y, float z)
{
  mPosition[0] = x;
  mPosition[1] = y;
  mPosition[2] = z;
}

const glm::vec3 PositionCamera::getPosition() const
{
  return mPosition;
}

void PositionCamera::updatePosition(glm::vec3 translation)
{
  mPosition += translation;
}

} // namespace Forge
