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

#include "Graphics/Mesh.h"

#include <GL/glew.h>

namespace Forge {

Buffer::Buffer() : mName(0), mTarget(-1)
{
}

void Buffer::create(Target target)
{
	if (mName != 0)
		return;

	mTarget = getGLTarget(target);

	if (mTarget != -1)
		glGenBuffers(1, &mName);
}

void Buffer::destroy()
{
	if (mName != 0)
	{
		release();
		glDeleteBuffers(1, &mName);
	}
	mName = 0;
	mTarget = -1;
}

void Buffer::bind()
{
	if (mTarget != -1)
		glBindBuffer(mTarget, mName);
}

void Buffer::setData(size_t size, const void* data, Usage usage)
{
	bind();
	glBufferData(mTarget, size, data, getGLUsage(usage));
}

void Buffer::setSubData(unsigned int begin, unsigned int size, void *data)
{
	bind();
	glBufferSubData(mTarget, begin, size, data);
}

void Buffer::setBindingPoint(unsigned int point)
{
	if (mTarget == GL_UNIFORM_BUFFER)
		glBindBufferBase(mTarget, point, mName);
}

void Buffer::release()
{
	if (mTarget != -1)
		glBindBuffer(mTarget, 0);
}

int Buffer::getGLTarget(Buffer::Target target)
{
	switch (target)
	{
	case Target::VERTEX_BUFFER:
		return GL_ARRAY_BUFFER;
	case Target::ELEMENT_BUFFER:
		return GL_ELEMENT_ARRAY_BUFFER;
	case Target::UNIFORM_BUFFER:
		return GL_UNIFORM_BUFFER;
	default:
		return -1;
	}
}

int Buffer::getGLUsage(Buffer::Usage usage)
{
	switch (usage)
	{
	case Usage::DYNAMIC_COPY:
		return GL_DYNAMIC_COPY;
	case Usage::DYNAMIC_DRAW:
		return GL_DYNAMIC_DRAW;
	case Usage::DYNAMIC_READ:
		return GL_DYNAMIC_READ;
	case Usage::STATIC_COPY:
		return GL_STATIC_COPY;
	case Usage::STATIC_DRAW:
		return GL_STATIC_DRAW;
	case Usage::STATIC_READ:
		return GL_STATIC_READ;
	case Usage::STREAM_COPY:
		return GL_STREAM_COPY;
	case Usage::STREAM_DRAW:
		return GL_STREAM_DRAW;
	case Usage::STREAM_READ:
		return GL_STREAM_READ;
	default:
		return -1;
	}
}

}
