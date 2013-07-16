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

#include "RenderWindow.hpp"
#include "X11RenderContext.hpp"

#include <memory>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


namespace Forge { namespace Graphics {

class X11RenderWindow : public RenderWindow
{
  public:
    X11RenderWindow();
    virtual ~X11RenderWindow();

    virtual bool const isValid() const;
    virtual void show();
    virtual void hide();
    virtual void setFullscreen(bool const enabled);
    virtual void resize(int width, int height);

    RenderContext& getContext();

  private:
    bool const checkGLXVersion() const;

    bool mFullscreen;
    bool mValid;
    X11RenderContext mContext;
    Colormap mColormap;
    Display* mDisplay;
    Window mWindow;
};

}}
