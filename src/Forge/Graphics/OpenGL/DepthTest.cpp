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

#include "DepthTest.hpp"

#include <GL/glew.h>

namespace Forge {

void DepthTest::enable()
{
	glEnable(GL_DEPTH_TEST);
}

void DepthTest::disable()
{
	glDisable(GL_DEPTH_TEST);
}

int DepthTest::getGLFunc(Function func)
{
	switch(func)
	{
	case Function::NEVER:
		return GL_NEVER;
	case Function::LESS:
		return GL_LESS;
	case Function::LEQUAL:
		return GL_LEQUAL;
	case Function::EQUAL:
		return GL_EQUAL;
	case Function::GEQUAL:
		return GL_GEQUAL;
	case Function::GREATER:
		return GL_GREATER;
	case Function::NOT_EQUAL:
		return GL_NOTEQUAL;
	case Function::ALWAYS:
		return GL_ALWAYS;
	default:
		return -1;
	}
}

}
