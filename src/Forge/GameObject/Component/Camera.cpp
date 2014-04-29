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
#include "Graphics/Viewport.hpp"
#include <glm/gtc/matrix_transform.hpp>


namespace Forge {

Camera::Camera(float fovY, float nearClip, float farClip):
  Component(),
  mFovY(fovY),
  mNearClip(nearClip),
  mFarClip(farClip)
{
}

glm::mat4 Camera::view() const
{
  return owner().transform().getMatrix();
}

glm::mat4 Camera::projection(Viewport const& viewport) const
{
  return glm::perspective(mFovY, viewport.aspectRatio(), mNearClip, mFarClip);
}

}
