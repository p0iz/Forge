#ifndef FORGECLI_HPP
#define FORGECLI_HPP
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

#include "Lua/LuaState.hpp"
#include <vector>
#include <iosfwd>

namespace Forge {

/** Class that represents the command-line Lua interface for the Forge engine */
class ForgeCLI
{
  public:
    ForgeCLI();

    void addLibrary(LuaLibrary& library);

    void start(std::istream& input);

    bool isRepl() const;

  private:
    void readInput(std::istream& input);

    void printPrompt();

    bool endOfStream(std::istream const& input) const;

    bool _isRepl;

    std::vector<LuaLibrary*> _libraries;
    LuaState _state;
};

}

#endif // FORGECLI_HPP
