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
#include "Camera.hpp"
#include "DebugAxis.h"
#include "Lua/UserdataMap.hpp"
#include "Libraries/MaterialLibrary.hpp"
#include "Scene/SceneConfig.hpp"
#include "Viewport.hpp"
#include "Util/Log.h"
#include "GL/glew.h"


namespace Forge {

Renderer::Renderer():
  mInitialized(false)
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
  mTechnique->addShader(Shader::VertexShader, "data/shaders/DefaultTechnique.vs");
  mTechnique->addShader(Shader::FragmentShader, "data/shaders/DefaultTechnique.fs");
  mTechnique->create();

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

void Renderer::updateViewport(int width, int height)
{
  glViewport(0, 0, width, height);
}

void Renderer::render(const Viewport& viewport, UserdataMap* meshes)
{
  int x = viewport.x();
  int y = viewport.y();
  int width = viewport.width();
  int height = viewport.height();

  glViewport(x, y, width, height);
  glScissor(x, y, width, height);

  static float colR, colG, colB;

  colR = static_cast<float>(random() % 255) / 255;
  colG = static_cast<float>(random() % 255) / 255;
  colB = static_cast<float>(random() % 255) / 255;

  glClearColor(colR,colG,colB,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto nameMesh : *meshes)
  {
    Mesh* mesh = static_cast<Mesh*>(nameMesh.second);
    for (SceneNode const* node : mesh->getAttachedNodes())
    {
      glm::mat4 world = node->mWorldTransform.getMatrix();
      glm::mat4 view = viewport.view();
      glm::mat4 projection = viewport.projection();
      mTechnique->beginMaterial();
      mTechnique->setTransforms(world, view, projection);
      mesh->draw();
    }
  }
}

void Renderer::updateLightData(const SceneConfig& scene, const glm::mat4& view)
{
  for (Light const& light : scene.lights)
  {
    light.getShaderData().viewSpacePosition = view * light.position;
    if (light.type == Light::SPOT)
    {
      light.getShaderData().spotDirection = glm::mat3(view) * light.spotDirection;
    }
  }
}

void Renderer::drawScene(const glm::mat4& view,
               const glm::mat4& projection,
               const SceneConfig& scene)
{
  for (auto materialName : scene.getUsedMaterials()) {
    Material const& material =
        *Graphics::MaterialLibrary::instance().getAssetInfo(materialName).asset;
    bool materialSelected = false;
    std::vector<MeshPtr> const& meshes = material.getMeshes();
    for (Light const& light : scene.lights)
    {
      if (light.type != Light::DISABLED)
      {
        Light::updateBuffer(light.getShaderData());
        for (MeshPtr mesh : meshes) {
          // For each mesh, get the world transform
          for (SceneNode* node : mesh->getAttachedNodes()) {
            if (!materialSelected) {
              material.beginMaterial();
              materialSelected = true;
            }
            const glm::mat4& world = node->mWorldTransform.getMatrix();
            material.setTransforms(world, view, projection);
            mesh->draw();
          }
        }
      }
    }
  }
}

void Renderer::render(const SceneConfig& scene)
{
  glDepthMask(GL_TRUE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const glm::mat4 view = scene.getCamera().getViewMatrix();
  const glm::mat4 projection = scene.getCamera().getProjectionMatrix();

  // Update view space light positions
  updateLightData(scene, view);

  // Z-only prepass
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  drawScene(view, projection, scene);

  // Render debug overlay
  if (DebugAxis::isDebugVisible()) {
    mDebugAxis.render(scene);
  }

  // Actual rendering
  glDepthFunc(GL_LEQUAL);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glDepthMask(GL_FALSE);

  glEnable(GL_BLEND);
  drawScene(view, projection, scene);

  // Render debug overlay
  if (DebugAxis::isDebugVisible()) {
    mDebugAxis.render(scene);
  }

  glDisable(GL_BLEND);

  // Post process
}

void Renderer::renderDebugOverlay(const SceneConfig& scene)
{
}

}
