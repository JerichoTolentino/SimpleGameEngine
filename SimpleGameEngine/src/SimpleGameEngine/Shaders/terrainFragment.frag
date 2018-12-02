#version 430 core

in vec2 vTextureCoords;
in vec3 vToLights[5];
in vec3 vNormal;

layout(location = 0) out vec4 OutputColor;

uniform float uAmbient;
uniform float uDiffuse;
uniform float uOpacity;
uniform float uTileFactor;
uniform vec3 uLightColors[5];
uniform vec3 uLightAttenuations[5];

uniform sampler2D uBlendMapSampler;
uniform sampler2D uRedSampler;
uniform sampler2D uGreenSampler;
uniform sampler2D uBlueSampler;
uniform sampler2D uBackgroundSampler;

void main()
{
	// Initialize running total of shading color
	vec3 total_diffuse = vec3(0.0);	

	// Normalize interpolated normal
	vec3 n_normal = normalize(vNormal);

	// Calculate diffuse shading
	for (int i = 0; i < 5; i++)
	{
		// Calculate light attenuation
		float distance_to_light = length(vToLights[i]);
		float attenuation_factor = uLightAttenuations[i].x + (uLightAttenuations[i].y * distance_to_light) + (uLightAttenuations[i].z * distance_to_light * distance_to_light);
		
		// Normalize light vector
		vec3 n_to_light = normalize(vToLights[i]);

		// Calculate diffuse color
		float diffuse_amount = max(dot(n_to_light, n_normal), 0.0);
		total_diffuse += (diffuse_amount * uLightColors[i]) / attenuation_factor;
	}

	// Clamp total diffuse and apply ambient shading
	total_diffuse = clamp(total_diffuse, uAmbient, 1.0);

	// Get the colors of each texture in a TexturePack
	vec2 tiled_texture_coords = vTextureCoords * uTileFactor;
	vec3 red_texture = texture(uRedSampler, tiled_texture_coords).xyz;
	vec3 green_texture = texture(uGreenSampler, tiled_texture_coords).xyz;
	vec3 blue_texture = texture(uBlueSampler, tiled_texture_coords).xyz;
	vec3 background_texture = texture(uBackgroundSampler, tiled_texture_coords).xyz;
	
	// Get the blend amounts for each texture
	vec3 blendTexture = texture(uBlendMapSampler, vTextureCoords).xyz;

	// Calculate the final texture color of the fragment
	float red_amount = blendTexture.r;
	float green_amount = blendTexture.g;
	float blue_amount = blendTexture.b;
	float background_amount = 1 - (red_amount + green_amount + blue_amount);
	vec3 final_texture_color = 
		red_texture * red_amount + 
		green_texture * green_amount + 
		blue_texture * blue_amount + 
		background_texture * background_amount;

	OutputColor = vec4(total_diffuse, uOpacity) * vec4(final_texture_color, 1) * uDiffuse;
}