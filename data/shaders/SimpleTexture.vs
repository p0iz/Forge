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
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

out vec2 UV;
out vec3 view_space_normal;
out vec3 view_space_vertex;

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

void main(void)
{
    gl_Position = WorldViewProjectionMatrix * vec4(position,1);
	view_space_normal = normalize(mat3(WorldViewMatrix) * normal);
	view_space_vertex = mat3(WorldViewMatrix) * position;
    UV = vertexUV;
	
	for (int i = 0; i < lights.length(); ++i) {
		if (lights[i].position.w > 0.0f) {
			// Calculate attenuation
			float d = distance(lights[i].position.xyz, view_space_vertex);
			attenuation[i] = 1.0f / (lights[i].constant + lights[i].linear * d + lights[i].quadratic * d * d);
		}
	}
	
}
