#version 430 core

layout (location = 0) in vec2 iPosition;

out vec4 vClipSpaceCoordinates;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
	vClipSpaceCoordinates = vec4(iPosition.x, 0.0, iPosition.y, 1.0) * uModelMatrix * uViewMatrix * uProjectionMatrix;
	gl_Position = vClipSpaceCoordinates;
}
