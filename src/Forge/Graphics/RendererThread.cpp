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

#include "RendererThread.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Light/Light.hpp"
#include "Util/Log.h"


namespace Forge {

RendererThread::RendererThread():
  mRunning(false),
  mThread(),
  mWindow(),
  mRenderer(),
  mViewports()
{
}

bool RendererThread::start()
{
  if (!mRunning)
  {
    if (mThread.joinable())
    {
      mThread.join();
    }

    mRunning = true;
    mThread = std::thread([this]()
    {
      mWindow.makeRenderCurrent();
      mWindow.resize(640,480);
      mWindow.show();
      mWindow.setTitle("Forge");
      mRenderer.initialize();

      while(mRunning)
      {
        for (auto nameViewport : mViewports)
        {
          if (nameViewport.second)
          {
            mRenderer.render(*static_cast<Viewport const*>(nameViewport.second));
          }
        }
        mWindow.swapBuffers();
      }
      mRenderer.deinitialize();
      mWindow.hide();
    });
  }
  return mThread.joinable();
}

void RendererThread::stop()
{
  if (mRunning)
  {
    mRunning = false;
    mThread.join();
  }
}

GraphicsContext* RendererThread::createAuxContext()
{
  return mWindow.createAuxContext();
}

RenderWindow const& RendererThread::window()
{
  return mWindow;
}

void RendererThread::addViewport(const std::string& name, Viewport* viewport)
{
  mViewports[name] = viewport;
}

Viewport* RendererThread::getViewport(const std::string& name)
{
  return mViewports[name];
}

}
