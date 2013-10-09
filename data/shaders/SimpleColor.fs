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
	float spotExponent;
	vec3  spotDirection;
	float spotCutoff;
	float spotFalloff;
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
	vec3 lightVec = normalize(vec3(light.position) - view_space_vertex);

	// Calculate ADS lighting per light
	vec3 halfway = normalize(lightVec + eye);
	float diffuse = max(dot(lightVec, normal), 0.0f);
	vec3 lighting = vec3(0.0f);
	float specular = pow(max(dot(halfway, normal), 0.0f), MaterialShininess);
	float spotlight = 1.0f;
	// Spotlight
	if (light.spotExponent > 0.0f) 
  {
		// Calculate fragment illumination
		spotlight = max(-dot(lightVec, normalize(light.spotDirection)), 0.0f);
		// Fade
		float fade =
			clamp(
        (light.spotCutoff - spotlight) / light.spotCutoff - light.spotFalloff,
        0.0f,
        1.0f
      );
		spotlight = pow(spotlight * fade, light.spotExponent);
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
