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

// Attributes
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexTexCoord;
layout(location = 2) in vec3 VertexNormal;
layout(location = 3) in vec3 VertexTangent;
layout(location = 4) in vec3 VertexBinormal;

// Uniforms
struct Light
{
	vec4 position;
	vec4 color;

	// Attenuation
	float constant;
	float linear;
	float quadratic;

	// For spot lights
	float spotExponent;
	vec3  spotDirection;
	float spotCutoff;
	float spotFalloff;
};

layout (std140) uniform Lights
{
  Light light;
};

uniform mat3 NormalMatrix;
uniform mat4 WorldViewProjection;
uniform mat4 WorldViewMatrix;

// Outputs
out float attenuation;
out vec3 object_space_halfway;
out vec3 object_space_light; // Vertex-to-light direction in object space
out vec3 object_space_view; // Vertex-to-view in object space
out vec3 view_space_normal;
out vec3 view_space_vertex;
out vec3 view_space_spot_direction;
out vec2 texture_coordinate;

void main(void)
{
	texture_coordinate = VertexTexCoord;

	vec4 pos = vec4(VertexPosition,1);
	
	// Normal, tangent and binormal to eye space
	view_space_vertex = vec3(WorldViewMatrix * pos);
	view_space_normal = normalize(NormalMatrix * VertexNormal);
	vec3 view_space_tangent = normalize(NormalMatrix * VertexTangent);
	vec3 view_space_binormal = normalize(NormalMatrix * VertexBinormal);

	mat3 object_local_matrix = mat3(view_space_tangent.x, view_space_binormal.x, view_space_normal.x,
									view_space_tangent.y, view_space_binormal.y, view_space_normal.y,
									view_space_tangent.z, view_space_binormal.z, view_space_normal.z);

	object_space_light = normalize(object_local_matrix * (light.position.xyz - view_space_vertex));
	object_space_view = object_local_matrix * normalize(-view_space_vertex);
	object_space_halfway = normalize(object_space_light + object_space_view);

  attenuation = 1.0;
	if (light.position.w > 0.0f) {
		float dist = distance(view_space_vertex, vec3(light.position));
		attenuation /= (light.constant + light.linear * dist + light.quadratic * dist * dist);
	}
	
	if (light.spotExponent > 0.0f) {
		view_space_spot_direction = NormalMatrix * light.spotDirection;
	}

	gl_Position = WorldViewProjection * pos;
}
