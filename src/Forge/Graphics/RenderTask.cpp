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

#include "RenderTask.h"

#include "Camera.h"

namespace Forge {

RenderTask::RenderTask(const Camera& camera)
	: mCamera(camera)
{
}

const Camera& RenderTask::getCamera() const
{
	return mCamera;
}

const glm::mat4x4& RenderTask::getWorldTransform() const
{
	return mWorldTransform;
}

void RenderTask::setWorldTransform(const glm::mat4x4& worldTransform)
{
	mWorldTransform = worldTransform;
}

}
