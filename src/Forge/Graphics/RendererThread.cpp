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
#include "Mesh.h"

namespace Forge {

RendererThread::RendererThread():
  mRunning(false),
  mThread(),
  mRenderer(),
  mWindow(),
  mMeshes(nullptr)
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
    mThread = std::thread([this](){
      mWindow.resize(640,480);
      mWindow.show();
      mWindow.setTitle("Forge");
      mRenderer.initialize();
      while(mRunning)
      {
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

void RendererThread::setMeshAssets(AssetMap* meshmap)
{
  mMeshes = meshmap;
}

GraphicsContext* RendererThread::createAuxContext()
{
  return mWindow.createAuxContext();
}

}
