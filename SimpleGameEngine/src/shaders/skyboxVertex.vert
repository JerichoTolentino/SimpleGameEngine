#version 400 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 textureUV;

out vec3 textureCoords;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;

void main()
{
	textureCoords = textureUV;

	gl_Position = vec4(position, 1.0) * view_matrix * proj_matrix;
}