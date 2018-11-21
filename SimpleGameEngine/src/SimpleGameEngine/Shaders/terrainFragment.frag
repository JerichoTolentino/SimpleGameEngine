#version 430 core

in vec2 vTextureCoords;
in vec3 vToLight;
in vec3 vNormal;

layout(location = 0) out vec4 OutputColor;

uniform float uAmbient;
uniform float uDiffuse;
uniform float uOpacity;
uniform float uTileFactor;

uniform sampler2D uBlendMapSampler;
uniform sampler2D uRedSampler;
uniform sampler2D uGreenSampler;
uniform sampler2D uBlueSampler;
uniform sampler2D uBackgroundSampler;

void main()
{
	// Calculate diffuse shading
	float diffusePart = dot(vToLight, vNormal);
	diffusePart = clamp(diffusePart, uAmbient, 1.0);

	// Get the colors of each texture in a TexturePack
	vec2 tiledTextureCoords = vTextureCoords * uTileFactor;
	vec3 redTexture = texture(uRedSampler, tiledTextureCoords).xyz;
	vec3 greenTexture = texture(uGreenSampler, tiledTextureCoords).xyz;
	vec3 blueTexture = texture(uBlueSampler, tiledTextureCoords).xyz;
	vec3 backTexture = texture(uBackgroundSampler, tiledTextureCoords).xyz;
	
	// Get the blend amounts for each texture
	vec3 blendTexture = texture(uBlendMapSampler, vTextureCoords).xyz;

	// Calculate the final color of the fragment
	float redAmount = blendTexture.r;
	float greenAmount = blendTexture.g;
	float blueAmount = blendTexture.b;
	float backAmount = 1 - (redAmount + greenAmount + blueAmount);
	vec3 finalColor = redTexture * redAmount + greenTexture * greenAmount + blueTexture * blueAmount + backTexture * backAmount;

	OutputColor = vec4(1, 1, 1, uOpacity) * vec4(finalColor, 1) * diffusePart * uDiffuse;
}