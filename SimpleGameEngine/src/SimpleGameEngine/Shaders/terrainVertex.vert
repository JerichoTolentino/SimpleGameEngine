#version 430 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTextureUv;

out vec2 vTextureCoords;
out vec3 vToLight;
out vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform vec3 uLightPosition;

void main()
{
	vec3 worldPos = (vec4(iPosition, 1.0) * uModelMatrix).xyz;
	vNormal = normalize(transpose(inverse(uModelMatrix)) * vec4(iNormal, 0.0)).xyz;
	
	vec3 toLight = uLightPosition - worldPos;
	vToLight = normalize(toLight);

	vTextureCoords = iTextureUv;

	gl_Position = vec4(iPosition, 1.0) * uModelMatrix * uViewMatrix * uProjectionMatrix;
}