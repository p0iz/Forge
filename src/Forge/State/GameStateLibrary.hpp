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

#pragma once

#include "ForgeExport.h"
#include "GameState.h"
#include "Util/Singleton.hpp"
#include <unordered_map>
#include <string>


namespace Forge {

/* This class can be used to store and access a library of game states. */
class FORGE_EXPORT GameStateLibrary : public Singleton<GameStateLibrary> {
public:
  void add(GameStatePtr state);
  GameStatePtr get(const std::string& name);
private:
  std::unordered_map<std::string, GameStatePtr> mGameStates;
};

}
