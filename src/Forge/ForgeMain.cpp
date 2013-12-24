#include "ForgeMain.hpp"
#include "Util/Log.h"
#include "Config/Configuration.hpp"
#include <SDL2/SDL.h>


namespace Forge {

namespace {
  float constexpr SecondsPerFrame = 1.0/60;
}

ForgeMain::ForgeMain():
  mClock(),
  mRenderWindow(),
  mRenderer(),
  mStateMachine(),
  mInput(),
  mEventHandler(mInput, mRenderWindow),
  mRunning(false)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
  Log::error << "Failed to initialize SDL: " << SDL_GetError() << "\n";
  }
}

ForgeMain::~ForgeMain()
{
  SDL_Quit();
}

void ForgeMain::init(std::string const& windowTitle, std::string const& cfgFile)
{
  Forge::Log::info << "Initializing Forge game engine...\n"
            "Built on " << __DATE__ << " at " << __TIME__ "\n";

  const Forge::Configuration& cfg = Forge::Configuration::instance();
  cfg.loadConfig(cfgFile);
  mRenderWindow.setTitle(windowTitle.c_str());
  mRenderWindow.setFullscreen(false);
  mRenderWindow.resize(cfg.display.width, cfg.display.height);
  mRenderWindow.show();

  mRenderer.initialize();
  mRenderer.updateViewport(cfg.display.width, cfg.display.height);
}

void ForgeMain::start(GameStatePtr const& startState)
{
  mStateMachine.init(startState);

  mRunning = true;
  while(mRunning)
  {

    mClock.updateDeltaTime();
    float const delta = mClock.getGameDelta();

    mRunning =
      mEventHandler.pumpMessages() &&
      mInput.process(delta) &&
      mStateMachine.update(delta);

    mRenderWindow.swapBuffers();

    // Sleep for rest of frame seconds
    mClock.updateDeltaTime();
    int sleepMillis = 1000 * (SecondsPerFrame - mClock.getRealDelta());
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepMillis));
  }
}

Graphics::Renderer& ForgeMain::renderer()
{
  return mRenderer;
}

Graphics::RenderWindow& ForgeMain::window()
{
  return mRenderWindow;
}

Input::InputHandler& ForgeMain::input()
{
  return mInput;
}

HighResClock& ForgeMain::clock()
{
  return mClock;
}

}
