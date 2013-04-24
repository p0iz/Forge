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

#pragma once

#include <glm/glm.hpp>

namespace Forge {

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void setPerspectiveProjection(int width, int height);
	void setOrthogonalProjection(int width, int height);

	virtual const glm::mat4x4 getViewMatrix() const = 0;

	void setFovY(float fov);
	void setClipDistances(float near, float far);

	const glm::mat4x4& getProjectionMatrix() const
	{
		return mProjectionMatrix;
	}

	// Call this whenever you need a fresh VP (e.g. each frame)
	void updateViewProjectionMatrix();

	void updatePosition(glm::vec3 translation);
	void updateRotation(float yaw = 0, float pitch = 0, float roll = 0);

	const glm::vec3 getRotation() const
	{
		return mRotation;
	}

	const glm::vec3 getPosition() const
	{
		return mPosition;
	}

private:

	float mFovY;
	float mNearClip;
	float mFarClip;

	glm::vec3 mRotation;
	glm::vec3 mPosition;

	bool mDirtyViewProjection;

	glm::mat4x4 mViewMatrix;
	glm::mat4x4 mProjectionMatrix;
	glm::mat4x4 mViewProjectionMatrix;
};

} // namespace Forge

