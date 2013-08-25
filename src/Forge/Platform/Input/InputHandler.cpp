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


namespace Forge { namespace Input {

InputHandler::InputHandler():
  mProcessor(nullptr)
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

void InputHandler::setProcessor(InputProcessor* processor)
{
  mProcessor = processor;
}

bool InputHandler::process(float const delta) const
{
  if (mProcessor)
  {
    return mProcessor->process(delta);
  }
  return true;
}

bool InputHandler::isKeyDown(Key key) const
{
  return mActiveKeys.count(key);
}

bool InputHandler::isKeyUp(Key key) const
{
  return !mActiveKeys.count(key);
}

const std::unordered_set<Key>&InputHandler::getActiveKeys() const
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

int InputHandler::getMouseX() const
{
  return mMouseX;
}

int InputHandler::getMouseY() const
{
  return mMouseY;
}

}}


