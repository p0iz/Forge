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

#pragma once

#include "Lua/LuaState.hpp"
#include "ForgeExport.h"
#include <iosfwd>


namespace Forge {

/** Class that represents the command-line Lua interface for the Forge engine */
class ForgeCLI
{
  public:
    explicit ForgeCLI(std::istream& input);

    void readInput();

    void printPrompt();

    bool endOfStream() const;

  private:
    LuaState mState;
    std::istream& mInput;
};

}
