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

#include "GameStateMachine.hpp"
#include "GameState.h"

namespace Forge {

GameStateMachine::GameStateMachine() : mCurrentState(nullptr) { }

void GameStateMachine::init(const GameStatePtr& initialState) {
  mCurrentState = initialState;
  mCurrentState->enter();
}

bool GameStateMachine::update(float const delta) {
  if (mCurrentState) {
    GameStatePtr nextState = mCurrentState->frameUpdate(delta);
    if (nextState != mCurrentState)
    {
      mCurrentState = nextState;
      mCurrentState->enter();
    }
    return true;
  } else {
    return false;
  }
}

void GameStateMachine::reset()
{
  mCurrentState.reset();
}

}
