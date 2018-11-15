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

uniform mat4 u_model_matrix;
uniform mat4 u_proj_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_normal_matrix;
uniform vec3 u_light_pos;
uniform vec3 u_eye_pos;
uniform float u_refractive_index;

void main()
{
	// Normalize normal vector
	vNormal = normalize(transpose(inverse(u_model_matrix)) * vec4(iNormal, 0.0)).xyz;

	// Transform vertex to world coordinates
	vec3 world_pos = (vec4(iPosition, 1.0) * u_model_matrix).xyz;
	
	// Calculate vector from vertex to the light source
	vToLight = normalize(u_light_pos - world_pos);

	// Calculate vector from the light source to the vertex
	vFromLight = normalize(world_pos - u_light_pos);

	// Calculate vector from vertex to the camera
	vToEye = normalize(u_eye_pos - world_pos);

	// Calculate reflection vectors
	vLightReflection = reflect(vFromLight, vNormal);
	vEyeReflection = reflect(-vToEye, vNormal);

	// Calculate refraction vector
	vRefracted = refract(-vToEye, vNormal, 1.0/u_refractive_index);

	// Pass the texture UVs
	vTextureCoordinates = iTextureUv;

	gl_Position = vec4(iPosition, 1.0) * u_model_matrix * u_view_matrix * u_proj_matrix;
}