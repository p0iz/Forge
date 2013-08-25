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

#include "../Event/X11EventHandler.hpp"
#include "../../Util/Log.h"

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>


namespace Forge { namespace Graphics {

X11RenderWindow::X11RenderWindow():
  RenderWindow(),
  mValid(false),
  mDesktopModeInfo(),
  mWidth(0),
  mHeight(0),
  mFullscreen(false),
  mContext(),
  mColormap(),
  mDisplay(nullptr),
  mWindow(),
  mTitle("Forge OpenGL window")
{
}

X11RenderWindow::~X11RenderWindow()
{
  destroy();
}

void X11RenderWindow::create()
{
  if (mValid)
    return;

  mDisplay = Event::X11EventHandler::display;
  if (!mDisplay)
  {
    Log::error << "X11 event handling not yet started! Failed to open window.\n";
    return;
  }

  if (!checkGLXVersion())
  {
    Log::error << "GLX version is not supported\n";
    return;
  }

  GLXFBConfig preferredConfig = getPreferredFrameBufferConfig();

  if (preferredConfig == nullptr)
  {
    Log::error << "Could not get a framebuffer config!\n";
    return;
  }

  createWindow(preferredConfig);

  if (!mWindow)
  {
    Log::error << "Unable to create a window with the selected visuals!\n";
    return;
  }

  if (mFullscreen)
  {
    grabFullscreenInput();
  }
  else
  {
    XStoreName(mDisplay, mWindow, mTitle);
  }

  if (!mContext.create(mDisplay, mWindow, preferredConfig))
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

bool const X11RenderWindow::checkGLXVersion() const
{
  int glxMajor, glxMinor;
  Bool accepted = glXQueryVersion(mDisplay, &glxMajor, &glxMinor);
  return (accepted && (glxMajor > 1 || (glxMajor == 1 && glxMinor >= 3)));
}

GLXFBConfig X11RenderWindow::getPreferredFrameBufferConfig()
{
  GLXFBConfig preferredConfig = nullptr;

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
    None
  };

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
    Log::error << "Failed to get framebuffer configuration list\n";
    return nullptr;
  }

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

      if ((preferredConfigIndex < 0) || (buffers && (samples > bestSamples)))
      {
        bestSamples = samples;
        preferredConfigIndex = i;
      }
    }
    XFree(visualInfo);
  }

  preferredConfig = fbConfig[preferredConfigIndex];

  XFree(fbConfig);

  return preferredConfig;
}

void X11RenderWindow::createWindow(GLXFBConfig preferredConfig)
{
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
  setWindowAttributes.event_mask = ExposureMask|KeyPressMask|ButtonPressMask|StructureNotifyMask;

  if (mFullscreen)
  {
    handleFullscreenOnCreate(setWindowAttributes);
  }

  mWindow =
      XCreateWindow(
        mDisplay,
        RootWindow(mDisplay, visualInfo->screen),
        0,
        0,
        mWidth,
        mHeight,
        0,
        visualInfo->depth,
        InputOutput,
        visualInfo->visual,
        CWBorderPixel|CWColormap|CWEventMask,
        &setWindowAttributes
      );

  XFree(visualInfo);

  if (mWindow == 0)
  {
    return;
  }

  XMapWindow(mDisplay, mWindow);
}

void X11RenderWindow::handleFullscreenOnCreate(XSetWindowAttributes& windowAttributes)
{
  int numModes;
  XF86VidModeModeInfo** modes;
  XF86VidModeGetAllModeLines(mDisplay, DefaultScreen(mDisplay), &numModes, &modes);
  mDesktopModeInfo = *modes[0];
  // Find mode suitable for fullscreen
  // Modify window attributes
  windowAttributes.override_redirect = True;
}

void X11RenderWindow::grabFullscreenInput()
{
  XWarpPointer(mDisplay, None, mWindow, 0, 0, 0, 0, 0, 0);
  XMapRaised(mDisplay, mWindow);
  XGrabKeyboard(mDisplay, mWindow, True, GrabModeAsync, GrabModeAsync, CurrentTime);
  XGrabPointer(
        mDisplay,
        mWindow,
        True,
        ButtonPressMask,
        GrabModeAsync,
        GrabModeAsync,
        mWindow,
        None,
        CurrentTime
  );
}

void X11RenderWindow::destroy()
{
  if (mValid)
  {
    mContext.destroy();
    XDestroyWindow(mDisplay, mWindow);
    XFreeColormap(mDisplay, mColormap);
    if (mFullscreen)
    {
      handleFullscreenOnDestroy();
    }
  }
  mValid = false;
}

void X11RenderWindow::handleFullscreenOnDestroy()
{
  XF86VidModeSwitchToMode(mDisplay, DefaultScreen(mDisplay), &mDesktopModeInfo);
  XF86VidModeSetViewPort(mDisplay, DefaultScreen(mDisplay), 0, 0);
}

bool const X11RenderWindow::isValid() const
{
  return mValid;
}

void X11RenderWindow::show()
{
  create();
}

void X11RenderWindow::hide()
{
  destroy();
}

void X11RenderWindow::setFullscreen(const bool enabled)
{
  if (enabled != mFullscreen)
  {
    mFullscreen = enabled;
    destroy();
    create();
  }
}

const bool X11RenderWindow::isFullscreen() const
{
  return mFullscreen;
}

void X11RenderWindow::resize(int width, int height)
{
  mWidth = width;
  mHeight = height;
  if (mValid)
  {
    destroy();
    create();
  }
}

void X11RenderWindow::setTitle(char const* title)
{
  mTitle = title;
  if (mValid)
  {
    XStoreName(mDisplay, mWindow, title);
    XSync(mDisplay, False);
  }
}

unsigned long X11RenderWindow::getHandle()
{
  return mWindow;
}

RenderContext& X11RenderWindow::getContext()
{
  return mContext;
}

}}
