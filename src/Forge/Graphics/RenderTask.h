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

#include "Light/Light.hpp"

#include <glm/glm.hpp>

namespace Forge {

class Camera;

class RenderTask
{
public:
	explicit RenderTask(const Camera& camera);

	const Camera& getCamera() const;

	const glm::mat4x4& getWorldTransform() const;

	void setWorldTransform(const glm::mat4x4& worldTransform);

	Light lights[Light::MAX_LIGHTS];

private:
	const Camera& mCamera;
	glm::mat4x4 mWorldTransform;
};

}
