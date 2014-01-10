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

#include "ForgeCLI.hpp"
#include "Lua/AssetsLibrary.hpp"
#include <iostream>


// main function for CLI
int main(int argc, char* argv[])
{
  // Optimization for freeing std::cin from syncing with stdin (makes Valgrind sad)
  //std::cin.sync_with_stdio(false);

  Forge::ForgeCLI cli(std::cin);

  Forge::AssetsLibrary assets;
  cli.addLibrary(assets);

  if (argc > 1)
  {
    cli.runScript(argv[1]);
    return 0;
  }

  cli.start();

  std::cout << std::endl;

  return 0;
}
