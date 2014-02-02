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

#include "RenderWindow.hpp"
#include "SDLGraphicsContext.hpp"
#include "Util/Log.h"
#include <SDL2/SDL.h>
#include "GL/glew.h"


namespace Forge {

RenderWindow::RenderWindow():
  mWindow(nullptr),
  mRenderingContext(nullptr),
  mFullscreen(false),
  mTitle("Forge render window"),
  mWidth(640),
  mHeight(480)
{
  mWindow = SDL_CreateWindow(
    mTitle.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    mWidth,
    mHeight,
    SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL
  );

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, SDL_TRUE);

  SDL_GLContext context = SDL_GL_CreateContext(mWindow);
  mRenderingContext = new SDLGraphicsContext(context, mWindow);

  if (context)
  {
    // Flag to load all extensions, needed by OpenGL 3.3
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
      Log::error << "Failed to initialize OpenGL functions. A crash is imminent...\n";
    }
  }

  SDL_GL_SetSwapInterval(1);
}

RenderWindow::~RenderWindow()
{
  delete mRenderingContext;
  mRenderingContext = nullptr;
  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;
}

void RenderWindow::show()
{
  SDL_ShowWindow(mWindow);
  mRenderingContext->makeCurrent();
}

void RenderWindow::hide()
{
  SDL_HideWindow(mWindow);
}

void RenderWindow::setFullscreen(const bool enabled)
{
  mFullscreen = enabled;
}

const bool RenderWindow::isFullscreen() const
{
  return mFullscreen;
}

void RenderWindow::resize(int width, int height)
{
  mWidth = width;
  mHeight = height;
  SDL_SetWindowSize(mWindow, mWidth, mHeight);
}

int RenderWindow::width() const
{
  return mWidth;
}

int RenderWindow::height() const
{
  return mHeight;
}

void RenderWindow::setTitle(const std::string& title)
{
  mTitle = title;
}

std::string const& RenderWindow::title() const
{
  return mTitle;
}

void RenderWindow::swapBuffers()
{
  SDL_GL_SwapWindow(mWindow);
}

bool RenderWindow::makeRenderCurrent()
{
  return mRenderingContext->makeCurrent();
}

GraphicsContext* RenderWindow::createAuxContext() const
{
  SDL_GLContext context = SDL_GL_CreateContext(mWindow);
  mRenderingContext->makeCurrent();
  return new SDLGraphicsContext(context, mWindow);
}

}
