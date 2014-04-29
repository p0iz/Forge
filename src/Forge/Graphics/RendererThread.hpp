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

#include "ForgeExport.h"
#include "Application/Application.hpp"
#include "Graphics/Renderer.h"
#include "Graphics/Viewport.hpp"
#include "Platform/Window/RenderWindow.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Platform/Event/EventHandler.hpp"
#include <thread>


namespace Forge {

class Camera;

class FORGE_EXPORT RendererThread
{
  public:
    RendererThread(Application& app);

    bool start();

    void stop();

    GraphicsContext* createAuxContext();

    RenderWindow const& window();

    Renderer& renderer();

    void addViewport(std::string const& name, Viewport* viewport);

    Viewport* getViewport(std::string const& name);

  private:
    bool mRunning;

    std::thread mThread;
    RenderWindow mWindow;
    EventHandler mEvents;
    Renderer mRenderer;
    std::unordered_map<std::string, Viewport*> mViewports;

    Application mApp;
};

}
