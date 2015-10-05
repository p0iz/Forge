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
 * Copyright 2015 Tommi Martela
 *
 */

#define SDL_MAIN_HANDLED 1

#include "ForgeCLI.hpp"
#include "Lua/AssetsLibrary.hpp"
#include "Lua/EventLibrary.hpp"
#include "Lua/RendererLibrary.hpp"
#include "Lua/SceneLibrary.hpp"
#include <fstream>
#include <iostream>

// main function for CLI
int main(int argc, char** argv)
{
  Forge::ForgeCLI cli;

  Forge::AssetsLibrary assets;
  cli.addLibrary(assets);

  Forge::EventLibrary event;
  cli.addLibrary(event);

  Forge::RendererLibrary renderer;
  cli.addLibrary(renderer);

  Forge::SceneLibrary scene;
  cli.addLibrary(scene);

  if (argc > 1)
  {
    cli.start(std::ifstream(argv[1]));
  }
  else
  {
    cli.start(std::cin);
  }

  return 0;
}
