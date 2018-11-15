#version 430 core

layout (location = 0) in vec3 iPosition;
layout (location = 2) in vec3 iTextureUv;

out vec3 vTextureCoords;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

void main()
{
	vTextureCoords = iTextureUv;

	gl_Position = vec4(iPosition, 1.0) * uViewMatrix * uProjectionMatrix;
}