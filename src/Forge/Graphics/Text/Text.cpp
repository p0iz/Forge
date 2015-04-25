/*
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
#include "Util/Log.h"
#include "Util/Math.hpp"
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
}

void Forge::Text::initialize()
{
  if (!TTF_WasInit() && TTF_Init() == -1)
  {
      Log::error << "TTF library failed to initialize! Error: " << TTF_GetError() << "\n";
  }

  // Create shaders
  createShaders();

  // Create glyph texture
  createTexture();

  // Create VBO
  createBuffer();
}

void Forge::Text::setFont(const char * fileName)
{
  _fontName = fileName;
}

void Forge::Text::setFontSize(int pt)
{
  _fontSize = pt;
}

void Forge::Text::setPosition(float x, float y)
{
  mPosition.x = x;
  mPosition.y = y;
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

  TTF_Font* font = TTF_OpenFont(_fontName.c_str(), _fontSize);

  static SDL_Color black { 0, 0, 0, 255 };

  SDL_Surface* renderedText = TTF_RenderText_Blended(font, mText.c_str(), black);

  float x = mPosition.x;
  float y = mPosition.y;

  int width = renderedText->w;
  int height = renderedText->h;

  unsigned char* convertedPixels = new unsigned char[width*height];

  Log::info << "Colors in renderedText: " << renderedText->format->palette->ncolors << "\n";

  Log::info << "Bytes per pixel: " << renderedText->pitch / renderedText->w << "\n";

  for (int i = 0; i < width * height; ++i)
  {
    int index = static_cast<int*>(renderedText->pixels)[i];
    SDL_Color* color = &renderedText->format->palette->colors[index];
    convertedPixels[i] = 0.212671f * color->r + 0.715160f * color->g + 0.072169f * color->b;
  }
  SDL_FreeSurface(renderedText);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RED,
    width,
    height,
    0,
    GL_RED,
    GL_UNSIGNED_BYTE,
    convertedPixels
  );

  delete[] convertedPixels;

  glm::vec2 vertCoords[] =
  {
    glm::vec2(x, y),
    glm::vec2(0, 1),
    glm::vec2(x + width, y),
    glm::vec2(1, 1),
    glm::vec2(x, y + height),
    glm::vec2(0, 0),
    glm::vec2(x + width, y + height),
    glm::vec2(1, 0)
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertCoords), vertCoords, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, (void*)sizeof(glm::vec2));

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  TTF_CloseFont(font);

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
}

void Forge::Text::setText(const char* text)
{
  mText.assign(text);
}


void Forge::Text::setColor(float r, float g, float b, float a)
{
  textProgram.use();
  glUniform4f(colorUniform, r, g, b, a);
  textProgram.release();
}
