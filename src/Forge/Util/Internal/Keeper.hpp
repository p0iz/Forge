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

#include <iterator>
#include <vector>


namespace Forge {

// This class stores and allocates memory for any type of classes with a fixed size
template <class ItemType>
class Keeper
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
    }

    std::vector<ItemType>& items()
    {
      return mItems;
    }

    typename std::vector<ItemType>::iterator begin()
    {
      return mItems.begin();
    }

    typename std::vector<ItemType>::iterator end()
    {
      return mItems.end();
    }

    typename std::vector<ItemType>::const_iterator begin() const
    {
      return mItems.begin();
    }

    typename std::vector<ItemType>::const_iterator end() const
    {
      return mItems.end();
    }

  private:
    std::vector<ItemType> mItems;
    std::vector<ItemType*> mFreeList;
};

}
