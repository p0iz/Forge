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

#include "EventHandler.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "SDL2/SDL.h"


namespace Forge {

EventHandler::EventHandler(
  InputHandler& input,
  RenderWindow& window
):
  mInput(input),
  mWindow(window)
{
}

bool EventHandler::pumpMessages()
{
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        return false;
      case SDL_KEYDOWN:
        mInput.injectKeyDown(static_cast<Forge::Key>(e.key.keysym.sym));
        break;
      case SDL_KEYUP:
        mInput.injectKeyUp(static_cast<Forge::Key>(e.key.keysym.sym));
        break;
      case SDL_MOUSEMOTION:
        mInput.injectMouseMove(e.motion.x, e.motion.y);
        break;
      case SDL_MOUSEBUTTONDOWN:
        mInput.injectMouseDown(static_cast<Forge::MouseButton>(SDL_BUTTON(e.button.button)));
        break;
      case SDL_MOUSEBUTTONUP:
        mInput.injectMouseDown(static_cast<Forge::MouseButton>(SDL_BUTTON(e.button.button)));
        break;
      case SDL_MOUSEWHEEL:
        mInput.injectMouseWheel(e.wheel.x, e.wheel.y);
        break;
    }
  }
  return true;
}

}
