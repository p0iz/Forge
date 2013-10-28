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

#include "TechniqueLibrary.hpp"
#include "TechniqueTraits.hpp"

#include "Graphics/Material/Technique/TechniqueLoader.hpp"

#include "Util/Log.h"

namespace Forge {

template <>
TechniquePtr Graphics::TechniqueLibrary::loadAsset(std::string const& file)
{
  TechniquePtr technique(new Technique);
  TechniqueLoader loader;

  loader.setTarget(*technique);
  if (!loader.loadFile(file))
  {
    technique.reset();
  }

  return technique;
}

}
