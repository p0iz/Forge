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

#include "RenderContext.hpp"

#include <GL/glx.h>


namespace Forge { namespace Graphics {

class X11RenderContext : public RenderContext
{
  public:
    X11RenderContext();
    virtual ~X11RenderContext();

    bool const create(Display* display, Window window, GLXFBConfig config);
    void destroy();
    bool const hasDirectRendering() const;

    virtual bool const isValid() const;
    virtual void makeCurrent();
    virtual void swapBuffers();

  private:
    GLXContext mContext;
    Display* mDisplay;
    Window mWindow;
};

}}
