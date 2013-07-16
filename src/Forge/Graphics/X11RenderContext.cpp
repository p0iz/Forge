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

#include "X11RenderContext.hpp"

#include "../Util/Log.h"


namespace {
  GLubyte const* CreateContextAttribsName = (GLubyte const*)"glXCreateContextAttribsARB";
}

namespace Forge { namespace Graphics {

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, int const*);

X11RenderContext::X11RenderContext():
  mContext(nullptr),
  mDisplay(nullptr),
  mWindow(0)
{
}

X11RenderContext::~X11RenderContext()
{
  destroy();
}

bool const X11RenderContext::create(Display* display, Window window, GLXFBConfig config)
{
  mDisplay = display;
  mWindow = window;

  glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
      (glXCreateContextAttribsARBProc)glXGetProcAddress(CreateContextAttribsName);
  if (glXCreateContextAttribsARB == nullptr)
  {
    Log::error << "Extension 'glXCreateContextAttribsARB' is unsupported!\n"
                  "Unable to create context. Please upgrade your graphics hardware or drivers.\n";
    return false;
  }

  int contextAttribs[] =
  {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 3,
    None
  };

  mContext = glXCreateContextAttribsARB(mDisplay, config, nullptr, True, contextAttribs);

  XSync(mDisplay, False);

  return mContext != nullptr;
}

void X11RenderContext::destroy()
{
  if (mContext != nullptr)
  {
    glXMakeCurrent(mDisplay, 0, 0);
    glXDestroyContext(mDisplay, mContext);
  }
  mContext = nullptr;
}

bool const X11RenderContext::hasDirectRendering() const
{
  return glXIsDirect(mDisplay, mContext);
}

bool const X11RenderContext::isValid() const
{
  return mContext;
}

void X11RenderContext::makeCurrent()
{
  glXMakeCurrent(mDisplay, mWindow, mContext);
}

}}
