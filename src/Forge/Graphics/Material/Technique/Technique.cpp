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

#include "Technique.hpp"
#include "Graphics/Light/Light.hpp"
#include "Util/Log.h"
#include <fstream>
#include <sstream>


namespace Forge {

namespace {

static std::pair<char const*, Technique::TransformType> const transforms[] =
{
  { "WorldViewProjection", Technique::WorldViewProjection },
  { "WorldViewMatrix", Technique::WorldView },
  { "NormalMatrix", Technique::NormalMatrix }
};

}

Technique::Technique():
  mName(),
  mProgram(),
  mTransformLocations()
{
  mProgram.create();
}

Technique::~Technique()
{
  mProgram.release();
}

void Technique::beginMaterial()
{
  mProgram.use();
}

void Technique::setupTransforms()
{
  if (!mProgram.isLinked())
  {
    return;
  }

  for (auto& transformPair : transforms)
  {
    auto location = mProgram.getUniformLocation(transformPair.first);
    if (location > -1)
    {
      mTransformLocations[transformPair.second] = location;
    }
  }
}

void Technique::setupLightBufferBinding()
{
  // Setup light uniform buffer binding
  unsigned int lightsUniformIndex = glGetUniformBlockIndex(mProgram.getId(), "Lights");
  glUniformBlockBinding(mProgram.getId(), lightsUniformIndex, Light::UNIFORM_BINDING_POINT);
}

void Technique::addShader(Shader::ShaderType type, const std::string& file)
{
  Shader shader;
  shader.create(type);
  shader.loadCode(file);
  if (shader.compile())
  {
    mProgram.attachShader(shader);
  }
}

void Technique::create()
{
  if (mProgram.link())
  {
    setupTransforms();
    setupLightBufferBinding();
  }
  else
  {
    Log::error << mProgram.getProgramInfoLog();
  }
}

void Technique::setTransforms(
    glm::mat4 const& world,
    glm::mat4 const& view,
    glm::mat4 const& projection
)
{
  for (auto const& pair : mTransformLocations)
  {
    switch (pair.first)
    {
      case WorldViewProjection:
      {
        glm::mat4 wvp = projection * view * world;
        glUniformMatrix4fv(pair.second, 1, GL_FALSE, &wvp[0][0]);
        break;
      }
      case WorldView:
      {
        glm::mat4 wv = view * world;
        glUniformMatrix4fv(pair.second, 1, GL_FALSE, &wv[0][0]);
        break;
      }
      case World:
      {
        glUniformMatrix4fv(pair.second, 1, GL_FALSE, &world[0][0]);
        break;
      }
      case NormalMatrix:
      {
        glm::mat3 normal(view * world);
        glUniformMatrix3fv(pair.second, 1, GL_FALSE, &normal[0][0]);
        break;
      }
      default:
        break;
    }
  }
}

void Technique::setName(const std::string& name)
{
  mName = name;
}

std::string const& Technique::getName() const
{
  return mName;
}

bool Technique::setUniform(std::string const& uniformName, glm::vec3 const& vector)
{
  return mProgram.setUniform3fv(uniformName.c_str(), &vector[0]);
}

bool Technique::setUniform(std::string const& uniformName, int length, float const* values)
{
  switch (length)
  {
    case 1:
      return mProgram.setUniform1fv(uniformName.c_str(), values);
    case 2:
      return mProgram.setUniform2fv(uniformName.c_str(), values);
    case 3:
      return mProgram.setUniform3fv(uniformName.c_str(), values);
    case 4:
      return mProgram.setUniform4fv(uniformName.c_str(), values);
    default:
      return false;
  }
}

bool Technique::setUniform(std::string const& uniformName, float value)
{
  return mProgram.setUniform1f(uniformName.c_str(), value);
}

std::vector<std::string> Technique::getUniformNames() const
{
  return mProgram.getUniformNames();
}

}
