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

#pragma once

#include "ForgeExport.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShaderProgram.h"
#include "Util/Math.hpp"
#include <string>

namespace Forge {

class FORGE_EXPORT Text
{
public:
  ~Text();

  void initialize();
  void setFont(const char* fileName);
  void setFontSize(int pt);
  void setPosition(float x, float y);
  void setColor(float r, float g, float b, float a);
  void setScreenAttributes(int width, int height);
  void setText(const char* text);
  void draw();

  void createBuffer();
private:

  unsigned int pow2(unsigned int n);

  void createShaders();
  void createTexture();

  glm::vec2 mPosition;
  glm::vec2 mScale;

  float color[4];

  Shader vertexShader;
  Shader fragmentShader;
  ShaderProgram textProgram;

  std::string mText;
  std::string _fontName;
  int _fontSize;

  unsigned int glyphTextureId;
  unsigned int glyphTextureUniform;
  unsigned int colorUniform;

  unsigned int glyphVertexArray;
  unsigned int glyphVertexBuffer;
};

} // Forge
