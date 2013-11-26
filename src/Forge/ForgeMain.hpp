#pragma once

#include "ForgeExport.h"
#include "Graphics/Renderer.h"
#include "Platform/Event/EventHandler.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Platform/Window/RenderWindow.hpp"
#include "State/GameStateMachine.hpp"
#include "Time/HighResClock.h"
#include <thread>


namespace Forge {

class FORGE_EXPORT ForgeMain
{
  public:
  ForgeMain();

  ~ForgeMain();

  void init(
    std::string const& windowTitle = "Forge render window",
    std::string const& cfgFile = "data/PaddleGame.configuration"
  );

  void start(Forge::GameStatePtr const& startState);

  Graphics::Renderer& renderer();

  Graphics::RenderWindow& window();

  Input::InputHandler& input();

  HighResClock& clock();

  private:
  HighResClock mClock;
  Graphics::RenderWindow mRenderWindow;
  Graphics::Renderer mRenderer;
  GameStateMachine mStateMachine;
  Input::InputHandler mInput;
  Event::EventHandler mEventHandler;
  bool mRunning;

};

}
