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

/** A high-res clock wrapper using the std::chrono::high_resolution_clock of C++11 */

namespace Forge {

class Engine;

class HighResClock
{
public:
	HighResClock(double scale = 1.0);
	void init();

	void updateDeltaTime();
	const float getGameDelta() const;
	const float getRealDelta() const;

	const float getElapsedRealTime() const;

	const double setTimeScale(double newFactor)
	{
		double oldFactor = mScaleFactor;
		mScaleFactor = newFactor;
		return oldFactor;
	}
	const double getTimeScale() const
	{
		return mScaleFactor;
	}

private:

	const double getCurrentTime() const;

	float mRealTimeDelta; // not scaled

	double mScaleFactor;
	double mInitTime;
	double mLastUpdateTime;
};

} // namespace Forge
