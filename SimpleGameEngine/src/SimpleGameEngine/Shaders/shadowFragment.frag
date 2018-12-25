#version 430 core

layout(location = 0) out vec4 OutputColor;

uniform sampler2D uTextureSampler;

const float NEAR_PLANE = 1.0;
const float FAR_PLANE = 1000;

// from: https://stackoverflow.com/questions/6652253/getting-the-true-z-value-from-the-depth-buffer
// doesn't seem to work
float linearDepth(float depthSample)
{
    depthSample = 2.0 * depthSample - 1.0;
    float zLinear = 2.0 * NEAR_PLANE * FAR_PLANE / (FAR_PLANE + NEAR_PLANE - depthSample * (FAR_PLANE - NEAR_PLANE));
    return zLinear;
}

void main()
{
	float result = linearDepth(gl_FragCoord.z);
	//OutputDepth = gl_FragCoord.z;
	OutputColor = vec4(result, result, result, 1);
}