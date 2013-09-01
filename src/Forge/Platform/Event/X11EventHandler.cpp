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

#include "X11EventHandler.hpp"

#include "../../Util/Log.h"


namespace Forge { namespace Event {

X11EventHandler::XDisplayConnection X11EventHandler::display;

X11EventHandler::X11EventHandler():
  EventHandler(),
  mInputHandler(Input::InputHandler::getInstance())
{
  mWmDeleteMessageAtom = XInternAtom(X11EventHandler::display, "WM_DELETE_WINDOW", False);
}

X11EventHandler::~X11EventHandler()
{
  mWindowHandles.clear();
}

void X11EventHandler::registerWindow(Graphics::RenderWindowPtr window)
{
  mWindowHandles.insert(window->getHandle());
}

void X11EventHandler::deregisterWindow(Graphics::RenderWindowPtr window)
{
  mWindowHandles.erase(window->getHandle());
}

bool X11EventHandler::pumpMessages()
{
  for (unsigned long handle : mWindowHandles)
  {
    XSetWMProtocols(display, handle, &mWmDeleteMessageAtom, 1);
    XEvent event;
    while (XPending(display) > 0)
    {
      if (XCheckTypedWindowEvent(display, handle, ClientMessage, &event) == True)
      {
        if (event.xclient.data.l[0] == (long)mWmDeleteMessageAtom)
        {
          return false;
        }
      }
      else
      {
        XNextEvent(display, &event);
        switch (event.type)
        {
          case ConfigureNotify:
            break;
          case KeyPress:
            mInputHandler.injectKeyDown(static_cast<Key>(event.xkey.keycode));
            break;
          case KeyRelease:
            mInputHandler.injectKeyUp(static_cast<Key>(event.xkey.keycode));
            break;
          case MotionNotify:
            mInputHandler.injectMouseMove(event.xmotion.x, event.xmotion.y);
            break;
          case ButtonPress:
            mInputHandler.injectMouseDown(static_cast<MouseButton>(event.xbutton.button));
            break;
          case ButtonRelease:
            mInputHandler.injectMouseUp(static_cast<MouseButton>(event.xbutton.button));
            break;
          default:
            break;
        }
      }
    }
    // Check for closed window
  }
  return true;
}

}}
