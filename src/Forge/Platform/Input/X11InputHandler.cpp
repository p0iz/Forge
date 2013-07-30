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
 * Copyright 2013 Tommi Martela
 *
 */

#include "X11InputHandler.hpp"


namespace Forge { namespace Input {

X11InputHandler::X11InputHandler():
  InputHandler(),
  mCurrentWindow(nullptr)
{
}

X11InputHandler::~X11InputHandler()
{
}

void X11InputHandler::setCurrentWindow(Graphics::RenderWindowPtr window)
{
  mCurrentWindow = window;
  // Get window handle and setup X11 events
}

Graphics::RenderWindowPtr const X11InputHandler::getCurrentWindow() const
{
  return mCurrentWindow;
}

void X11InputHandler::capture()
{
  // Subscribe to X11 input events
}

void X11InputHandler::release()
{
  // Unsubscribe from X11 input events
}

bool X11InputHandler::isKeyDown(Key key)
{
  return false;
}

bool X11InputHandler::isKeyUp(Key key)
{
  return false;
}

bool X11InputHandler::isMouseDown(MouseButton mask)
{
  return false;
}

bool X11InputHandler::isMouseUp(MouseButton mask)
{
  return false;
}

int X11InputHandler::getMouseLocX()
{
  return 0;
}

int X11InputHandler::getMouseLocY()
{
  return 0;
}

}}
