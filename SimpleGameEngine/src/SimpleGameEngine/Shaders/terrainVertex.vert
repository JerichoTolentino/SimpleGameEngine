#version 430 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTextureUv;

out vec2 vTextureCoords;
out vec3 vToLights[5];
out vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform vec3 uLightPositions[5];

uniform vec4 uClippingPlane;

void main()
{
	// Calculate position and normal in world space
	vec4 world_position = vec4(iPosition, 1.0) * uModelMatrix;
	vec4 world_normal = vec4(iNormal, 0.0) * transpose(inverse(uModelMatrix));

	// Pass normal and texture coordinates
	vNormal = world_normal.xyz;
	vTextureCoords = iTextureUv;

	for (int i = 0; i < 5; i++)
	{
		vToLights[i] = normalize(uLightPositions[i] - world_position.xyz);
	}

	gl_Position = world_position * uViewMatrix * uProjectionMatrix;
	gl_ClipDistance[0] = dot(world_position, uClippingPlane);
}