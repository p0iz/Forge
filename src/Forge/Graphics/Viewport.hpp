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

#include "Util/Math.hpp"


namespace Forge
{

class Camera;

class RenderWindow;

class Viewport
{
  public:
    // The x, y, width and height are in percentages of total window area
    explicit Viewport(
      RenderWindow const& window,
      float x = 0.0f,
      float y = 0.0f,
      float width = 1.0f,
      float height = 1.0f
    );

    void setSize(float x, float y, float width, float height);

    int x() const;

    int y() const;

    int width() const;

    int height() const;

    float aspectRatio() const;

    void setCamera(Camera const* camera);

    bool hasCamera() const;

    glm::mat4 view() const;

    glm::mat4 projection() const;

  private:
    RenderWindow const& mWindow;
    Camera const* mCamera;

    float mX;
    float mY;
    float mWidth;
    float mHeight;
};

}
