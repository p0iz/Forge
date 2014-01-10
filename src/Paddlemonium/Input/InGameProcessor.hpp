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

#include "Graphics/Scene/SceneConfig.hpp"
#include "Platform/Window/RenderWindow.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Platform/Input/InputProcessor.hpp"
#include "Platform/Input/KeySymbols.hpp"
#include "Time/HighResClock.h"

#include <map>

enum GameAction
{
  // Paddle
  PaddleLeft,
  PaddleRight,

  // Misc.
  ToggleFullscreen,
  ToggleDebug,

  // Speed
  SpeedPaused,
  SpeedSlow,
  SpeedNormal,
  SpeedFast,

  // Quit
  QuitGame
};

template <class ActionType>
using KeyMap = std::map<Forge::Key, ActionType>;

namespace Paddlemonium {

class InGameProcessor : public Forge::Input::InputProcessor
{
  public:
  InGameProcessor(
    Forge::HighResClock& clock,
    Forge::Input::InputHandler& input,
    Forge::RenderWindow& window,
    Forge::SceneConfig& scene
  );
  virtual ~InGameProcessor();

  virtual bool process(float const delta);
  private:
  void processMouseMove();
  bool processKeyPress(float const delta);
  void mapDefaultKeys();

  Forge::SceneConfig& mScene;
  KeyMap<GameAction> mKeyMap;
  Forge::HighResClock& mClock;
  Forge::Input::InputHandler& mInputHandler;
  Forge::RenderWindow& mWindow;
};

}
