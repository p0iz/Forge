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

#include "ShaderProgram.h"

#include <GL/glew.h>

#include <vector>

namespace Forge {

ShaderProgram::ShaderProgram():
  mId(0)
{
}

ShaderProgram::~ShaderProgram()
{
  if (mId == 0)
  {
    return;
  }

  int numShaders = 0;
  glGetProgramiv(mId, GL_ATTACHED_SHADERS, &numShaders);

  std::vector<unsigned int> shaders(numShaders);
  glGetAttachedShaders(mId, numShaders, nullptr, &shaders[0]);
  for (unsigned int shader : shaders)
  {
    glDetachShader(mId, shader);
  }
  glDeleteProgram(mId);
}

void ShaderProgram::create()
{
  mId = glCreateProgram();
}

bool ShaderProgram::link()
{
  if (!mId)
  {
    return false;
  }
  glLinkProgram(mId);
  return isLinked();
}

bool ShaderProgram::isLinked() const
{
  GLint linkStatus;
  glGetProgramiv(mId, GL_LINK_STATUS, &linkStatus);
  return linkStatus;
}

const GLuint ShaderProgram::getAttribLocation(const char *attribName) const
{
  return glGetAttribLocation(mId, attribName);
}

int const ShaderProgram::getUniformLocation(const char *uniformName) const
{
  return glGetUniformLocation(mId, uniformName);
}

const unsigned int ShaderProgram::getId()
{
  return mId;
}

bool ShaderProgram::setUniform1fv(char const* name, GLfloat const* values)
{
  GLint location = glGetUniformLocation(mId, name);
  if (location == -1)
  {
    return false;
  }
  glUseProgram(mId);
  glUniform1fv(location, 1, values);
  return true;
}

bool ShaderProgram::setUniform2fv(char const* name, GLfloat const* values)
{
  GLint location = glGetUniformLocation(mId, name);
  if (location == -1)
  {
    return false;
  }
  glUseProgram(mId);
  glUniform2fv(location, 1, values);
  return true;
}

bool ShaderProgram::setUniform3fv(char const* name, GLfloat const* values)
{
  GLint location = glGetUniformLocation(mId, name);
  if (location == -1)
  {
    return false;
  }
  glUseProgram(mId);
  glUniform3fv(location, 1, values);
  return true;
}

bool ShaderProgram::setUniform4fv(char const* name, GLfloat const* values)
{
  GLint location = glGetUniformLocation(mId, name);
  if (location == -1)
  {
    return false;
  }
  glUseProgram(mId);
  glUniform4fv(location, 1, values);
  return true;
}

bool ShaderProgram::setUniform1f(const char* name, GLfloat value)
{
  GLint location = glGetUniformLocation(mId, name);
  if (location == -1)
  {
    return false;
  }
  glUseProgram(mId);
  glUniform1f(location, value);
  return true;
}

const std::string ShaderProgram::getProgramInfoLog() const
{
  std::string logString;
  int logLength = 0;
  glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &logLength);
  logString.reserve(logLength);
  glGetProgramInfoLog(mId, logLength, nullptr, &logString[0]);
  return logString;
}

std::vector<std::string> ShaderProgram::getUniformNames() const
{
  std::vector<std::string> names;

  int numUniforms;
  glGetProgramiv(mId, GL_ACTIVE_UNIFORMS, &numUniforms);
  int maxNameLength;
  glGetProgramiv(mId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

  for (int i = 1; i <= numUniforms; ++i)
  {
    char name[256];
    glGetActiveUniformName(mId, i, sizeof(name), nullptr, name);
    names.push_back(name);
  }

  return names;
}

void ShaderProgram::attachShader(Shader const& shader)
{
  glAttachShader(mId, shader.getId());
}

void ShaderProgram::attachShader(unsigned int shader)
{
  glAttachShader(mId, shader);
}

void ShaderProgram::use() const
{
  glUseProgram(mId);
}

void ShaderProgram::release()
{
  glUseProgram(0);
}

} // namespace Forge
