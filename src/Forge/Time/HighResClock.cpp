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

#include <chrono>

namespace Forge {

HighResClock::HighResClock(double scale)
	: mScaleFactor(scale), mLastUpdateTime(getCurrentTime())
{
}

const float HighResClock::getGameDelta() const
{
	const float delta = static_cast<float>(mScaleFactor * mRealTimeDelta);
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
	mRealTimeDelta = static_cast<float>(now - mLastUpdateTime);
	mLastUpdateTime = now;
}

const double HighResClock::getCurrentTime()
{
	using namespace std::chrono;

	high_resolution_clock::duration currentClock = high_resolution_clock::now().time_since_epoch();
	return static_cast<double>(currentClock.count()) / high_resolution_clock::period::den;
}

const float HighResClock::getElapsedRealTime() const
{
	return static_cast<float>(mLastUpdateTime - mInitTime);
}

const double HighResClock::setTimeScale(double newFactor)
{
	double oldFactor = mScaleFactor;
	mScaleFactor = newFactor;
	return oldFactor;
}

const double HighResClock::getTimeScale() const {
	return mScaleFactor;
}

} // Forge
