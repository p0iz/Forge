#include "EventLibrary.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Platform/Event/EventHandler.hpp"

namespace Forge {

namespace {
  InputHandler input;
  EventHandler event(input);
}

void EventLibrary::import(lua_State* state)
{
}

void EventLibrary::remove(lua_State* state)
{
}

void EventLibrary::frameUpdate()
{
  event.pumpMessages();
}

}