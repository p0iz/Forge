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

#include "X11RenderWindow.hpp"

#include "../Util/Log.h"

#include <GL/gl.h>
#include <GL/glx.h>


namespace Forge { namespace Graphics {

X11RenderWindow::X11RenderWindow():
  RenderWindow(),
  mFullscreen(false),
  mValid(false),
  mColormap(),
  mDisplay(XOpenDisplay(nullptr)),
  mWindow()
{
  if (!mDisplay)
  {
    Log::error << "Could not open XDisplay!\n";
  }

  // Get a matching FB config
  static int visualAttributes[] =
  {
    GLX_X_RENDERABLE    , True,
    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
    GLX_RED_SIZE        , 8,
    GLX_GREEN_SIZE      , 8,
    GLX_BLUE_SIZE       , 8,
    GLX_ALPHA_SIZE      , 8,
    GLX_DEPTH_SIZE      , 24,
    GLX_STENCIL_SIZE    , 8,
    GLX_DOUBLEBUFFER    , True,
    //GLX_SAMPLE_BUFFERS  , 1,
    //GLX_SAMPLES         , 4,
    None
  };

  if (!checkGLXVersion())
  {
    Log::error << "GLX version is not supported\n";
    return;
  }

  int configCount;
  GLXFBConfig* fbConfig =
      glXChooseFBConfig(
        mDisplay,
        DefaultScreen(mDisplay),
        visualAttributes,
        &configCount
      );
  if (!fbConfig)
  {
    Log::error << "Failed to get FB configuration\n";
    return;
  }
  Log::info << "Found " << configCount << " matching configurations.\n";

  int preferredConfigIndex = -1;
  int bestSamples = -1;

  for (int i = 0; i < configCount; ++i)
  {
    XVisualInfo* visualInfo = glXGetVisualFromFBConfig(mDisplay, fbConfig[i]);
    if (visualInfo)
    {
      int samples, buffers;
      glXGetFBConfigAttrib(mDisplay, fbConfig[i], GLX_SAMPLES, &samples);
      glXGetFBConfigAttrib(mDisplay, fbConfig[i], GLX_SAMPLE_BUFFERS, &buffers);

      Log::info << "Visual info -- ID: " << visualInfo->visualid <<
                   " Samples: " << samples <<
                   " Sample buffers: " << buffers << "\n";

      if ((preferredConfigIndex < 0) || (buffers && (samples > bestSamples)))
      {
        bestSamples = samples;
        preferredConfigIndex = i;
      }
    }
    XFree(visualInfo);
  }

  GLXFBConfig preferredConfig = fbConfig[preferredConfigIndex];
  XFree(fbConfig);

  XVisualInfo* visualInfo = glXGetVisualFromFBConfig(mDisplay, preferredConfig);
  Log::info << "Chosen visual ID: " << visualInfo->visualid << "\n";

  XSetWindowAttributes setWindowAttributes;
  mColormap =
      XCreateColormap(
        mDisplay,
        RootWindow(mDisplay, visualInfo->screen),
        visualInfo->visual,
        AllocNone
      );
  setWindowAttributes.colormap = mColormap;
  setWindowAttributes.background_pixmap = None;
  setWindowAttributes.border_pixel = 0;
  setWindowAttributes.event_mask = StructureNotifyMask;

  mWindow =
      XCreateWindow(
        mDisplay,
        RootWindow(mDisplay, visualInfo->screen),
        0,
        0,
        100,
        100,
        0,
        visualInfo->depth,
        InputOutput,
        visualInfo->visual,
        CWBorderPixel|CWColormap|CWEventMask,
        &setWindowAttributes
      );

  if (mWindow == 0)
  {
    Log::error << "Unable to create a window with the selected visuals!\n";
  }
  XFree(visualInfo);

  XStoreName(mDisplay, mWindow, "OpenGL window");

  XMapWindow(mDisplay, mWindow);

  bool createdContext = mContext.create(mDisplay, mWindow, preferredConfig);

  if (!createdContext)
  {
    Log::error << "Failed to create an X11 OpenGL context!\n";
    return;
  }

  if (!mContext.hasDirectRendering())
  {
    Log::error << "Direct rendering is disabled. Performance may suffer.\n";
  }

  mContext.makeCurrent();

  mValid = true;
}

X11RenderWindow::~X11RenderWindow()
{
  XDestroyWindow( mDisplay, mWindow );
  XFreeColormap( mDisplay, mColormap );
  XCloseDisplay( mDisplay );
}

bool const X11RenderWindow::checkGLXVersion() const
{
  int glxMajor, glxMinor;
  Bool accepted = glXQueryVersion(mDisplay, &glxMajor, &glxMinor);
  return (accepted && (glxMajor > 1 || (glxMajor == 1 && glxMinor >= 3)));
}

bool const X11RenderWindow::isValid() const
{
  return mValid;
}

void X11RenderWindow::show()
{
}

void X11RenderWindow::hide()
{
}

void X11RenderWindow::setFullscreen(const bool enabled)
{
  if (enabled != mFullscreen)
  {
    mFullscreen = enabled;
  }
}

void X11RenderWindow::resize(int width, int height)
{

}

RenderContext& X11RenderWindow::getContext()
{
  return mContext;
}


}}
