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

#include "SimpleColor.hpp"

#include "Graphics/Light/Light.hpp"
#include "Util/Log.h"

namespace Forge {

SimpleColor::SimpleColor()
  : Technique("SimpleColor")
{
}

Technique* SimpleColor::clone()
{
  return new SimpleColor;
}


void SimpleColor::create()
{
  // Craft the test cube shaders
  vertexShader.create(GL_VERTEX_SHADER);
  vertexShader.loadCode("data/shaders/SimpleTexture.vs"); // same vertex shader as SimpleTexture
  vertexShader.compile();
  fragmentShader.create(GL_FRAGMENT_SHADER);
  fragmentShader.loadCode("data/shaders/SimpleColor.fs");
  fragmentShader.compile();
  shaderProgram.create();
  shaderProgram.setVertexShader(vertexShader.getId());
  shaderProgram.setFragmentShader(fragmentShader.getId());
  if (shaderProgram.link() != GL_TRUE)
  {
    Log::info << shaderProgram.getProgramInfoLog();
  }
  // Setup light uniform buffer binding
  lightsUniformIndex = glGetUniformBlockIndex(shaderProgram.getId(), "Lights");
  glUniformBlockBinding(shaderProgram.getId(), lightsUniformIndex, Light::UNIFORM_BINDING_POINT);

  // Get uniform locations
  wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
  wvLocation = shaderProgram.getUniformLocation("WorldViewMatrix");
  nLocation = shaderProgram.getUniformLocation("NormalMatrix");

  materialAmbientLoc = shaderProgram.getUniformLocation("MaterialAmbient");
  materialDiffuseLoc = shaderProgram.getUniformLocation("MaterialDiffuse");
  materialSpecularLoc = shaderProgram.getUniformLocation("MaterialSpecular");
  materialShininessLoc = shaderProgram.getUniformLocation("MaterialShininess");
}

void SimpleColor::destroy()
{
}

void SimpleColor::updateProperties(LuaProperties &properties)
{
  shaderProgram.use();

  // Ambient color reflectivity
  if (properties.hasProperty("ambient"))
  {
    glUniform3fv(materialAmbientLoc, 1, &properties.getFloatArray("ambient")[0]);
  }

  // Diffuse color reflectivity
  if (properties.hasProperty("diffuse"))
  {
    glUniform3fv(materialDiffuseLoc, 1, &properties.getFloatArray("diffuse")[0]);
  }

  // Specular color reflectivity
  if (properties.hasProperty("specular"))
  {
    glUniform3fv(materialSpecularLoc, 1, &properties.getFloatArray("specular")[0]);
  }

  // Shininess
  if (properties.hasProperty("shininess"))
  {
    glUniform1f(materialShininessLoc, properties.getFloat("shininess"));
  }
}

void SimpleColor::beginMaterial()
{
  shaderProgram.use();
}

void SimpleColor::setTransforms(
    glm::mat4 const& world,
    glm::mat4 const& view,
    glm::mat4 const& projection
  )
{
  // Update
  const glm::mat4x4 worldViewTransform = view * world;
  const glm::mat3x3 normalMatrix(worldViewTransform);
  glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(projection * worldViewTransform)[0][0]);
  glUniformMatrix4fv(wvLocation, 1, GL_FALSE, &worldViewTransform[0][0]);
  glUniformMatrix3fv(nLocation, 1, GL_FALSE, &normalMatrix[0][0]);
}

}
