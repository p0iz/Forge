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

#include "Material.h"

#include <cassert>
#include <GL/glew.h>

namespace Forge {

void Material::reloadMaterial()
{
	mVertexShader.loadCode(mVertexShaderFile);
	mFragmentShader.loadCode(mFragmentShaderFile);
	buildShaderProgram();
}

void Material::buildShaderProgram()
{
	compileShaders();
	linkShaderProgram();
}

void Material::compileShaders()
{
	mVertexShader.compile();
	mFragmentShader.compile();
}

void Material::linkShaderProgram()
{
	assert(mShaderProgram.link() == GL_TRUE);
}

void Material::apply()
{
	mShaderProgram.use();
}

void Material::setVertexShader(const char* file)
{
	mVertexShaderFile = file;
	mVertexShader.loadCode(file);
}

void Material::setFragmentShader(const char* file)
{
	mFragmentShaderFile = file;
	mFragmentShader.loadCode(file);
}

} // namespace Forge
