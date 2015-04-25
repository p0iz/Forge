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

#include "Viewport.hpp"
#include "GameObject/Component/Camera.hpp"
#include "Window/RenderWindow.hpp"
#include "Util/Math.hpp"

#include <GL/glew.h>


namespace Forge {

Viewport::Viewport(Forge::RenderWindow const& window, float x, float y, float width, float height):
  mWindow(window),
  mX(x),
  mY(y),
  mWidth(width),
  mHeight(height)
{
}

void Viewport::setSize(float x, float y, float width, float height)
{
  mX = x;
  mY = y;
  mWidth = width;
  mHeight = height;
}

int Viewport::x() const
{
  return mX * mWindow.width();
}

int Viewport::y() const
{
  return mY * mWindow.height();
}

int Viewport::width() const
{
  return mWidth * mWindow.width();
}

int Viewport::height() const
{
  int height = mHeight * mWindow.height();
  return height > 0 ? height : 1;
}

float Viewport::aspectRatio() const
{
  return (mWidth * mWindow.width()) / (mHeight * mWindow.height());
}

void Viewport::updateGLViewport() const
{
  int posX = x();
  int posY = y();
  int width = this->width();
  int height = this->height();

  glViewport(posX, posY, width, height);
  glScissor(posX, posY, width, height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Camera const* Viewport::camera() const
{
  return _camera;
}

void Viewport::setCamera(Camera const* camera)
{
  _camera = camera;
}

}
