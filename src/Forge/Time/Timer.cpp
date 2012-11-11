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

#include "Timer.hpp"

#include <chrono>
#include <iostream>

Timer::Timer()
	: mCallback([]{}), mRecurring(false)
{
}

Timer::~Timer()
{
	stop();
	mTimerThread.join();
}

void Timer::start(int microseconds)
{
	mTimerThread = std::thread([microseconds, this]
		{
			do {
				std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
				if (!mStopped)
				{
					mCallback();
				}
			} while (mRecurring && !mStopped);
		});
}

void Timer::stop()
{
	mStopped = true;
}

void Timer::setCallback(std::function<void()> callback)
{
	mCallback = callback;
}

void Timer::setRecurring(bool recurring)
{
	mRecurring = recurring;
}

bool Timer::isRecurring()
{
	return mRecurring;
}

