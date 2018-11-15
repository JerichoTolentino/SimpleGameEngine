#version 430 core

in vec3 vTextureCoords;

uniform samplerCube cubemapSampler;

void main()
{
	gl_FragColor = texture(cubemapSampler, vTextureCoords);
}