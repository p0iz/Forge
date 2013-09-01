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
 * Copyright 2012 Tommi Martela
 *
 */

#pragma once

#include "RenderContext.hpp"

#include <memory>


/* This abstract class provides a contract for implementing a render window
 * for Forge. The function implementations should provide intuitive behaviour
 * with regard to rendering into a window.
 *
 * The constructor should create a OpenGL rendering context that fulfills the
 * RenderContext contract and make it current at the end of the constructor.
 */

#include "Event/Publisher.hpp"
#include "../../Graphics/ResizeEvent.h"

namespace Forge { namespace Graphics {

class RenderWindow;
typedef std::shared_ptr<RenderWindow> RenderWindowPtr;

class RenderWindow : public Publisher<ResizeEvent>
{
  public:
    RenderWindow();
    virtual ~RenderWindow();

    virtual bool const isValid() const = 0;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void setFullscreen(bool const enabled) = 0;
    virtual bool const isFullscreen() const = 0;
    virtual void resize(int width, int height) = 0;

    virtual int width() const = 0;
    virtual int height() const = 0;

    /* This is a context-specific identifier for the render window */
    virtual unsigned long getHandle() = 0;

    virtual void setTitle(char const* title) = 0;

    virtual RenderContext& getContext() = 0;

    /* Use this to get a shared pointer to a new render window.
     * Implement this for each supported platform separately. */
    static RenderWindowPtr createInstance();
};

}}
