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

#include "Application/ForgeCLI.hpp"
#include <iostream>


// main function for CLI
#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  int argc = __argc;
  char** argv = __argv;
#else
int main(int argc, char** argv)
{
#endif
  // Optimization for freeing std::cin from syncing with stdin (makes Valgrind sad)
  //std::cin.sync_with_stdio(false);

  Forge::ForgeCLI cli(std::cin);

  if (argc > 1)
  {
    cli.runScript(argv[1]);
  }
  else
  {
    cli.start();
  }

  return 0;
}
