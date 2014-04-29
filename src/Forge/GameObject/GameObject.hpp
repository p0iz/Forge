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
#include "Component/Component.hpp"
#include "Transformation.hpp"
#include <string>
#include <unordered_set>
#include <vector>


namespace Forge {

class FORGE_EXPORT GameObject
{
  public:
    explicit GameObject(GameObject* parent = nullptr);
    ~GameObject();

    Transformation transform() const;

    Transformation& localTransform();
    Transformation const& localTransform() const;

    void setName(std::string const& name);
    std::string const& name() const;

    void addComponent(Component* component);
    void addChild(GameObject* child);
    void removeChild(GameObject* child);

  private:
    std::string mName;
    Transformation mWorldTransform;
    std::vector<Component*> mComponents;

    GameObject* mParent;
    std::unordered_set<GameObject*> mChildren;
};

}
