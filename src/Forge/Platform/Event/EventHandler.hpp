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

#include "Platform/Window/RenderWindow.hpp"


namespace Forge { namespace Event {

class EventHandler
{
  public:
    EventHandler();
    virtual ~EventHandler() { }

    virtual void registerWindow(Graphics::RenderWindowPtr window) = 0;
    virtual void deregisterWindow(Graphics::RenderWindowPtr window) = 0;

    virtual bool pumpMessages() = 0;

    static EventHandler& getInstance();
};

}}
