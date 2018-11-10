#version 400 core

in vec2 textureCoords;
in vec3 nToLight;
in vec3 nNormal;

uniform float u_ambient;
uniform float u_diffuse;
uniform float u_opacity;
uniform float u_tile_factor;

uniform sampler2D u_blend_sampler;
uniform sampler2D u_red_sampler;
uniform sampler2D u_green_sampler;
uniform sampler2D u_blue_sampler;
uniform sampler2D u_back_sampler;

//uniform sampler2D textureSampler;

void main()
{
	vec3 normal = normalize(nNormal);

	float diffusePart = dot(nToLight, normal);
	diffusePart = clamp(diffusePart, u_ambient, 1.0);

	vec2 tiledTextureCoords = textureCoords * u_tile_factor;

	vec3 redTexture = texture(u_red_sampler, tiledTextureCoords).xyz;
	vec3 greenTexture = texture(u_green_sampler, tiledTextureCoords).xyz;
	vec3 blueTexture = texture(u_blue_sampler, tiledTextureCoords).xyz;
	vec3 backTexture = texture(u_back_sampler, tiledTextureCoords).xyz;
	vec3 blendTexture = texture(u_blend_sampler, textureCoords).xyz;

	float redAmount = blendTexture.r;
	float greenAmount = blendTexture.g;
	float blueAmount = blendTexture.b;
	float backAmount = 1 - (redAmount + greenAmount + blueAmount);

	vec3 finalColor = redTexture * redAmount + greenTexture * greenAmount + blueTexture * blueAmount + backTexture * backAmount;

	gl_FragColor = vec4(1, 1, 1, u_opacity) * vec4(finalColor, 1) * diffusePart * u_diffuse;
	//gl_FragColor = vec4(1, 1, 1, u_opacity) * texture(textureSampler, textureCoords) * diffusePart * u_diffuse;
}