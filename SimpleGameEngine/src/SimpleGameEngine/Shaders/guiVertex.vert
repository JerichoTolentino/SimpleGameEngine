#version 430 core

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec2 iTextureUv;

out vec2 vTextureCoordinates;

uniform mat4 uModelMatrix;

void main()
{
	// Pass the texture UVs
	vTextureCoordinates = iTextureUv;

	gl_Position = vec4(iPosition, 0.0, 1.0) * uModelMatrix;
}