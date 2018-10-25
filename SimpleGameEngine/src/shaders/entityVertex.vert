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

uniform float value;
uniform mat4 model_matrix;
uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 normal_matrix;
uniform vec3 lightPos;
uniform vec3 eyePos;

void main()
{
	vec3 worldPos = (vec4(position, 1.0) * model_matrix).xyz;
	nNormal = normalize(transpose(inverse(model_matrix)) * vec4(normal, 0.0)).xyz;

	//---QUARANTINED---//

	//NOTE: Do not need to have glNormalMatrix = model * view
	//		- The above seems to work perfectly fine...

	//nNormal = normalize(transpose(inverse(modelView)) * vec4(normal, 0.0)).xyz;

	//---QUARANTINED---//
	
	vec3 toLight = lightPos - worldPos;
	nToLight = normalize(toLight);

	vec3 fromLight = worldPos - lightPos;
	nFromLight = normalize(fromLight);

	vec3 toEye = eyePos - worldPos;
	nToEye = normalize(toEye);

	//vec3 lv = toLight + toEye;
	//nHalf = normalize(lv / length(lv));

	textureCoords = textureUV;

	gl_Position = vec4(position, 1.0) * model_matrix * view_matrix * proj_matrix;
}