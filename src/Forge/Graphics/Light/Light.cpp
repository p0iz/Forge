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

#include "Light.hpp"


namespace Forge {

std::vector<Light::Data> shaderData;
std::vector<int> freeList;

unsigned int lightUniformBuffer = 0;

Light::Light():
  type(DISABLED),
  position(0.0f),
  dataIndex(0)
{
  if (freeList.size())
  {
    int newIndex = freeList.back();
    freeList.pop_back();
    dataIndex = newIndex;
    shaderData[dataIndex] = Light::Data();
  }
  else
  {
    shaderData.push_back(Light::Data());
    dataIndex = shaderData.size() - 1;
  }
}

Light::~Light()
{
}

void Light::releaseDataIndex()
{
  freeList.push_back(dataIndex);
}

Light::Data& Light::getShaderData() const
{
  return shaderData[dataIndex];
}

void Light::createBuffer() {
  glGenBuffers(1, &lightUniformBuffer);
  glBindBuffer(GL_UNIFORM_BUFFER, lightUniformBuffer);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(Light::Data), nullptr, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, UNIFORM_BINDING_POINT, lightUniformBuffer);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Light::destroyBuffer() {
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glDeleteBuffers(1, &lightUniformBuffer);
}

void Light::updateBuffer(Data const& lightData) {
  glBindBuffer(GL_UNIFORM_BUFFER, lightUniformBuffer);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light::Data), &lightData);
}


}
