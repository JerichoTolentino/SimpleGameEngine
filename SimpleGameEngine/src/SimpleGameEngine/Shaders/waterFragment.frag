#version 430 core

layout (location = 0) out vec4 OutputColor;

in vec2 vTextureCoordinates;

void main()
{
	OutputColor = vec4(0, 0, 1, 1);
}
