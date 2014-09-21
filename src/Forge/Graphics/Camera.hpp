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

#pragma once

#include "GameObject/Attachable.hpp"
#include "Util/Math.hpp"


namespace Forge {

class Viewport;

class GameObject;

class Camera : public Attachable
{
  public:
    explicit Camera(
      float fovY = 45.0f,
      float nearClip = 1.0f,
      float farClip = 100.0f);

    void lookAt(GameObject* target);

    void setFovY(float fovY);

    void setClip(float near, float far);

    glm::mat4 view() const;

    glm::mat4 projection(Viewport const& viewport) const;

  private:
    float mFovY;
    float mNearClip;
    float mFarClip;

    GameObject* mTarget;
};

}
