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
class InputHandler
{
  public:
    InputHandler();
    virtual ~InputHandler();

    /* Set the window to read events from */
    virtual void setCurrentWindow(Graphics::RenderWindowPtr) = 0;
    virtual Graphics::RenderWindowPtr const getCurrentWindow() const = 0;

    /* Capture must be done before input can be processed */
    virtual void capture() = 0;
    virtual void release() = 0;

    /* Used by e.g. event handler to inject input events */
    void injectKeyDown(Key key);
    void injectKeyUp(Key key);
    void injectMouseMove(int x, int y);
    void injectMouseDown(MouseButton button);
    void injectMouseUp(MouseButton button);

    /* Set the input processor to use for processing captured events */
    void setProcessor(InputProcessor* processor);
    bool process(float const delta);

    bool isKeyPressed(Key key) const;
    bool isKeyDown(Key key) const;
    bool isKeyUp(Key key) const;
    std::unordered_set<Key> const& getActiveKeys() const;
    std::unordered_set<Key> const& getPressedKeys() const; // Cleared after each frame
    bool isMouseClicked(MouseButton mask) const;
    bool isMouseDown(MouseButton mask) const;
    bool isMouseUp(MouseButton mask) const;

    int getMouseX() const;
    int getMouseY() const;
    int getMouseRelX() const;
    int getMouseRelY() const;

    static InputHandler& getInstance();

  private:
    InputProcessor* mProcessor;

    int mMouseRelX;
    int mMouseRelY;
    int mMouseX;
    int mMouseY;

    std::unordered_set<Key> mActiveKeys;
    std::unordered_set<Key> mPressedKeys; // Single-frame container
    MouseButton mActiveButtons;
    MouseButton mClickedButtons; // Single-frame container
    Modifier mActiveModifiers;
};

}}
