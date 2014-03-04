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

#include "Util/Singleton.hpp"
#include <vector>


// This class stores and allocates memory for any type of classes with a fixed size
template <class ItemType>
class Keeper : public Singleton<Keeper<ItemType>>
{
  public:
    void clear()
    {
      mItems.clear();
      mFreeList.clear();
    }

    template<class... Args>
    ItemType* create(Args... args)
    {
      ItemType* item = nullptr;
      if (mFreeList.empty())
      {
        mItems.emplace_back(args...);
        item = &mItems.back();
      }
      else
      {
        item = new (mFreeList.back()) ItemType(args...);
        mFreeList.pop_back();
      }
      return item;
    }

    void destroy(ItemType* item)
    {
      mFreeList.push_back(item);
      item->~ItemType();
    }

    std::vector<ItemType>& items()
    {
      return mItems;
    }

  private:
    std::vector<ItemType> mItems;
    std::vector<ItemType*> mFreeList;
};
