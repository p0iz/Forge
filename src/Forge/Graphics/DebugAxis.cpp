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

#include "DebugAxis.h"
#include "Light/Light.hpp"
#include "Shader/Shader.h"
#include "Shader/ShaderProgram.h"
#include "Util/Math.hpp"
#include <iostream>

namespace Forge {

bool showDebug = false;

DebugAxis::DebugAxis()
  : initialized(GL_FALSE)
{
}


void DebugAxis::initialize()
{
  if (initialized)
    return;

  GLfloat debugVertexData[] =
  {
    0,0,0,
    10,0,0,
    0,0,0,
    0,10,0,
    0,0,0,
    0,0,10
  };

  GLfloat debugVertexColor[] =
  {
    1,0,0,
    1,0,0,
    0,1,0,
    0,1,0,
    0,0,1,
    0,0,1
  };

  // create the debug shader program
  debugVertexShader.create(Shader::VertexShader);
  debugVertexShader.loadCode("data/shaders/DebugShader.vert");
  debugVertexShader.compile();

  debugFragmentShader.create(Shader::FragmentShader);
  debugFragmentShader.loadCode("data/shaders/DebugShader.frag");
  debugFragmentShader.compile();

  debugShaderProgram.create();
  debugShaderProgram.attachShader(debugVertexShader.getId());
  debugShaderProgram.attachShader(debugFragmentShader.getId());

  if (!debugShaderProgram.link())
  {
    std::cout << "Debug shader failed with the following output:\n"
          << debugShaderProgram.getProgramInfoLog()
          << std::flush;
  }

  debugUniformMVP = debugShaderProgram.getUniformLocation("MVP");

  // Get vertex array and buffers
  glGenVertexArrays(1, &debugVertexArrayId);
  glGenBuffers(2, debugBuffers);

  // Bind VAO
  glBindVertexArray(debugVertexArrayId);

  // Fill buffers
  glBindBuffer(GL_ARRAY_BUFFER, debugBuffers[0]);
  glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(debugVertexData),
        debugVertexData,
        GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, debugBuffers[1]);
  glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(debugVertexColor),
        debugVertexColor,
        GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // Finished, now unbind
  glBindVertexArray(0);

  initialized = GL_TRUE;
}

void DebugAxis::deinitialize()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glDeleteBuffers(2, debugBuffers);
  glDeleteVertexArrays(1, &debugVertexArrayId);
}

void DebugAxis::toggleDebuggingInfo()
{
  showDebug = !showDebug;
}

void DebugAxis::setDebuggingInfo(bool state)
{
  showDebug = state;
}

bool DebugAxis::isDebugVisible()
{
  return showDebug;
}

DebugAxis::~DebugAxis()
{
}

} // namespace Forge
