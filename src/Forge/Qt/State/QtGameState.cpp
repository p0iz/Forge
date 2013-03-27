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

#include "State/QtGameState.h"
#include "State/GameStateLibrary.hpp"

#include "Input/QtInputHandler.h"
#include "Graphics/QtRenderer.hpp"
#include "Time/HighResClock.h"

namespace Forge
{

QtGameState::QtGameState(
		const QString& name,
		QtRenderer& renderer,
		QtInputHandler& input,
		HighResClock& clock)
	: GameState(name.toStdString()), mRenderer(renderer), mInput(input), mClock(clock)
{
}

GameStatePtr QtGameState::update()
{
	static GameStateLibrary& library = GameStateLibrary::getSingleton();
	float delta = mClock.getGameDelta();
	mClock.updateDeltaTime();
	mInput.processInput(delta);
	mRenderer.render();
	return library.get(getName());
}

} // namespace Forge
