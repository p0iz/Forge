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

#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

out vec2 texture_coordinate;
out vec3 eye_space_normal;
out vec3 eye_space_vertex;

struct Light
{
	vec4 position;
	vec4 color;
	float constant;
	float linear;
	float quadratic;
};

layout (std140) uniform Lights
{
  Light lights[8]; // max 8 lights per mesh
};
out float attenuation[8];

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;

void main(void)
{
	vec4 pos = vec4(position, 1);
    gl_Position = WorldViewProjectionMatrix * pos;
    eye_space_normal = normalize(NormalMatrix * normal);
    eye_space_vertex = vec3(WorldViewMatrix * pos);
    texture_coordinate = texcoord;
	// calculate attenuation per light
	for (int i = 0; i < 8; ++i) {
		if (lights[i].position.w > 0.001f) {
			float dist = distance(eye_space_vertex, vec3(lights[i].position));
			attenuation[i] =
				1.0 / (lights[i].constant + lights[i].linear * dist + lights[i].quadratic * dist * dist);
		}
	}
}
