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


/** A high-res clock wrapper using the std::chrono::high_resolution_clock of C++11 */
namespace Forge {

class FORGE_EXPORT HighResClock
{
public:
  HighResClock(double scale = 1.0);
  void init();

  // Time deltas
  void updateDeltaTime();
  const float getGameDelta() const;
  const float getRealDelta() const;

  // Real-time
  static const double getCurrentTime();
  const float getElapsedRealTime() const;

  // Time scale manipulators
  const double setTimeScale(double newFactor);
  const double getTimeScale() const;

private:
  int mRealTimeDeltaMillis;
  float mRealTimeDelta;
  double mScaleFactor;
  double mInitTime;
  double mLastUpdateTime;
};

} // namespace Forge
