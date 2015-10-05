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
#include "Mesh.h"
#include "Scene/SceneNode.hpp"
#include "Lua/UserdataMap.hpp"
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

  mWindow.makeRenderCurrent();
  mWindow.resize(640,480);
  mWindow.show();
  mWindow.setTitle("Forge");

  glClearColor(0.1f,0.1f,0.1f,1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_ONE, GL_ONE);

  if (!glIsEnabled(GL_SCISSOR_TEST))
  {
    glEnable(GL_SCISSOR_TEST);
  }

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

  mWindow.hide();

  if (mTechnique)
  {
    delete mTechnique;
    mTechnique = nullptr;
  }

  Light::destroyBuffer();

  mInitialized = false;
}

void Renderer::updateViewport(int width, int height)
{
  glViewport(0, 0, width, height);
}

void Renderer::frameUpdate()
{
  if (!mMeshes || !mLights)
  {
    return;
  }

  for (auto nameViewport : mViewports)
  {
    if (nameViewport.second)
    {
      render(*static_cast<Viewport const*>(nameViewport.second), mMeshes, *mLights);
    }
  }

  mWindow.swapBuffers();
}

void Renderer::render(const Viewport& viewport, UserdataMap* meshes, std::vector<Light> const& lights)
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

  updateLightData(lights, view);

  for (Light const& light : lights)
  {
    if (light.type != Light::DISABLED)
    {
      Light::updateBuffer(light.getShaderData());
      for (auto nameMesh : *meshes)
      {
        Mesh* mesh = static_cast<Mesh*>(nameMesh.second);
        for (SceneNode const* node : mesh->getAttachedNodes())
        {
          glm::mat4 world = node->mWorldTransform.getMatrix();
          mTechnique->beginMaterial();
          mTechnique->setTransforms(world, view, projection);
          mesh->draw();
        }
      }
    }
  }
}

void Renderer::updateLightData(const std::vector<Light>& lights, const glm::mat4& view)
{
  for (Light const& light : lights)
  {
    light.getShaderData().viewSpacePosition = view * light.position;
    if (light.type == Light::SPOT)
    {
      light.getShaderData().spotDirection = glm::mat3(view) * light.spotDirection;
    }
  }
}

void Renderer::setMeshAssets(UserdataMap* meshmap)
{
  mMeshes = meshmap;
}

void Renderer::setLights(std::vector<Light>* lights)
{
  mLights = lights;
}

RenderWindow const& Renderer::window()
{
  return mWindow;
}

void Renderer::addViewport(const std::string& name, Viewport* viewport)
{
  mViewports[name] = viewport;
}

Viewport* Renderer::getViewport(const std::string& name)
{
  return mViewports[name];
}

}
