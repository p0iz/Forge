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

#include "ForgeExport.h"
#include <string>
#include <SDL2/SDL.h>


/* This abstract class provides a contract for implementing a render window
 * for Forge. The function implementations should provide intuitive behaviour
 * with regard to rendering into a window.
 *
 * The constructor should create a OpenGL rendering context that fulfills the
 * RenderContext contract and make it current at the end of the constructor.
 */


namespace Forge { namespace Graphics {

class FORGE_EXPORT RenderWindow
{
  public:
    RenderWindow();
    ~RenderWindow();

    bool const isValid() const;

    void show();
    void hide();
    void setFullscreen(bool const enabled);
    bool const isFullscreen() const;
    void resize(int width, int height);

    int width() const;
    int height() const;

    /* This is a context-specific identifier for the render window */
    unsigned long getHandle();

    void setTitle(std::string const& title);
    std::string const& title() const;

    void swapBuffers();

  private:
    SDL_Window* mWindow;
    SDL_GLContext mContext;

    bool mFullscreen;
    std::string mTitle;

    int mWidth;
    int mHeight;

};

}}
