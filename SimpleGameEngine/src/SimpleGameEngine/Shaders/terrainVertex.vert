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

void main()
{
	// Calculate world position of vertex
	vec3 world_position = (vec4(iPosition, 1.0) * uModelMatrix).xyz;

	// Pass normalized vectors and texture coordinates
	//vNormal = normalize(transpose(inverse(uModelMatrix)) * vec4(iNormal, 0.0)).xyz;
	vNormal = (uModelMatrix * vec4(iNormal, 0.0)).xyz;
	vTextureCoords = iTextureUv;
	for (int i = 0; i < 5; i++)
	{
		vToLights[i] = normalize(uLightPositions[i] - world_position);
	}

	gl_Position = vec4(iPosition, 1.0) * uModelMatrix * uViewMatrix * uProjectionMatrix;
}