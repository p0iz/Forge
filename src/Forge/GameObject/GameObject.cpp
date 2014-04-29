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


namespace Forge {

GameObject::GameObject(GameObject* parent)
  : mName(""), mWorldTransform(), mParent(parent), mChildren()
{
  if (parent)
  {
    parent->addChild(this);
  }
}

GameObject::~GameObject()
{
  if (mParent)
  {
    mParent->removeChild(this);
  }
}

Transformation GameObject::transform() const
{
  if (mParent)
  {
    return mParent->transform() * mWorldTransform;
  }
  else
  {
    return mWorldTransform;
  }
}

Transformation& GameObject::localTransform()
{
  return mWorldTransform;
}

Transformation const& GameObject::localTransform() const
{
  return mWorldTransform;
}

void GameObject::setName(const std::string& name)
{
  mName = name;
}

std::string const& GameObject::name() const
{
  return mName;
}

void GameObject::addComponent(Component* component)
{
  component->setOwner(this);
  mComponents.push_back(component);
}

void GameObject::addChild(GameObject* child)
{
  child->mParent = this;
  mChildren.insert(child);
}

void GameObject::removeChild(GameObject* child)
{
  mChildren.erase(child);
}

}
