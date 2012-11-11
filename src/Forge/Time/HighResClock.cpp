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

#include "HighResClock.h"

#include "Engine.h"

#include <chrono>

namespace Forge {

HighResClock::HighResClock(double scale)
	: mScaleFactor(scale), mLastUpdateTime(getCurrentTime())
{
}

const float HighResClock::getGameDelta() const
{
	const float delta = mScaleFactor * mRealTimeDelta;
	return delta;
}

const float HighResClock::getRealDelta() const
{
	return mRealTimeDelta;
}

void HighResClock::init()
{
	mInitTime = getCurrentTime();
	mLastUpdateTime = mInitTime;
}

void HighResClock::updateDeltaTime()
{
	double now = getCurrentTime();
	mRealTimeDelta = now - mLastUpdateTime;
	mLastUpdateTime = now;
}

const double HighResClock::getCurrentTime() const
{
	using namespace std::chrono;

	auto currentClock = high_resolution_clock::now().time_since_epoch();
	return (1.0*currentClock.count()) / high_resolution_clock::period::den;
}

const float HighResClock::getElapsedRealTime() const
{
	return mLastUpdateTime - mInitTime;
}

} // Forge

