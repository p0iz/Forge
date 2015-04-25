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

#include "MeshInstance.hpp"
#include "Assets/AssetManager.hpp"
#include "Graphics/StaticMesh.h"
#include "Util/ServiceProvider.hpp"


namespace Forge {

MeshInstance::MeshInstance(std::string const& mesh):
  Component(),
  mHandle(AssetHandle::create()),
  mMeshPtr(),
  mMesh()
{
  AssetManager& assetMan = Service::get<AssetManager>();
  mHandle = assetMan.load(mesh);
  mMeshPtr = mHandle.isValid() ? assetMan.get(mHandle) : nullptr;
  mMesh = static_cast<StaticMesh*>(mMeshPtr.get());
}

MeshInstance::~MeshInstance()
{
}

ComponentType MeshInstance::getType() const
{
  return ComponentType::Mesh;
}

void MeshInstance::update()
{
  if (mMesh)
  {
    mMesh->draw();
  }
}

void MeshInstance::destroy()
{
}

}
