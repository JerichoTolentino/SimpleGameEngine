#version 430 core

layout(location = 0) out vec4 OutputColor;

in vec2 vTextureCoordinates;
in vec3 vToEye;
in vec3 vNormal;
in vec3 vToLights[5];
in vec3 vLightReflections[5];
in vec3 vRefracted;
in vec3 vEyeReflection;

uniform float uAmbient;
uniform float uEmissive;
uniform float uDiffuse;
uniform float uSpecular;
uniform float uSpecularHighlight;
uniform float uReflectivity;
uniform float uOpacity;
uniform vec3 uLightColors[5];
uniform vec3 uLightAttenuations[5];

uniform sampler2D uTextureSampler;
uniform samplerCube uCubemapSampler;

void main()
{
	// Initialize running totals of shading colors
	vec3 total_emissive = vec3(0.0);
	vec3 total_diffuse = vec3(0.0);
	vec3 total_specular = vec3(0.0);

	// Normalize vectors
	vec3 n_to_eye = normalize(vToEye);
	vec3 n_normal = normalize(vNormal);
	vec3 n_refracted = normalize(vRefracted);
	vec3 n_eye_reflection = normalize(vEyeReflection);

	for (int i = 0; i < 5; i++)
	{
		// Calculate light attenuation factor
		float distance_to_light = length(vToLights[i]);
		float attenuation_factor = uLightAttenuations[i].x + (uLightAttenuations[i].y * distance_to_light) + (uLightAttenuations[i].z * distance_to_light * distance_to_light);

		// Normalize light vector
		vec3 n_to_light = normalize(vToLights[i]);

		// Calculate emissive portion of color
		total_emissive +=  uLightColors[i];

		// Calculate diffuse portion of color
		float diffuse_amount = max(dot(n_to_light, n_normal), 0.0);
		total_diffuse += (diffuse_amount * uLightColors[i]) / attenuation_factor;

		// Calculate specular portion of color
		vec3 n_light_reflection = normalize(vLightReflections[i]);
		float specular_amount = pow(max(dot(n_to_eye, n_light_reflection), 0.0), uSpecularHighlight);
		total_specular += (specular_amount * uLightColors[i]) / attenuation_factor;
	}

	// Clamp total values (and apply ambient shading)
	total_emissive = clamp(total_emissive, 0.0, 1.0);
	total_diffuse = clamp(total_diffuse, uAmbient, 1.0);
	total_specular = clamp(total_specular, 0.0, 1.0);
	
	// Calculate phong shading color of fragment
	vec4 texture_color = texture(uTextureSampler, vTextureCoordinates);
	vec4 final_phong = 
		(vec4(total_emissive, 1.0) * uEmissive) +
		(vec4(total_diffuse, 1.0) * uDiffuse) * texture_color + 
		(vec4(total_specular, 1.0) * uSpecular);

	// Get color from environment map reflections/refractions
	vec4 final_reflection = texture(uCubemapSampler, n_eye_reflection);
	vec4 final_refracted = texture(uCubemapSampler, n_refracted);

	// Mix colors
	vec4 surface_color = mix(final_phong, final_reflection, uReflectivity);
	OutputColor = mix(final_refracted, surface_color, uOpacity);
}