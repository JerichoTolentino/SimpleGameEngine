#version 430 core

in vec2 vTextureCoordinates;
in vec3 vToLight;
in vec3 vToEye;
in vec3 vNormal;
in vec3 vFromLight;
out vec3 vLightReflection;
out vec3 vEyeReflection;
in vec3 vRefracted;

uniform float uAmbient;
uniform float uEmissive;
uniform float uDiffuse;
uniform float uSpecular;
uniform float uSpecularHighlight;
uniform float uReflectivity;
uniform float uOpacity;

uniform sampler2D uTextureSampler;
uniform samplerCube uCubemapSampler;

void main()
{
	// Calculate diffuse portion of color
	float diffuse_part = dot(vToLight, vNormal);
	diffuse_part = clamp(diffuse_part, uAmbient, 1.0);

	// Calculate specular portion of color
	float specular_part = dot(vToEye, vLightReflection);
	specular_part = clamp(specular_part, 0, 1);

	// Calculate phong shading color of fragment
	vec4 texture_color = texture(uTextureSampler, vTextureCoordinates);
	vec4 final_phong = vec4(1, 1, 1, uOpacity) * texture_color * diffuse_part * uDiffuse + uSpecular * pow(specular_part, uSpecularHighlight);

	// Calculate color from environment map reflections/refractions
	vec4 finalReflection = texture(uCubemapSampler, reflect(-vToEye, vNormal));
	vec4 finalRefracted = texture(uCubemapSampler, vRefracted);
	vec4 environmentColor = mix(finalReflection, finalRefracted, 0.5);

	gl_FragColor = mix(environmentColor, final_phong, 0.5);
	//gl_FragColor = uReflectivity * finalReflection + (1 - uReflectivity) * final_phong;
}