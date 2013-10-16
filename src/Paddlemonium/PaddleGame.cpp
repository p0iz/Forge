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

#include "PaddleGame.h"

#include "State/InGame.h"
#include "State/Menu.h"

// Forge includes
#include "Config/Configuration.hpp"
#include "State/GameStateLibrary.hpp"
#include "Util/Log.h"

#include "Platform/FileSystem/Directory.hpp"

#include <thread>


namespace {
  float const FRAME_SECONDS = 1.0/60;
}

namespace Paddlemonium {

PaddleGame::PaddleGame():
  mClock(),
  mEventHandler(Forge::Event::EventHandler::getInstance()),
  mRenderWindow(Forge::Graphics::RenderWindow::createInstance()),
  mStateMachine(),
  mInGameProcessor(mClock, *mRenderWindow),
  mInput(Forge::Input::InputHandler::getInstance())
{
}

void PaddleGame::initializeGameStates()
{
  Forge::GameStatePtr menuState(new State::Menu());
  menuState->createState();

  mInput.setProcessor(&mInGameProcessor);

  Forge::GameStatePtr inGameState(new State::InGame(mRenderer, mInGameProcessor));

  inGameState->createState();

  Forge::GameStateLibrary::instance().add(menuState);
  Forge::GameStateLibrary::instance().add(inGameState);
  mStateMachine.init(menuState);
}

void PaddleGame::init(std::string const& windowTitle, std::string const& cfgFile)
{
  Forge::Log::info << "Initializing Forge game engine...\n"
                      "Built on " << __DATE__ << " at " << __TIME__ "\n";

  const Forge::Configuration& cfg = Forge::Configuration::instance();
  cfg.loadConfig(cfgFile);
  mRenderWindow->setTitle(windowTitle.c_str());
  mRenderWindow->setFullscreen(false);
  mRenderWindow->resize(cfg.display.width, cfg.display.height);
  mRenderWindow->show();
  mEventHandler.registerWindow(mRenderWindow);
  mInput.setCurrentWindow(mRenderWindow);

  mRenderer.initialize();
  mRenderer.updateViewport(cfg.display.width, cfg.display.height);
  initializeGameStates();
}

int PaddleGame::run()
{
  int result = 0;
  mClock.init();

  bool running = true;
  mInput.capture();
  while(running)
  {
    mClock.updateDeltaTime();
    float const delta = mClock.getGameDelta();

    running =
      mInput.process(delta) &&
      mStateMachine.update(delta) &&
      mEventHandler.pumpMessages();

    mRenderWindow->getContext().swapBuffers();

    // Sleep for rest of frame seconds
    mClock.updateDeltaTime();
    int sleepMillis = 1000 * (FRAME_SECONDS - mClock.getRealDelta());
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepMillis));
  }
  mInput.release();

  return result;
}

}
