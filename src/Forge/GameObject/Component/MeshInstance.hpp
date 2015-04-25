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

#pragma once

#include "Component.hpp"
#include "Assets/AssetHandle.hpp"
#include <memory>
#include <string>


namespace Forge {

class StaticMesh;

// Derived component
class MeshInstance : public Component
{
  public:
    // Acquire assets, load scripts etc. here
    explicit MeshInstance(std::string const& mesh);
    virtual ~MeshInstance();

    virtual ComponentType getType() const;

    // Perform a frame update on the component
    virtual void update();

    // Release any acquired assets here
    virtual void destroy();

  private:
    AssetHandle mHandle;
    std::shared_ptr<void> mMeshPtr;
    StaticMesh* mMesh;
};

}
