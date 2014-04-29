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

#include "ForgeExport.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShaderProgram.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>


namespace Forge {

/* Technique is comprised of one or several shader passes and accompanying properties */
class FORGE_EXPORT Technique
{
public:
  enum TransformType
  {
    World,
    View,
    Projection,
    WorldView,
    ViewProjection,
    WorldViewProjection,
    NormalMatrix
  };

  Technique();
  ~Technique();

  // 1. Add shaders to the technique
  void addShader(Shader::ShaderType type, std::string const& file);

  // 2. Link the technique program, setup built-in uniform variables (transforms)
  void create();

  // Called when starting to draw a mesh (TODO: Optimize!)
  void setTransforms(
      glm::mat4 const& world,
      glm::mat4 const& view,
      glm::mat4 const& projection
  );

  void setName(std::string const& name);
  std::string const& getName() const;

  bool setUniform(std::string const& uniformName, glm::vec3 const& vector);
  bool setUniform(std::string const& uniformName, int length, float const* values);
  bool setUniform(std::string const& uniformName, float value);

  std::vector<std::string> getUniformNames() const;

  // Called when starting to draw with the technique
  void beginMaterial();

private:
  Technique(Technique const&);
  Technique& operator=(Technique const&);

  std::string mName;
  ShaderProgram mProgram;
  std::unordered_map<int, unsigned int> mTransformLocations;

  // Checks which transforms are required after compiling the program
  void setupTransforms();

  // Sets up a light buffer
  void setupLightBufferBinding();

};

typedef std::shared_ptr<Technique> TechniquePtr;

}
