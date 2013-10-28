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

#include "Shader.h"

#include <cassert>
#include <fstream>
#include <sstream>

namespace Forge {

Shader::Shader()
  : mId(0), mType(0)
{
}

Shader::~Shader()
{
  if (mId)
  {
    glDeleteShader(mId);
  }
}

void Shader::create(ShaderType type)
{
  if (mId)
  {
    glDeleteShader(mId);
  }
  mType = type;
  mId = glCreateShader(type);
}

const GLint Shader::compile()
{
  glCompileShader(mId);
  GLint result = GL_FALSE;
  glGetShaderiv(mId, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    printInfoLog();
  }
  return result;
}

std::string Shader::getInfoLog() const
{
  std::string infoLog;
  int logLength;
  glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &logLength);
  char* shaderInfoLog = new char[logLength];
  glGetShaderInfoLog(mId, logLength, NULL, shaderInfoLog);
  infoLog.assign(shaderInfoLog);
  delete[] shaderInfoLog;
  return infoLog;
}

void Shader::printInfoLog() const
{
  std::string infoLog = getInfoLog();

  const char* shaderType = nullptr;
  switch (mType)
  {
  case GL_FRAGMENT_SHADER:
    shaderType = "fragment";
    break;
  case GL_VERTEX_SHADER:
    shaderType = "vertex";
    break;
  case GL_GEOMETRY_SHADER:
    shaderType = "geometry";
    break;
  }

  printf("Error while compiling %s shader: %s\n",
       shaderType,
       infoLog.c_str());
}

void Shader::loadCode(const std::string& file)
{
  std::ifstream shaderFile(file);
  if (shaderFile)
  {
    std::stringstream shaderBuffer;
    shaderBuffer << shaderFile.rdbuf();
    std::string shaderCode(shaderBuffer.str());
    const char* code = shaderCode.c_str();
    int codeLength = shaderCode.length();
    glShaderSource(mId, 1, &code, &codeLength);
  }
}

} // namespace Forge
