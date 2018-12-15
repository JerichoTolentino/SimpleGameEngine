#version 430 core

layout (location = 0) out vec4 OutputColor;

in vec4 vClipSpaceCoordinates;

uniform sampler2D uWaterReflectionSampler;
uniform sampler2D uWaterRefractionSampler;

void main()
{
	vec2 norm_device_coords = (vClipSpaceCoordinates.xy / vClipSpaceCoordinates.w) / 2.0 + 0.5;

	vec4 water_refl_color = texture(uWaterReflectionSampler, vec2(norm_device_coords.x, -norm_device_coords.y));
	vec4 water_refr_color = texture(uWaterRefractionSampler, norm_device_coords);

	OutputColor = mix(water_refl_color, water_refr_color, 0.5);
}
