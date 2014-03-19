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
#include "Lua/ComponentsLibrary.hpp"
#include "Lua/RendererLibrary.hpp"
#include "Platform/Window/GraphicsContext.hpp"
#include <fstream>
#include <iostream>
#include <string>


namespace Forge {

namespace {

static std::string const ProgramName = "=ForgeCLI";

}

ForgeCLI::ForgeCLI(std::istream& input):
  mState(),
  mInput(input)
{
  mState.initialize();

  AssetsLibrary assets;
  addLibrary(assets);

  ComponentsLibrary components;
  addLibrary(components);

  RendererLibrary renderer;
  addLibrary(renderer);

  // Create an auxiliary context to use for loading asset data into OpenGL from scripts
  GraphicsContext* loaderContext = renderer.thread().createAuxContext();
  loaderContext->makeCurrent();
}

ForgeCLI::~ForgeCLI()
{
  RendererLibrary::thread().stop();
}

void ForgeCLI::readInput()
{
  std::string chunk, line;
  do {
    std::getline(mInput, line);
    chunk.append(line);
    chunk.push_back('\n');
  }
  while (mState.isIncompleteChunk(chunk) && std::cout << " ... ");
  mState.runChunk(ProgramName, chunk);
}

void ForgeCLI::addLibrary(LuaLibrary& library)
{
  if (mState.isInitialized())
  {
    mState.importLibrary(library);
  }
}

void ForgeCLI::printPrompt()
{
  std::cout << "Forge > ";
}

bool ForgeCLI::endOfStream() const
{
  return mInput.eof();
}

void ForgeCLI::runScript(std::string const& filename)
{
  mState.runScript(filename);
}

void ForgeCLI::start()
{
  while (!endOfStream())
  {
    printPrompt();
    readInput();
  }
}

}
