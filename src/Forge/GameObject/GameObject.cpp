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
 * Copyright 2013 Tommi Martela
 *
 */

#include "GameObject.hpp"
#include "Util/Log.h"


namespace Forge {

GameObject::GameObject(std::string const& name)
  : mName(name), mWorldTransform()
{
}

Transformation const& GameObject::transform() const
{
  return mWorldTransform;
}

void GameObject::translate(float x, float y, float z)
{
  mWorldTransform.translate(x, y, z);
}

std::string const& GameObject::name() const
{
  return mName;
}

}
