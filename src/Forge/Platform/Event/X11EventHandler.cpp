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

Display* X11EventHandler::display = nullptr;

X11EventHandler::X11EventHandler():
  EventHandler()
{
  if (!X11EventHandler::display)
  {
    display = XOpenDisplay(nullptr);
  }

  if (!display)
  {
    Log::error << "Could not open X11 display connection!\n";
  }
  else
  {
    mWmDeleteMessageAtom = XInternAtom(X11EventHandler::display, "WM_DELETE_WINDOW", False);
  }
}

X11EventHandler::~X11EventHandler()
{
  mWindowHandles.clear();
  XCloseDisplay(X11EventHandler::display);
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
    XSetWMProtocols(X11EventHandler::display, handle, &mWmDeleteMessageAtom, 1);
    XEvent event;
    while (XPending(X11EventHandler::display) > 0)
    {
      if (XCheckTypedWindowEvent(X11EventHandler::display, handle, ClientMessage, &event) == True)
      {
        if (event.xclient.data.l[0] == (long)mWmDeleteMessageAtom)
        {
          return false;
        }
      }
      else
      {
        XNextEvent(X11EventHandler::display, &event);
      }
    }
    // Check for closed window
  }
  return true;
}

}}
