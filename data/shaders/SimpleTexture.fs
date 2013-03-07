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

in vec2 texture_coordinate;
in vec3 eye_space_normal;
in vec3 eye_space_vertex;

out vec3 color;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

uniform sampler2D albedo;

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
  Light lights[8]; // max 8 lights per mesh
};
in float attenuation[8];

vec3 ads_lighting() {
	// Need to re-normalize interpolated values
	vec3 normal = normalize(eye_space_normal);
	vec3 eye = normalize(-eye_space_vertex);
	
	// Calculate ADS lighting per light
	vec3 lighting = vec3(0.0f);
	for (int i = 0; i < lights.length(); ++i) {
		vec3 eye_space_light = normalize(vec3(lights[i].position) - eye_space_vertex);
		vec3 halfway = normalize(eye_space_light + eye);
		float diffuse = max(dot(eye_space_light, normal), 0.0f);
		float specular = pow(max(dot(halfway, normal), 0.0f), materialShininess);
		vec3 lightContribution = lights[i].color.rgb * lights[i].color.a *
			(materialAmbient + 
			materialDiffuse * diffuse + 
			materialSpecular * specular);
		// Spotlight
		if (lights[i].exponent > 0.0f) {
			// Calculate fragment illumination
			float spotlight = max(-dot(eye_space_light, normalize(lights[i].direction)), 0.0f);
			// Fade 
			float fade = 
				clamp((lights[i].cutoff - spotlight) / lights[i].cutoff - lights[i].falloff, 0.0f, 1.0f); 
			spotlight = pow(spotlight * fade, lights[i].exponent);
			lightContribution *= spotlight;
		}
		
		lighting += lightContribution * attenuation[i];
	}
	return lighting;
}

void main(void)
{
	color = texture2D(albedo, texture_coordinate).rgb * ads_lighting();
}
