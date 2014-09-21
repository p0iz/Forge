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
 * Copyright 2014 Tommi Martela
 *
 */

#include "Camera.hpp"
#include "GameObject/GameObject.hpp"
#include "Platform/Window/RenderWindow.hpp"
#include "Viewport.hpp"
#include "Util/Math.hpp"


namespace Forge {

Camera::Camera(float fovY, float nearClip, float farClip):
  Attachable(),
  mFovY(fovY),
  mNearClip(nearClip),
  mFarClip(farClip),
  mTarget(nullptr)
{
}

void Camera::lookAt(GameObject* target)
{
  mTarget = target;
}

glm::mat4 Camera::view() const
{
  if (!attachedTo())
  {
    return glm::mat4();
  }

  // Create a view matrix here
  glm::vec3 camera(attachedTo()->transform().position());
  glm::vec3 target(mTarget ? mTarget->transform().position() : camera + glm::vec3(0,0,1));
  return glm::lookAt(camera, target, glm::vec3(0,1,0));
}

glm::mat4 Camera::projection(Viewport const& viewport) const
{
  return glm::perspective(mFovY, viewport.aspectRatio(), mNearClip, mFarClip);
}

}
