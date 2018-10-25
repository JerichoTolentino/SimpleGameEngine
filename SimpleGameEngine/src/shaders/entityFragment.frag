#version 400 core

in vec2 textureCoords;
in vec3 nToLight;
in vec3 nToEye;
in vec3 nNormal;
in vec3 nFromLight;
//in vec3 nHalf;

uniform float ka; //ambient
uniform float ke; //emissive
uniform float kd; //diffuse
uniform float ks; //specular
uniform float sh; //specular highlight
uniform float r; //reflectivity
uniform float n; //refractive index
uniform float o; //opacity

uniform sampler2D textureSampler;
uniform samplerCube cubeMapSampler;

void main()
{
	vec3 normal = normalize(nNormal);

	float diffusePart = dot(nToLight, normal);
	diffusePart = clamp(diffusePart, ka, 1.0);

	vec3 reflected = normalize(reflect(nFromLight, normal));

	float specularPart = dot(nToEye, reflected);
	//float specularPart = dot(normal, nHalf);
	specularPart = clamp(specularPart, 0, 1);

	vec4 finalPhong = vec4(1, 1, 1, o) * texture(textureSampler, textureCoords) * diffusePart * kd + ks * pow(specularPart, sh);
	vec4 finalReflection = texture(cubeMapSampler, normalize(reflect(-nToEye, normal)));

	//gl_FragColor = finalReflection;
	gl_FragColor = r * finalReflection + (1 - r) * finalPhong;
}