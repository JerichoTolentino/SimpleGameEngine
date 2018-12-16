#version 430 core

layout (location = 0) in vec2 iPosition;

out vec4 vClipSpaceCoordinates;
out vec2 vTextureCoordinates;
out vec3 vToEye;
out vec3 vFromSun;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform vec3 uEyePosition;
uniform vec3 uSunPosition;
uniform float uTileFactor;

void main()
{
	vec4 world_position = vec4(iPosition.x, 0.0, iPosition.y, 1.0) * uModelMatrix;

	vToEye = uEyePosition - world_position.xyz;
	vFromSun = world_position.xyz - uSunPosition;

	vTextureCoordinates = vec2(iPosition.x / 2.0 + 0.5, iPosition.y / 2.0 + 0.5) * uTileFactor;
	vClipSpaceCoordinates = world_position * uViewMatrix * uProjectionMatrix;
	gl_Position = vClipSpaceCoordinates;
}
