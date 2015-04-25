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

#include "DebugAxis.h"
#include "ForgeExport.h"
#include "Graphics/Light/Light.hpp"
#include "Graphics/Viewport.hpp"
#include "Material/Technique/Technique.hpp"
#include "Util/Math.hpp"

#include <unordered_map>

namespace Forge {

/* A class that is used to render scenes from scene configurations */
class FORGE_EXPORT Renderer
{
public:
  Renderer();
  ~Renderer();

  void render();

  void addViewport(std::string const& name, Viewport* viewport);
  Viewport* getViewport(std::string const& name);

private:
  std::unordered_map<std::string, Viewport*> _viewports;
};

}
