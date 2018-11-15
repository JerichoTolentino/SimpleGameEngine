#version 430 core

in vec3 vTextureCoords;

layout(location = 0) out vec4 OutputColor;

uniform samplerCube cubemapSampler;

void main()
{
	OutputColor = texture(cubemapSampler, vTextureCoords);
	//gl_FragColor = texture(cubemapSampler, vTextureCoords);
}