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

#include "InputHandler.hpp"
#include "Util/Log.h"


namespace Forge {

InputHandler::InputHandler():
  mMouseRelX(0),
  mMouseRelY(0),
  mMouseX(0),
  mMouseY(0),
  mMouseWheelX(0),
  mMouseWheelY(0),
  mActiveKeys(),
  mActiveButtons(),
  mActiveModifiers()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::injectKeyDown(Key key)
{
  mActiveKeys.insert(key);
}

void InputHandler::injectKeyUp(Key key)
{
  mActiveKeys.erase(key);
}

void InputHandler::injectMouseMove(int x, int y)
{
  mMouseRelX = x - mMouseX;
  mMouseRelY = y - mMouseY;
  mMouseX = x;
  mMouseY = y;
}

void InputHandler::injectMouseDown(MouseButton button)
{
  mActiveButtons = static_cast<MouseButton>(mActiveButtons | button);
}

void InputHandler::injectMouseUp(MouseButton button)
{
  mActiveButtons = static_cast<MouseButton>(mActiveButtons & ~button);
}

void InputHandler::injectMouseWheel(int x, int y)
{

}

bool InputHandler::isKeyDown(Key key) const
{
  return mActiveKeys.count(key);
}

bool InputHandler::isKeyUp(Key key) const
{
  return !mActiveKeys.count(key);
}

std::unordered_set<Key> const& InputHandler::getActiveKeys() const
{
  return mActiveKeys;
}

bool InputHandler::isMouseDown(MouseButton mask) const
{
  return mActiveButtons & mask;
}

bool InputHandler::isMouseUp(MouseButton mask) const
{
  return (mActiveButtons & mask) == 0;
}

int InputHandler::getMouseWheelX()
{
  int temp = mMouseWheelX;
  mMouseWheelX = 0;
  return temp;
}

int InputHandler::getMouseWheelY()
{
  int temp = mMouseWheelY;
  mMouseWheelY = 0;
  return temp;
}

int InputHandler::getMouseX() const
{
  return mMouseX;
}

int InputHandler::getMouseY() const
{
  return mMouseY;
}

int InputHandler::getMouseRelX() const
{
  return mMouseRelX;
}

int InputHandler::getMouseRelY() const
{
  return mMouseRelY;
}

}


