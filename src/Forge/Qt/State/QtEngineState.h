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

#include "Engine.h"
#include "State/EngineState.h"

#include "Graphics/QtRenderer.hpp"

namespace Forge
{
	class QtInputHandler;

	class QtEngineState : public EngineState
	{
	public:
		QtEngineState(
				QtRenderer& renderer,
				QtInputHandler& input,
				HighResClock& clock);

		virtual void fire() const;

	private:
		QtRenderer& mRenderer;
		QtInputHandler& mInput;
		HighResClock& mClock;
	};
} // namespace Forge
