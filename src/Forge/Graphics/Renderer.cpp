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

#include "Renderer.h"
#include "DebugAxis.h"
#include "GameObject/Component/Camera.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Component/MeshInstance.hpp"
#include "Util/Internal/Keeper.hpp"
#include "Util/ServiceProvider.hpp"
#include "Util/Log.h"
#include "GL/glew.h"


namespace Forge {

Renderer::Renderer()
{
  glClearColor(0.1f,0.1f,0.1f,1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_ONE, GL_ONE);

  if (!glIsEnabled(GL_SCISSOR_TEST))
  {
    Log::info << "Enabling scissor test.\n";
    glEnable(GL_SCISSOR_TEST);
  }
}

Renderer::~Renderer()
{
  for (auto vp : _viewports)
  {
    delete vp.second;
  }
}

void Renderer::addViewport(std::string const& name, Viewport* viewport)
{
  _viewports[name] = viewport;
}

Viewport* Renderer::getViewport(std::string const& name)
{
  return _viewports[name];
}

void Renderer::render()
{
  // Render all viewports
  for (auto it : _viewports)
  {
    Viewport* vp = it.second;
    vp->updateGLViewport();
    Camera const* cam = vp->camera();
  }
}

}
