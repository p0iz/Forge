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

uniform sampler2D fbo_texture;
uniform float time;

in vec2 f_texcoord;

out vec4 fragColor;

void main(void)
{
	if (int(f_texcoord.y * 2000) % 2 == 0)
		discard;
	vec2 texcoord = f_texcoord;
	texcoord.x += sin(texcoord.y * 4*2*3.14159 + time) / 100;
	fragColor = texture2D(fbo_texture, texcoord);
}
