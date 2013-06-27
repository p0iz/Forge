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

#include "Texture.hpp"

#include "Graphics/Mesh.h"

#include <GL/glew.h>

namespace Forge {

void Texture::create(Texture::Target type)
{
	mTarget = getGLType(type);
	glGenTextures(1, &mName);
}

void Texture::destroy()
{
	release();
	glDeleteTextures(1, &mName);
}

int Texture::getGLType(Texture::Target target)
{
	switch (target)
	{
	case Target::TEXTURE_1D:
		return GL_TEXTURE_1D;
	case Target::TEXTURE_2D:
		return GL_TEXTURE_2D;
	case Target::TEXTURE_3D:
		return GL_TEXTURE_3D;
	case Target::TEXTURE_CUBE:
		return GL_TEXTURE_CUBE_MAP;
	default:
		return -1;
	}
}

void Texture::release()
{
	glBindTexture(mTarget, 0);
}

void Texture::setActiveUnit(Texture::Unit unit)
{
	glActiveTexture(getGLUnit(unit));
}

int Texture::getGLUnit(Texture::Unit unit)
{
	switch (unit)
	{
	case Unit::TEXTURE0:
		return GL_TEXTURE0;
	case Unit::TEXTURE1:
		return GL_TEXTURE1;
	case Unit::TEXTURE2:
		return GL_TEXTURE2;
	case Unit::TEXTURE3:
		return GL_TEXTURE3;
	case Unit::TEXTURE4:
		return GL_TEXTURE4;
	case Unit::TEXTURE5:
		return GL_TEXTURE5;
	case Unit::TEXTURE6:
		return GL_TEXTURE6;
	case Unit::TEXTURE7:
		return GL_TEXTURE7;
	default:
		return -1;
	}
}

int Texture::getGLWrap(Wrap wrap)
{
	switch (wrap)
	{
	case Wrap::CLAMP_EDGE:
		return GL_CLAMP_TO_EDGE;
	case Wrap::REPEAT:
		return GL_REPEAT;
	case Wrap::REPEAT_MIRROR:
		return GL_MIRRORED_REPEAT;
	default:
		return -1;
	}
}

int Texture::getGLFilter(Filter filter)
{
	switch (filter)
	{
	case Filter::NEAREST:
		return GL_NEAREST;
	case Filter::LINEAR:
		return GL_LINEAR;
	case Filter::NEAREST_MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;
	case Filter::LINEAR_MIPMAP_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;
	case Filter::NEAREST_MIPMAP_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;
	case Filter::LINEAR_MIPMAP_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		return -1;
	}
}

Texture::Texture(int target, unsigned int name) : mTarget(target), mName(name)
{
}

void Texture::setWrapping(Wrap s)
{
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, getGLWrap(s));
}

void Texture::setWrapping(Wrap s, Wrap t)
{
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, getGLWrap(s));
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, getGLWrap(t));
}

void Texture::setWrapping(Wrap s, Wrap t, Wrap r)
{
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, getGLWrap(s));
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, getGLWrap(t));
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, getGLWrap(r));
}

void Texture::setFiltering(Filter min, Filter mag)
{
	glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, getGLFilter(min));
	glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, getGLFilter(mag));
}

}
