#version 430 core

layout(location = 0) out vec4 OutputColor;

in vec2 vTextureCoordinates;

uniform sampler2D uTextureSampler;

void main()
{
	OutputColor = texture(uTextureSampler, vTextureCoordinates);
}