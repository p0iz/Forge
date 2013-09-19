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

#include "MaterialLoader.hpp"
#include "MaterialTraits.hpp"
#include "Graphics/Vertex.h"
#include "Util/Log.h"

#include <algorithm>
#include <fstream>
#include <sstream>


namespace Forge {

template <>
MaterialPtr AssetLoader<Material>::loadAsset(std::string const& file)
{
  MaterialPtr material(new Material);
  material->loadMaterial(file);
  return material;
}

}
