#version 430 core

layout (location = 0) in vec2 iPosition;

out vec4 vClipSpaceCoordinates;
out vec2 vTextureCoordinates;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

const float TILE_FACTOR = 4.0;

void main()
{
	vTextureCoordinates = vec2(iPosition.x / 2.0 + 0.5, iPosition.y / 2.0 + 0.5) * TILE_FACTOR;
	vClipSpaceCoordinates = vec4(iPosition.x, 0.0, iPosition.y, 1.0) * uModelMatrix * uViewMatrix * uProjectionMatrix;
	gl_Position = vClipSpaceCoordinates;
}
