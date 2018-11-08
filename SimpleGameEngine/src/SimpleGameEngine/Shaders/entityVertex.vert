#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureUV;

out vec2 textureCoords;
out vec3 nToLight;
out vec3 nToEye;
out vec3 nNormal;
out vec3 nFromLight;
//out vec3 nHalf;

uniform mat4 u_model_matrix;
uniform mat4 u_proj_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_normal_matrix;
uniform vec3 u_light_pos;
uniform vec3 u_eye_pos;

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

	vec3 fromLight = worldPos - u_light_pos;
	nFromLight = normalize(fromLight);

	vec3 toEye = u_eye_pos - worldPos;
	nToEye = normalize(toEye);

	//vec3 lv = toLight + toEye;
	//nHalf = normalize(lv / length(lv));

	textureCoords = textureUV;

	gl_Position = vec4(position, 1.0) * u_model_matrix * u_view_matrix * u_proj_matrix;
}