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

#include "../Window/RenderWindow.hpp"
#include "InputProcessor.hpp"
#include "KeySymbols.hpp"
#include "MouseButtons.hpp"

#include <memory>


namespace Forge { namespace Input {

/* Base class for platform-specific implementations */

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

class InputHandler
{
  public:
    InputHandler();
    virtual ~InputHandler();

    virtual void setCurrentWindow(Graphics::RenderWindowPtr) = 0;
    virtual Graphics::RenderWindowPtr const getCurrentWindow() const = 0;

    /* Capture must be done before input can be processed */
    virtual void capture() = 0;
    virtual void release() = 0;

    void setProcessor(InputProcessor* processor);
    void process(float const delta) const;

    virtual bool isKeyDown(Key key) = 0;
    virtual bool isKeyUp(Key key) = 0;
    virtual bool isMouseDown(MouseButton mask) = 0;
    virtual bool isMouseUp(MouseButton mask) = 0;

    virtual int getMouseLocX() = 0;
    virtual int getMouseLocY() = 0;

    static InputHandlerPtr createInstance();
  private:
    InputProcessor* mProcessor;
};

}}
