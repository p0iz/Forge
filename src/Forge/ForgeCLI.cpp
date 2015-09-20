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
#include "Lua/LuaLibrary.hpp"
#include "Util\Log.h"
#include <iostream>
#include <string>

namespace Forge {

namespace {

static std::string const ProgramName = "=ForgeCLI";

}

ForgeCLI::ForgeCLI():
  _state(),
  _isRepl(false)
{
  if (!_state.initialize())
  {
    Log::error << "Failed to initialize Lua state in ForgeCLI!";
  }
}

void ForgeCLI::readInput(std::istream& input)
{
  std::string chunk, line;
  bool isContinued = false;
  do {
    std::getline(input, line);
    chunk.append(line);
    chunk.push_back('\n');
    isContinued = _state.isIncompleteChunk(chunk);
    if (_isRepl && isContinued)
    {
      std::cout << " ... ";
    }
  }
  while (isContinued);
  _state.runChunk(ProgramName, chunk);

}

void ForgeCLI::addLibrary(LuaLibrary& library)
{
  if (_state.isInitialized())
  {
    _state.importLibrary(library);
    _libraries.push_back(&library);
  }
}

void ForgeCLI::printPrompt()
{
  std::cout << "Forge > ";
}

bool ForgeCLI::endOfStream(std::istream const& input) const
{
  return input.eof();
}

void ForgeCLI::start(std::istream& input)
{
  _isRepl = (&input == &std::cin);

  while (!endOfStream(input))
  {
    if (_isRepl)
    {
      printPrompt();
    }
    readInput(input);
    for (LuaLibrary* lib : _libraries)
    {
      lib->frameUpdate();
    }
  }
  std::cout << std::endl;
}

bool ForgeCLI::isRepl() const
{
  return _isRepl;
}

}
