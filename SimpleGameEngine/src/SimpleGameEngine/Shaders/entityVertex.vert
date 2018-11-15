#version 430 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTextureUv;

out vec2 vTextureCoordinates;
out vec3 vToLight;
out vec3 vToEye;
out vec3 vNormal;
out vec3 vFromLight;
out vec3 vLightReflection;
out vec3 vEyeReflection;
out vec3 vRefracted;

uniform mat4 uModelMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uNormalMatrix;
uniform vec3 uLightPosition;
uniform vec3 uEyePosition;
uniform float uRefractiveIndex;

void main()
{
	// Normalize normal vector
	vNormal = normalize(transpose(inverse(uModelMatrix)) * vec4(iNormal, 0.0)).xyz;

	// Transform vertex to world coordinates
	vec3 world_pos = (vec4(iPosition, 1.0) * uModelMatrix).xyz;
	
	// Calculate vector from vertex to the light source
	vToLight = normalize(uLightPosition - world_pos);

	// Calculate vector from the light source to the vertex
	vFromLight = normalize(world_pos - uLightPosition);

	// Calculate vector from vertex to the camera
	vToEye = normalize(uEyePosition - world_pos);

	// Calculate reflection vectors
	vLightReflection = reflect(vFromLight, vNormal);
	vEyeReflection = reflect(-vToEye, vNormal);

	// Calculate refraction vector
	vRefracted = refract(-vToEye, vNormal, 1.0/uRefractiveIndex);

	// Pass the texture UVs
	vTextureCoordinates = iTextureUv;

	gl_Position = vec4(iPosition, 1.0) * uModelMatrix * uViewMatrix * uProjectionMatrix;
}