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
#include "Application/Application.hpp"
#include "DebugAxis.h"
#include "GameObject/Component/Camera.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Component/MeshInstance.hpp"
#include "Util/Internal/Keeper.hpp"
#include "Viewport.hpp"
#include "Util/Log.h"
#include "GL/glew.h"


namespace Forge {

Renderer::Renderer(Application& app):
  mInitialized(false),
  mApp(app)
{
}

Renderer::~Renderer()
{
}

void Renderer::initialize()
{
  if (mInitialized) return;

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

  mDebugAxis.initialize();

  mTechnique = new Technique;
  mTechnique->addShader(Shader::VertexShader, "data/shaders/SimpleTexture.vs");
  mTechnique->addShader(Shader::FragmentShader, "data/shaders/SimpleColor.fs");
  mTechnique->create();

  mTechnique->setUniform("ambient", glm::vec3(0.1f,0.1f,0.1f));
  mTechnique->setUniform("diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
  mTechnique->setUniform("specular", glm::vec3(1.0f, 1.0f, 1.0f));
  mTechnique->setUniform("shininess", 512.0f);

  Light::createBuffer();

  mInitialized = true;
}

void Renderer::deinitialize()
{
  if (!mInitialized) return;

  if (mTechnique)
  {
    delete mTechnique;
    mTechnique = nullptr;
  }

  Light::destroyBuffer();
  mDebugAxis.deinitialize();
  mInitialized = false;
}

void Renderer::render(Viewport const& viewport)
{
  int x = viewport.x();
  int y = viewport.y();
  int width = viewport.width();
  int height = viewport.height();

  glViewport(x, y, width, height);
  glScissor(x, y, width, height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 view = viewport.view();
  glm::mat4 projection = viewport.projection();

  updateLightData(view);

  mTechnique->beginMaterial();

  for (Light const& light : mApp.lights())
  {
    if (light.type != Light::DISABLED)
    {
      Light::updateBuffer(light.getShaderData());
      for (MeshInstance& mi : mApp.meshes())
      {
        glm::mat4 world = mi.owner().transform().getMatrix();
        mTechnique->setTransforms(world, view, projection);
        mi.update();
      }
    }
  }
}

void Renderer::updateLightData(glm::mat4 const& view)
{
  for (Light const& light : mApp.lights())
  {
    light.getShaderData().viewSpacePosition = view * light.position;
    if (light.type == Light::SPOT)
    {
      light.getShaderData().spotDirection = glm::mat3(view) * light.spotDirection;
    }
  }
}

}
