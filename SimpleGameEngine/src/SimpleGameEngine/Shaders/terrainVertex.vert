#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureUV;

out vec2 textureCoords;
out vec3 nToLight;
out vec3 nNormal;

uniform mat4 u_model_matrix;
uniform mat4 u_proj_matrix;
uniform mat4 u_view_matrix;
uniform vec3 u_light_pos;

void main()
{
	vec3 worldPos = (vec4(position, 1.0) * u_model_matrix).xyz;
	nNormal = normalize(transpose(inverse(u_model_matrix)) * vec4(normal, 0.0)).xyz;

	//---QUARANTINED---//

	//NOTE: Do not need to have glNormalMatrix = model * view
	//		- The above seems to work perfectly fine...

	//nNormal = normalize(transpose(inverse(modelView)) * vec4(normal, 0.0)).xyz;

	//---QUARANTINED---//
	
	vec3 toLight = u_light_pos - worldPos;
	nToLight = normalize(toLight);

	textureCoords = textureUV;

	gl_Position = vec4(position, 1.0) * u_model_matrix * u_view_matrix * u_proj_matrix;
}