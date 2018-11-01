#version 400 core

in vec3 textureCoords;

uniform samplerCube cubemapSampler;

void main()
{
	gl_FragColor = texture(cubemapSampler, textureCoords);
}