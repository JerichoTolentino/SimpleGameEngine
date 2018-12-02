#version 430 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTextureUv;

out vec2 vTextureCoordinates;
out vec3 vToEye;
out vec3 vNormal;
out vec3 vToLights[5];
out vec3 vLightReflections[5];
out vec3 vEyeReflection;
out vec3 vRefracted;

uniform mat4 uModelMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uNormalMatrix;
uniform vec3 uLightPositions[5];
uniform vec3 uEyePosition;
uniform float uRefractiveIndex;

void main()
{
	// Transform position and normal to world coordinates
	vec4 world_pos = vec4(iPosition, 1.0) * uModelMatrix;
	vec4 world_normal = vec4(iNormal, 0.0) * transpose(inverse(uModelMatrix)); // Transpose inverse of model matrix accounts for scaling

	// Pass swizzled normal vector out
	vNormal = world_normal.xyz;

	// Normalize normal
	vec3 n_normal = normalize(vNormal);

	for (int i = 0; i < 5; i++)
	{
		// Calculate vector from vertex to the light source
		vToLights[i] = uLightPositions[i] - world_pos.xyz;

		// Calculate light reflection vector
		vec3 n_to_light = normalize(vToLights[i]);
		vLightReflections[i] = reflect(-n_to_light, n_normal);
	}

	// Calculate vector from vertex to the camera
	vToEye = uEyePosition - world_pos.xyz;
	vec3 n_to_eye = normalize(vToEye);

	// Calculate eye reflection vector
	vEyeReflection = reflect(-n_to_eye, n_normal);

	// Calculate refraction vector
	vRefracted = refract(-n_to_eye, n_normal, 1.0/uRefractiveIndex);

	// Pass the texture UVs
	vTextureCoordinates = iTextureUv;

	gl_Position = world_pos * uViewMatrix * uProjectionMatrix;
}