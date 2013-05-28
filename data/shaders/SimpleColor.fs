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
 * Copyright 2013 Tommi Martela
 *
 */

#version 330

 // Inputs
in vec2 texture_coordinate;
in vec3 view_space_normal;
in vec3 view_space_vertex;
in float attenuation;

// Uniforms
uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;
uniform vec3 MaterialSpecular;
uniform float MaterialShininess;

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
out vec3 color;

vec3 ads_lighting() {
	// Need to re-normalize interpolated values
	vec3 normal = normalize(view_space_normal);
	vec3 eye = normalize(-view_space_vertex);

	// Calculate ADS lighting per light
	vec3 lighting = vec3(0.0f);
	vec3 view_space_light = normalize(vec3(light.position) - view_space_vertex);
	vec3 halfway = normalize(view_space_light + eye);
	float diffuse = max(dot(view_space_light, normal), 0.0f);
	float specular = 0.0f;
	float spotlight = 1.0f;
	if (diffuse > 0.0f) {
		// Spotlight
		if (light.exponent > 0.0f) {
			// Calculate fragment illumination
			spotlight = max(-dot(view_space_light, normalize(light.direction)), 0.0f);
			// Fade
			float fade =
				clamp((light.cutoff - spotlight) / light.cutoff - light.falloff, 0.0f, 1.0f);
			spotlight = pow(spotlight * fade, light.exponent);
		}
		// Specular
		specular = pow(max(dot(halfway, normal), 0.0f), MaterialShininess);
	}
	vec3 lightContribution = light.color.rgb * light.color.a * spotlight *
		(MaterialAmbient +
		MaterialDiffuse * diffuse +
		MaterialSpecular * specular);
	lighting += lightContribution * attenuation;

	return lighting;
}

void main(void)
{
	color = ads_lighting();
}
