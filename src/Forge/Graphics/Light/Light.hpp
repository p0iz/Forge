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

#pragma once

#include "Graphics/Scene/Attachable.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


namespace Forge {

/* Describes a light in the game world */
struct Light {
  Light();
  ~Light();

  /* Appends the data memory location for reuse */
  void releaseDataIndex();

  enum LightType {
    DIRECTIONAL,
    POINT,
    SPOT,
    DISABLED
  };

  LightType type;
  glm::vec4 position;
  glm::vec3 spotDirection;
  int dataIndex;


  /* Light data structure for shaders */
  struct Data {
    Data() :
      viewSpacePosition(0.0f),
      color(0.0f),
      attenuation({ 0.1f, 0.1f, 0.00025f }),
      spotExponent(0.0f),
      spotDirection(0.0f),
      spotCutoff(0.0f),
      spotFalloff(0.0f) { }

    glm::vec4 viewSpacePosition;
    glm::vec4 color; // alpha component describes light intensity
    struct {
      float constant;
      float linear;
      float quadratic;
    } attenuation; // distance attenuation

    // Spotlight
    float spotExponent;
    glm::vec3 spotDirection; // spot direction.
    float spotCutoff; // cutoff angle (in degrees when specified, calculated to cosine when used)
    float spotFalloff; // falloff angle (in degrees when specified, calculated to cosine when used)

    // Padding for std140 GLSL layout
    float padding[3];
  };

  /* Initializes the buffer used for light uniforms */
  static void createBuffer();
  /* Destroys the buffer used for light uniforms */
  static void destroyBuffer();
  /* Uploads the selected data into the uniform */
  static void updateBuffer(Data const& lightData);

  static const int UNIFORM_BINDING_POINT = 1;

  Data& getShaderData() const;

private:
  static unsigned int mLightUniformBuffer;

  // Keep all shader data in contiguous memory
  static std::vector<Data> shaderData;
  // Store destroyed light data indices to reuse memory locations
  static std::vector<int> freeList;
};

}
