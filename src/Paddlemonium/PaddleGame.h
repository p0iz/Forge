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

#include "Input/InGameProcessor.hpp"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/Renderer.h"
#include "Graphics/Scene/SceneConfig.hpp"
#include "Platform/Event/EventHandler.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Platform/Window/RenderWindow.hpp"
#include "State/GameStateMachine.hpp"
#include "Time/HighResClock.h"

namespace Paddlemonium {

class PaddleGame
{
public:
  PaddleGame();
  void init(
      const std::string& windowTitle = "SUPER AWESOME PADDLE DEATH!",
      std::string const& cfgFile = "data/PaddleGame.configuration");
  int run();
private:
  void initializeGameStates();

  Forge::HighResClock mClock;
  Forge::Event::EventHandler& mEventHandler;
  Forge::Graphics::RenderWindowPtr mRenderWindow;
  Forge::Graphics::Renderer mRenderer;
  Forge::GameStateMachine mStateMachine;
  Forge::SceneConfig mSceneConfig;

  InGameProcessor mInGameProcessor;
  Forge::Input::InputHandlerPtr mInput;
};

}
