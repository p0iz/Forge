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

#include "MeshComponent.hpp"
#include "Graphics/StaticMesh.h"
#include "Util/Internal/Keeper.hpp"


namespace Forge {

MeshComponent::MeshComponent(GameObject* owner, StaticMesh* mesh):
  Component(owner),
  mMesh(mesh)
{
}

void MeshComponent::update()
{
  mMesh->draw();
}

void MeshComponent::destroy()
{
  Keeper<MeshComponent>::instance().destroy(this);
}

}
