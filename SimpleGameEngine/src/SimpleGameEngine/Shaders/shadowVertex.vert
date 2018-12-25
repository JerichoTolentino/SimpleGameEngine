#version 430 core

layout (location = 0) in vec3 iPosition;

uniform mat4 uModelViewProjectionMatrix;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
	gl_Position = vec4(iPosition, 1) * model_matrix * view_matrix * projection_matrix;
	//gl_Position = vec4(iPosition, 1) * uModelViewProjectionMatrix;
}