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

#include "Graphics/OpenGL/PixelStore.hpp"
#include "Graphics/OpenGL/DepthTest.hpp"
#include "Graphics/OpenGL/Blending.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <iostream>

#include <GL/glew.h>

void Forge::Text::createShaders()
{
	vertexShader.create(Shader::Type::VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/TextShader.vert");
	fragmentShader.create(Shader::Type::FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/TextShader.frag");
	assert(vertexShader.compile() && fragmentShader.compile());
	textProgram.create();
	textProgram.setVertexShader(vertexShader.getId());
	textProgram.setFragmentShader(fragmentShader.getId());
	if (textProgram.link() == false)
	{
		std::cout << textProgram.getProgramInfoLog();
	}

	// Acquire uniforms
	glyphTextureUniform = textProgram.getUniformLocation("glyphTexture");
	colorUniform = textProgram.getUniformLocation("textColor");
}

void Forge::Text::createTexture()
{
	glyphTexture.create(Texture::Target::TEXTURE_2D);

	glyphTexture.bind();
	glyphTexture.setWrapping(Texture::Wrap::CLAMP_EDGE, Texture::Wrap::CLAMP_EDGE);
	glyphTexture.setFiltering(Texture::Filter::LINEAR, Texture::Filter::LINEAR);
	glyphTexture.release();

	textProgram.use();
	int glyphTextureSampler = 0;
	textProgram.setUniform(glyphTextureUniform, 1, 1, &glyphTextureSampler);
	textProgram.release();
}

void Forge::Text::createBuffer()
{
	glyphVertexArray.create();
	glyphVertexBuffer.create(Buffer::Target::VERTEX_BUFFER);
	glyphVertexArray.bind();
	glyphVertexBuffer.bind();

	glyphVertexArray.setAttribute(0,
								  2,
								  VertexArray::ElementType::FLOAT,
								  false,
								  sizeof(glm::vec2)*2,
								  0);
	glyphVertexArray.enableAttribute(0);

	glyphVertexArray.setAttribute(1,
								  2,
								  VertexArray::ElementType::FLOAT,
								  false,
								  sizeof(glm::vec2)*2,
								  (void*)sizeof(glm::vec2));
	glyphVertexArray.enableAttribute(1);

	glyphVertexArray.release();
}

Forge::Text::~Text()
{
	FT_Done_FreeType(static_cast<FT_Library>(mFontLibrary));
}

void Forge::Text::initialize()
{
	// Initialize FreeType
	assert(!FT_Init_FreeType(&mFontLibrary));

	// Create shaders
	createShaders();

	// Create glyph texture
	createTexture();

	// Create VBO
	createBuffer();
}

void Forge::Text::setFont(const char * fileName)
{
	assert(!FT_New_Face(mFontLibrary, fileName, 0, &face));
	glyph = face->glyph;
}

void Forge::Text::setFontSize(int pt)
{
	FT_Set_Pixel_Sizes(face, 0, pt);
}

void Forge::Text::setPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Forge::Text::draw()
{
	glyphVertexArray.bind();

	textProgram.use();

	Texture::setActiveUnit(Texture::Unit::TEXTURE0);
	glyphTexture.bind();

	float posX = mPosition.x;
	float posY = mPosition.y;

	DepthTest::disable();

	Blending::enable();
	Blending::setFunction(Blending::Factor::SRC_ALPHA, Blending::Factor::ONE_MINUS_SRC_ALPHA);

	PixelStore::setUnpackAlignment(1);

	for (char c : mText)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			continue;

		glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					glyph->bitmap.width,
					glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					glyph->bitmap.buffer);

		float x = posX + (glyph->bitmap_left * mScale.x);
		float y = posY - ((glyph->bitmap.rows - glyph->bitmap_top) * mScale.y);

		float width = glyph->bitmap.width * mScale.x;
		float height = glyph->bitmap.rows * mScale.y;

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

		glyphVertexBuffer.setData(sizeof(vertCoords), vertCoords, Buffer::Usage::DYNAMIC_DRAW);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		posX += (glyph->advance.x >> 6) * mScale.x;
		posY += (glyph->advance.y >> 6) * mScale.y;
	}

	PixelStore::setUnpackAlignment(4);

	Blending::disable();

	DepthTest::enable();

	glyphTexture.release();
	textProgram.release();
	glyphVertexArray.release();
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
	float color[] = { r, g, b, a };
	textProgram.setUniform(colorUniform, 1, 4, color);
	textProgram.release();
}
