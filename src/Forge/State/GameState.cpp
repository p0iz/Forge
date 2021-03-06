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

#include "GameState.h"
#include "GameStateLibrary.hpp"

namespace Forge
{

GameState::GameState(const std::string& name) : mName(name) { }

GameState::~GameState() {
  destroyState();
}

void GameState::enter()
{
}

void GameState::createState() { }
void GameState::destroyState() { }

GameStatePtr GameState::frameUpdate(const float delta)
{
  return GameStatePtr(nullptr);
}

const std::string& GameState::getName() const {
  return mName;
}

} // namespace Forge
