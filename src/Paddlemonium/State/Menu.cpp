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

#include "Menu.h"
#include "State/GameStateLibrary.hpp"
#include "Time/HighResClock.h"
#include "Util/Log.h"
#include <sstream>

namespace Paddlemonium { namespace State {

Menu::Menu():
  GameState("Menu")
{
}

Forge::GameStatePtr Menu::frameUpdate(float const /*delta*/) {
  static Forge::GameStateLibrary& library = Forge::GameStateLibrary::instance();

  // Return next (this) state
  Forge::Log::info << "Starting game.\n";
  return library.get("InGame");
}

void Menu::createState() {
}

void Menu::destroyState() { }

}}
