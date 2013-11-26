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

#include "ForgeMain.hpp"
#include "State/GameStateLibrary.hpp"

#include "State/InGame.h"
#include "State/Menu.h"
#include "Input/InGameProcessor.hpp"
#include <windows.h>

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
  Forge::ForgeMain forge;
  forge.init("Paddlemonium");

  // Create the initial state and pass it to Forge
  Forge::GameStatePtr inGame(new Paddlemonium::State::InGame(forge));
  inGame->createState();
  Forge::GameStateLibrary::instance().add(inGame);

  forge.start(inGame);

  return 0;
}
