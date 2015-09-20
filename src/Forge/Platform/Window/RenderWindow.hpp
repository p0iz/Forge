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

#include "SDLGraphicsContext.hpp"
#include <string>


/* This class provides an SDL render window for Forge.
 *
 * The constructor should create a OpenGL rendering context that fulfills the
 * RenderContext contract and make it current at the end of the constructor.
 */


class SDL_Window;

namespace Forge {

class RenderWindow
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

    void setTitle(std::string const& title);
    std::string const& title() const;

    void swapBuffers();

    // Create additional contexts for processing graphics commands (buffering, loading, etc.)
    // Do NOT issue draw commands from these contexts. Draw commands should only be issued from
    // the rendering context.
    SDLGraphicsContext* createAuxContext() const;

    // Make the rendering context the current graphics context
    bool makeRenderCurrent();

  private:
    SDL_Window* mWindow;
    SDLGraphicsContext* mRenderingContext;

    bool mFullscreen;
    std::string mTitle;

    int mWidth;
    int mHeight;

};

}
