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


namespace Forge {

class GameObject;

// Component abstract base class
class Component
{
  public:
    explicit Component(GameObject* owner);
    virtual ~Component() {}

    virtual void update() = 0;
    virtual void destroy() = 0;

    GameObject& owner();
    GameObject const& owner() const;

  private:
    GameObject* mOwner;
};

}
