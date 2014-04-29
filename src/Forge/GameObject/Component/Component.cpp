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
 * Copyright 2014 Tommi Martela
 *
 */

#include "Component.hpp"

namespace Forge {

Component::Component(GameObject* owner):
  mOwner(owner),
  mActive(true)
{
}

bool Component::active() const
{
  return mActive;
}

void Component::setActive(bool active)
{
  mActive = active;
}

void Component::setOwner(GameObject* go)
{
  mOwner = go;
}

GameObject& Component::owner()
{
  return *mOwner;
}

GameObject const& Component::owner() const
{
  return *mOwner;
}

}
