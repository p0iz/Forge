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

#include "Text.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <iostream>
#include <SDL2/SDL_ttf.h>

void Forge::Text::createShaders()
{
  vertexShader.create(Shader::VertexShader);
  vertexShader.loadCode("data/shaders/TextShader.vert");
  fragmentShader.create(Shader::FragmentShader);
  fragmentShader.loadCode("data/shaders/TextShader.frag");
  assert(vertexShader.compile() && fragmentShader.compile());
  textProgram.create();
  textProgram.attachShader(vertexShader.getId());
  textProgram.attachShader(fragmentShader.getId());
  if (textProgram.link() != GL_TRUE)
  {
    std::cout << textProgram.getProgramInfoLog();
  }

  // Acquire uniforms
  glyphTextureUniform = textProgram.getUniformLocation("glyphTexture");
  colorUniform = textProgram.getUniformLocation("textColor");
}

void Forge::Text::createTexture()
{
  glGenTextures(1, &glyphTextureId);
  glBindTexture(GL_TEXTURE_2D, glyphTextureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  textProgram.use();
  glUniform1i(glyphTextureUniform, 0);
  textProgram.release();
}

void Forge::Text::createBuffer()
{
  glGenVertexArrays(1, &glyphVertexArray);
  glBindVertexArray(glyphVertexArray);
  glGenBuffers(1, &glyphVertexBuffer);
  glBindVertexArray(0);
}

Forge::Text::~Text()
{
  if (_font)
  {
    TTF_CloseFont(_font);
  }
  if (--_refCount == 0)
  {
    TTF_Quit();
  }
}

void Forge::Text::initialize()
{
  // Initialize FreeType
  if (!TTF_WasInit())
  {
    TTF_Init();
    ++_refCount;
  }

  _textRendered = false;

  // Create shaders
  createShaders();

  // Create VBO
  createBuffer();
}

void Forge::Text::setFont(const char * fileName)
{
  if (_font)
  {
    TTF_CloseFont(_font);
    _font = nullptr;
  }
  _font = TTF_OpenFont(fileName, _fontPtSize);
  _textRendered = false;
}

void Forge::Text::setFontSize(int pt)
{
  if (pt != _fontPtSize)
  {
    _fontPtSize = pt;
    _textRendered = false;
  }
}

void Forge::Text::setPosition(float x, float y)
{
  if (x != mPosition.x || y != mPosition.y)
  {
    mPosition.x = x;
    mPosition.y = y;
    _textRendered = false;
  }
}

void Forge::Text::draw()
{
  glBindVertexArray(glyphVertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, glyphVertexBuffer);

  textProgram.use();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, glyphTextureId);

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  if (!_textRendered)
  {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(_font, mText.c_str(), { 0, 0, 0 });
    int colors = surface->format->BytesPerPixel;
    GLenum texture_format = GL_RGBA;
    if (colors == 4) {   // alpha
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGBA;
      else
        texture_format = GL_BGRA;
    }
    else {             // no alpha
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGB;
      else
        texture_format = GL_BGR;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, colors, surface->w, surface->h, 0,
      texture_format, GL_UNSIGNED_BYTE, surface->pixels);

    glm::vec2 vertCoords[] =
    {
      glm::vec2(mPosition.x, mPosition.y),
      glm::vec2(0, 1),
      glm::vec2(mPosition.x + surface->w, mPosition.y),
      glm::vec2(1, 1),
      glm::vec2(mPosition.x, mPosition.y + surface->h),
      glm::vec2(0, 0),
      glm::vec2(mPosition.x + surface->w, mPosition.y + surface->h),
      glm::vec2(1, 0)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertCoords), vertCoords, GL_DYNAMIC_DRAW);
    _textRendered = true;
  }

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, (void*)sizeof(glm::vec2));

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBindTexture(GL_TEXTURE_2D, 0);
  textProgram.release();
  glBindVertexArray(0);
}

unsigned int Forge::Text::pow2(unsigned int n)
{
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;
  return n;
}

void Forge::Text::setScreenAttributes(int width, int height)
{
  textProgram.use();
  mScale.x = 2.0f / width;
  mScale.y = 2.0f / height;
  textProgram.release();
  _textRendered = false;
}

void Forge::Text::setText(const char* text)
{
  mText.assign(text);
  _textRendered = false;
}


void Forge::Text::setColor(float r, float g, float b, float a)
{
  textProgram.use();
  glUniform4f(colorUniform, r, g, b, a);
  textProgram.release();
  _textRendered = false;
}
