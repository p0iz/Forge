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
#include "Util/Log.h"
#include <SDL2/SDL.h>


namespace Forge { namespace Graphics {

RenderWindow::RenderWindow():
  mWindow(nullptr),
  mContext(nullptr),
  mFullscreen(false),
  mTitle("Forge render window"),
  mWidth(640),
  mHeight(480)
{
}

RenderWindow::~RenderWindow()
{
  SDL_GL_DeleteContext(mContext);
  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;
}

void RenderWindow::show()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  mWindow = SDL_CreateWindow(
    mTitle.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    mWidth,
    mHeight,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL
  );
  mContext = SDL_GL_CreateContext(mWindow);
  SDL_GL_SetSwapInterval(1);
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

const std::string&RenderWindow::title() const
{
  return mTitle;
}

void RenderWindow::swapBuffers()
{
  SDL_GL_SwapWindow(mWindow);
}

}}
