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

// Inputs
in float attenuation;
in vec3 object_space_halfway;
in vec3 object_space_light;
in vec3 object_space_view;
in vec3 view_space_spot_direction;
in vec2 texture_coordinate;

// Uniforms
uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;
uniform vec3 MaterialSpecular;
uniform float MaterialShininess;

uniform sampler2D DiffuseMap;
uniform sampler2D SpecularMap;
uniform sampler2D NormalMap;

struct Light
{
	vec4 position;
	vec4 color;

	// Attenuation
	float constant;
	float linear;
	float quadratic;

	// For spot lights
	float exponent;
	vec3 direction;
	float cutoff;
	float falloff;
};

layout (std140) uniform Lights
{
  Light light;
};

// Outputs
out vec4 color;

vec3 ads_lighting() {
	// Get normal from normal map
	vec3 normal = texture(NormalMap, texture_coordinate).xyz;

	vec3 lightDir = normalize(object_space_light);
	vec3 viewDir = normalize(object_space_view);
	vec3 halfwayDir = normalize(object_space_light + object_space_view);
	
	float lightProjection = dot(lightDir, normal);
	float diffuse = 0.0f;
	float specular = 0.0f;
	if (lightProjection > 0.0f)
	{
		diffuse = lightProjection;
		specular = pow(max(dot(halfwayDir, normal), 0.0f), MaterialShininess);
	}
	
	vec3 lightContribution = light.color.rgb * light.color.a *
		(MaterialAmbient +
		MaterialDiffuse * diffuse +
		MaterialSpecular * specular);
		
	// Spotlight
	if (light.exponent > 0.0f) {
		// Calculate fragment illumination
		float spotlight = max(dot(light.position.xyz, normalize(view_space_spot_direction)), 0.0f);
		// Fade
		float fade =
			clamp((light.cutoff - spotlight) / light.cutoff - light.falloff, 0.0f, 1.0f);
		spotlight = pow(spotlight * fade, light.exponent);
		lightContribution *= spotlight;
	}

	return lightContribution * attenuation;
}

void main(void)
{
	color = texture2D(DiffuseMap, texture_coordinate) * vec4(ads_lighting(), 1);
}
