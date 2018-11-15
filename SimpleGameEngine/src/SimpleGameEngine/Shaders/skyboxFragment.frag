#version 430 core

in vec3 vTextureCoords;

layout(location = 0) out vec4 OutputColor;

uniform samplerCube uCubemapSampler;

void main()
{
	OutputColor = texture(uCubemapSampler, vTextureCoords);
}