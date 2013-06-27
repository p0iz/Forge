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

#include "VertexArray.hpp"

#include <GL/glew.h>

namespace Forge {

VertexArray::VertexArray() : mName(-1)
{
}

void VertexArray::create()
{
	if (mName == -1)
	{
		glGenVertexArrays(1, &mName);
	}
}

void VertexArray::destroy()
{
	// Delete vertex array
	release();
	glDeleteVertexArrays(1, &mName);
	mName = -1;
}

void VertexArray::bind()
{
	int currentVertexArray;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVertexArray);
	if (static_cast<unsigned int>(currentVertexArray) != mName) {
		glBindVertexArray(mName);
	}
}

void VertexArray::setAttribute(const unsigned int location,
							   const unsigned int elements,
							   const ElementType type,
							   const bool normalized,
							   const unsigned int stride,
							   const void* offset)
{
	glVertexAttribPointer(location,
						  elements,
						  getGLType(type),
						  normalized ? GL_TRUE : GL_FALSE,
						  stride,
						  offset);
}

void VertexArray::release()
{
	glBindVertexArray(0);
}

int VertexArray::getGLType(ElementType type)
{
	switch (type)
	{
	case ElementType::BYTE:
		return GL_BYTE;
	case ElementType::SHORT:
		return GL_SHORT;
	case ElementType::INT:
		return GL_INT;
	case ElementType::FLOAT:
		return GL_FLOAT;
	case ElementType::DOUBLE:
		return GL_DOUBLE;
	case ElementType::UNSIGNED_BYTE:
		return GL_UNSIGNED_BYTE;
	case ElementType::UNSIGNED_SHORT:
		return GL_UNSIGNED_SHORT;
	case ElementType::UNSIGNED_INT:
		return GL_UNSIGNED_INT;
	default:
		return -1;
	}
}

void VertexArray::enableAttribute(unsigned int location)
{
	glEnableVertexAttribArray(location);
}

void VertexArray::disableAttribute(unsigned int location)
{
	glDisableVertexAttribArray(location);
}

}
