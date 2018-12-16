#version 430 core

layout (location = 0) out vec4 OutputColor;

in vec4 vClipSpaceCoordinates;
in vec2 vTextureCoordinates;
in vec3 vToEye;
in vec3 vFromSun;

uniform float uNearClippingPlane;
uniform float uFarClippingPlane;
uniform float uWaterFlowFactor;
uniform float uFresnelConstant;
uniform float uWaveStrength;
uniform float uShineDamper;
uniform float uReflectivity;
uniform vec3 uSunColor;

uniform sampler2D uWaterReflectionSampler;
uniform sampler2D uWaterRefractionSampler;
uniform sampler2D uWaterDuDvMapSampler;
uniform sampler2D uWaterNormalMapSampler;
uniform sampler2D uWaterDepthMapSampler;

float calculateDistance(float depth)
{
	return 2.0 * uNearClippingPlane* uFarClippingPlane / (uFarClippingPlane + uNearClippingPlane - (2.0 * depth - 1.0) * (uFarClippingPlane - uNearClippingPlane));
}

void main()
{
	// Calculate normalize device coordinates by perspective division
	// and converting from (-1, 1) to (0, 1)
	vec2 norm_device_coords = (vClipSpaceCoordinates.xy / vClipSpaceCoordinates.w) / 2.0 + 0.5;

	// Sample depth map
	float depth = texture(uWaterDepthMapSampler, norm_device_coords).x;
	float eye_to_terrain_distance = calculateDistance(depth);
	
	depth = gl_FragCoord.z;
	float eye_to_water_distance = calculateDistance(depth);
	float water_depth = eye_to_terrain_distance - eye_to_water_distance;

	// Calculate coordinates to sample water textures
	vec2 water_refl_coords = vec2(norm_device_coords.x, -norm_device_coords.y);
	vec2 water_refr_coords = norm_device_coords;

	// Calculate distortion of water by sampling the dudv map
	vec2 water_distortion = texture(uWaterDuDvMapSampler, vec2(vTextureCoordinates.x + uWaterFlowFactor, vTextureCoordinates.y)).xy * 0.1;
	water_distortion = vTextureCoordinates + vec2(water_distortion.x, water_distortion.y + uWaterFlowFactor);
	vec2 total_water_distortion = (texture(uWaterDuDvMapSampler, water_distortion).xy * 2.0 - 1.0) * uWaveStrength * clamp(water_depth / 20.0, 0.0, 1.0);

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

	// Sample normal map and calculate surface normal
	vec4 normal_map_color = texture(uWaterNormalMapSampler, water_distortion);
	vec3 normal = vec3(normal_map_color.r * 2.0 - 1.0, normal_map_color.b * 3, normal_map_color.g * 2.0 - 1.0);
	vec3 n_normal = normalize(normal);

	// Calculation for fresnel effect
	vec3 n_to_eye = normalize(vToEye);
	float refr_factor = dot(n_to_eye, n_normal);
	refr_factor = pow(refr_factor, uFresnelConstant);
	refr_factor = clamp(refr_factor, 0.0, 1.0);

	// Calculate specular highlight
	vec3 n_reflect_sun = reflect(normalize(vFromSun), n_normal);
	float specular = max(dot(n_reflect_sun, n_to_eye), 0.0);
	specular = pow(specular, uShineDamper);
	vec3 specular_highlight = uSunColor * specular * uReflectivity * clamp(water_depth / 5.0, 0.0, 1.0);

	OutputColor = mix(water_refl_color, water_refr_color, refr_factor) + vec4(specular_highlight, 0.0);
	OutputColor.w = clamp(water_depth / 5.0, 0.0, 1.0);
}
