#version 400 core

in vec2 textureCoords;
in vec3 nToLight;
in vec3 nNormal;

uniform float ka; //ambient
uniform float kd; //diffuse
uniform float o; //opacity

uniform float tileFactor;
uniform sampler2D blendSampler;
uniform sampler2D redSampler;
uniform sampler2D greenSampler;
uniform sampler2D blueSampler;
uniform sampler2D backSampler;

//uniform sampler2D textureSampler;

void main()
{
	vec3 normal = normalize(nNormal);

	float diffusePart = dot(nToLight, normal);
	diffusePart = clamp(diffusePart, ka, 1.0);

	vec2 tiledTextureCoords = textureCoords * tileFactor;

	vec3 redTexture = texture(redSampler, tiledTextureCoords).xyz;
	vec3 greenTexture = texture(greenSampler, tiledTextureCoords).xyz;
	vec3 blueTexture = texture(blueSampler, tiledTextureCoords).xyz;
	vec3 backTexture = texture(backSampler, tiledTextureCoords).xyz;
	vec3 blendTexture = texture(blendSampler, textureCoords).xyz;

	float redAmount = blendTexture.r;
	float greenAmount = blendTexture.g;
	float blueAmount = blendTexture.b;
	float backAmount = 1 - (redAmount + greenAmount + blueAmount);

	vec3 finalColor = redTexture * redAmount + greenTexture * greenAmount + blueTexture * blueAmount + backTexture * backAmount;

	gl_FragColor = vec4(1, 1, 1, o) * vec4(finalColor, 1) * diffusePart * kd;
	//gl_FragColor = vec4(1, 1, 1, o) * texture(textureSampler, textureCoords) * diffusePart * kd;
}