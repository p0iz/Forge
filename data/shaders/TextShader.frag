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

#version 330

in vec2 texcoord;

uniform sampler2D glyphTexture;
uniform vec4 textColor;

out vec4 fragColor;

void main(void)
{
	float alpha = texture2D(glyphTexture, texcoord).r;
	fragColor = vec4(1, 1, 1, alpha) * textColor;
//	fragColor = vec4(1,0,0,1);
}
