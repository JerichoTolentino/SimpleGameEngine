#version 430 core

layout (location = 0) in vec2 iPosition;

out vec2 vTextureCoordinates;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
	vTextureCoordinates = vec2(iPosition.x / 2.0 + 0.5, iPosition.y / 2.0 + 0.5);

	gl_Position = vec4(iPosition.x, 0.0, iPosition.y, 1.0) * uModelMatrix * uViewMatrix * uProjectionMatrix;
}
