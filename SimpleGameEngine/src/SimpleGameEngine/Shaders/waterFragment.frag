#version 430 core

layout (location = 0) out vec4 OutputColor;

in vec4 vClipSpaceCoordinates;
in vec2 vTextureCoordinates;
in vec3 vToEye;

uniform float uWaterFlowFactor;
uniform float uFresnelHighlight;

uniform sampler2D uWaterReflectionSampler;
uniform sampler2D uWaterRefractionSampler;
uniform sampler2D uWaterDuDvMapSampler;

const float WAVE_STRENGTH = 0.2;

void main()
{
	// Calculate normalize device coordinates by perspective division
	// and converting from (-1, 1) to (0, 1)
	vec2 norm_device_coords = (vClipSpaceCoordinates.xy / vClipSpaceCoordinates.w) / 2.0 + 0.5;

	// Calculate coordinates to sample water textures
	vec2 water_refl_coords = vec2(norm_device_coords.x, -norm_device_coords.y);
	vec2 water_refr_coords = norm_device_coords;

	// Calculate distortion of water by sampling the dudv map
	vec2 water_distortion = (texture(uWaterDuDvMapSampler, vec2(vTextureCoordinates.x + uWaterFlowFactor, vTextureCoordinates.y)).xy * 2.0 - 1.0) * WAVE_STRENGTH;
	vec2 water_distortion2 = (texture(uWaterDuDvMapSampler, vec2(-vTextureCoordinates.x + uWaterFlowFactor, vTextureCoordinates.y + uWaterFlowFactor)).xy * 2.0 - 1.0) * WAVE_STRENGTH;
	vec2 total_water_distortion = water_distortion + water_distortion2;

	// Apply distortion by offsetting texture coordinates
	water_refl_coords += total_water_distortion;
	water_refr_coords += total_water_distortion;

	// Clamp texture coordinates to ensure they don't wrap around the texture
	water_refl_coords.x = clamp(water_refl_coords.x, 0.001, 0.999);
	water_refl_coords.y = clamp(water_refl_coords.y, -0.999, -0.001);
	water_refr_coords = clamp(water_refr_coords, 0.001, 0.999);

	// Sample water textures
	vec4 water_refl_color = texture(uWaterReflectionSampler, water_refl_coords);
	vec4 water_refr_color = texture(uWaterRefractionSampler, norm_device_coords);

	// Calculation for fresnel effect
	vec3 n_to_eye = normalize(vToEye);
	float refr_factor = dot(n_to_eye, vec3(0, 1, 0));
	refr_factor = pow(refr_factor, uFresnelHighlight);
	
	OutputColor = mix(water_refl_color, water_refr_color, refr_factor);
}
