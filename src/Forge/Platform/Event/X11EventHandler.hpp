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

#pragma once

#include "EventHandler.hpp"
#include "../Input/InputHandler.hpp"
#include <unordered_set>

#include <X11/Xlib.h>


namespace Forge { namespace Event {

class X11EventHandler : public EventHandler
{
  public:
    X11EventHandler();
    virtual ~X11EventHandler();

    virtual void registerWindow(Graphics::RenderWindowPtr window);
    virtual void deregisterWindow(Graphics::RenderWindowPtr window);

    virtual bool pumpMessages();

    static Display* display;
  private:
    Input::InputHandler& mInputHandler;

    std::unordered_set<unsigned long> mWindowHandles;

    // Used to catch the WM closing the window
    Atom mWmDeleteMessageAtom;
};

}}
