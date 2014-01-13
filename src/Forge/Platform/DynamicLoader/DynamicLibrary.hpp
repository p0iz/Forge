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

#pragma once

#include "ForgeExport.h"
#include "LibraryHandle.hpp"
#include <unordered_map>


namespace Forge {

class FORGE_EXPORT DynamicLibrary
{
  public:
    DynamicLibrary();
    explicit DynamicLibrary(LibraryHandle handle);
    ~DynamicLibrary();

    void setHandle(LibraryHandle handle);

    template <class ReturnType>
    ReturnType loadSymbol(std::string const& symbol);

    bool isValid() const;

  private:
    LibraryHandle mHandle;
    typedef std::unordered_map<std::string, void*> SymbolMap;
    SymbolMap mSymbolCache;

    void* getSymbol(std::string const& symbol);

    void freeHandle();

};

template <class ReturnType>
ReturnType DynamicLibrary::loadSymbol(std::string const& symbol)
{
  ReturnType loadedSymbol;
  void* symbolPtr = nullptr;
  if (mHandle)
  {
    if (mSymbolCache.count(symbol) == 0)
    {
      symbolPtr = getSymbol(symbol);
      if (symbolPtr)
      {
        mSymbolCache[symbol] = symbolPtr;
      }
    }
    else
    {
      symbolPtr = mSymbolCache.at(symbol);
    }
  }
  *reinterpret_cast<void**>(&loadedSymbol) = symbolPtr;
  return loadedSymbol;
}

}
