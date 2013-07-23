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

namespace Forge { namespace Input {

/* Base class for platform-specific implementations */

/* TODO: Split into input capture (platform) and input processing (application) */

class InputHandler
{
  public:
    InputHandler(RenderWindowPtr window = nullptr);
    virtual ~InputHandler();

    virtual void setCurrentWindow(RenderWindowPtr) = 0;
    RenderWindowPtr const getCurrentWindow() const;

    /* Capture must be done before input can be processed */
    void captureAll();
    virtual void captureMouse() = 0;
    virtual void captureKeyboard() = 0;

    /* Implement input handling here */
    virtual void processInput() = 0;

    /*
     * isKeyDown
     * isKeyUp
     * isMouseDown
     * isMouseUp
     * getMouseLoc
     */
  private:
    RenderWindowPtr mCurrentWindow;
};

}}
