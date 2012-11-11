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

#include "QtEngineState.h"

#include "Input/QtInputHandler.h"
#include "Graphics/RendererWidget.h"
#include "Time/HighResClock.h"

namespace Forge
{

QtEngineState::QtEngineState(
		RendererWidget& renderer,
		QtInputHandler& input,
		HighResClock& clock)
	: mRenderer(renderer), mInput(input), mClock(clock)
{
}

void QtEngineState::fire() const
{
	float delta = mClock.getGameDelta();
	mClock.updateDeltaTime();
	mInput.processInput(delta);
	mRenderer.updateGL();
}

} // namespace Forge
