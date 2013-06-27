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

#include "Blending.hpp"

#include <GL/glew.h>

namespace Forge {

void Blending::enable()
{
	glEnable(GL_BLEND);
}

void Blending::disable()
{
	glDisable(GL_BLEND);
}

void Blending::setEquation(Equation equation)
{
	glBlendEquation(getGLEquation(equation));
}

void Blending::setFunction(Factor source, Factor destination)
{
	glBlendFunc(getGLFactor(source), getGLFactor(destination));
}

void Blending::setColor(float r, float g, float b, float a)
{
	glBlendColor(r, g, b, a);
}

int Blending::getGLFactor(Factor factor)
{
	switch (factor)
	{
	case Factor::ZERO:
		return GL_ZERO;
	case Factor::ONE:
		return GL_ONE;
	case Factor::SRC_COLOR:
		return GL_SRC_COLOR;
	case Factor::ONE_MINUS_SRC_COLOR:
		return GL_ONE_MINUS_SRC_COLOR;
	case Factor::DST_COLOR:
		return GL_DST_COLOR;
	case Factor::ONE_MINUS_DST_COLOR:
		return GL_ONE_MINUS_DST_COLOR;
	case Factor::SRC_ALPHA:
		return GL_SRC_ALPHA;
	case Factor::ONE_MINUS_SRC_ALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
	case Factor::DST_ALPHA:
		return GL_DST_ALPHA;
	case Factor::ONE_MINUS_DST_ALPHA:
		return GL_ONE_MINUS_DST_ALPHA;
	case Factor::CONSTANT_COLOR:
		return GL_CONSTANT_COLOR;
	case Factor::ONE_MINUS_CONSTANT_COLOR:
		return GL_ONE_MINUS_CONSTANT_COLOR;
	case Factor::CONSTANT_ALPHA:
		return GL_CONSTANT_ALPHA;
	case Factor::ONE_MINUS_CONSTANT_ALPHA:
		return GL_ONE_MINUS_CONSTANT_ALPHA;
	default:
		return -1;
	}
}

int Blending::getGLEquation(Blending::Equation equation)
{
	switch (equation)
	{
	case Equation::ADD:
		return GL_FUNC_ADD;
	case Equation::SUBTRACT:
		return GL_FUNC_SUBTRACT;
	case Equation::REVERSE_SUBTRACT:
		return GL_FUNC_REVERSE_SUBTRACT;
	case Equation::MIN:
		return GL_MIN;
	case Equation::MAX:
		return GL_MAX;
	default:
		return -1;
	}
}

}
