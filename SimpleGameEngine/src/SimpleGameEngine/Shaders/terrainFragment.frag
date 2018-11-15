#version 430 core

in vec2 vTextureCoords;
in vec3 vToLight;
in vec3 vNormal;

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
	vec3 normal = normalize(vNormal);

	float diffusePart = dot(vToLight, normal);
	diffusePart = clamp(diffusePart, uAmbient, 1.0);

	vec2 tiledTextureCoords = vTextureCoords * uTileFactor;

	vec3 redTexture = texture(uRedSampler, tiledTextureCoords).xyz;
	vec3 greenTexture = texture(uGreenSampler, tiledTextureCoords).xyz;
	vec3 blueTexture = texture(uBlueSampler, tiledTextureCoords).xyz;
	vec3 backTexture = texture(uBackgroundSampler, tiledTextureCoords).xyz;
	vec3 blendTexture = texture(uBlendMapSampler, vTextureCoords).xyz;

	float redAmount = blendTexture.r;
	float greenAmount = blendTexture.g;
	float blueAmount = blendTexture.b;
	float backAmount = 1 - (redAmount + greenAmount + blueAmount);

	vec3 finalColor = redTexture * redAmount + greenTexture * greenAmount + blueTexture * blueAmount + backTexture * backAmount;

	gl_FragColor = vec4(1, 1, 1, uOpacity) * vec4(finalColor, 1) * diffusePart * uDiffuse;
	//gl_FragColor = vec4(1, 1, 1, uOpacity) * texture(textureSampler, vTextureCoords) * diffusePart * uDiffuse;
}