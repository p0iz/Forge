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

#include "DefaultTechnique.h"
#include "Util/Log.h"
#include "Util/Math.hpp"

namespace Forge {

DefaultTechnique::DefaultTechnique()
  : Technique()
{
  vertexShader.create(Shader::VertexShader);
  vertexShader.loadCode("data/shaders/DefaultTechnique.vs");
  vertexShader.compile();
  fragmentShader.create(Shader::FragmentShader);
  fragmentShader.loadCode("data/shaders/DefaultTechnique.fs");
  fragmentShader.compile();
  shaderProgram.create();
  shaderProgram.attachShader(vertexShader.getId());
  shaderProgram.attachShader(fragmentShader.getId());
  if (!shaderProgram.link())
  {
    Log::error << shaderProgram.getProgramInfoLog();
  }

  // Get uniform location
  wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
}

TechniquePtr DefaultTechnique::clone()
{
  return TechniquePtr(new DefaultTechnique);
}

void DefaultTechnique::beginMaterial()
{
  shaderProgram.use();
}

void DefaultTechnique::setTransforms(const glm::mat4& world,
                const glm::mat4& view,
                const glm::mat4& projection)
{
  // Update
  const glm::mat4x4 wvp = projection * view * world;
  glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(wvp)[0][0]);
}

}
