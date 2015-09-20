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

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"
#include <string>
#include <vector>


namespace Forge {

// Class for shader programs
class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

  void create();
  bool link();

  bool isLinked() const;

  const unsigned int getAttribLocation(const char* attribName) const;
  int const getUniformLocation(const char* uniformName) const;
  const unsigned int getId();

  bool setUniform1fv(char const* name, GLfloat const* values);
  bool setUniform2fv(char const* name, GLfloat const* values);
  bool setUniform3fv(char const* name, GLfloat const* values);
  bool setUniform4fv(char const* name, GLfloat const* values);
  bool setUniform1f(char const* name, GLfloat value);

  const std::string getProgramInfoLog() const;

  std::vector<std::string> getUniformNames() const;

  void attachShader(Shader const& shader);
  void attachShader(unsigned int shader);

  void use() const;

  static void release();

private:
  unsigned int mId;

};

} // namespace Forge

#endif // SHADERPROGRAM_H
