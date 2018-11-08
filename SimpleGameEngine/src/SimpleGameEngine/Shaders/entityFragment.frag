#version 400 core

in vec2 textureCoords;
in vec3 nToLight;
in vec3 nToEye;
in vec3 nNormal;
in vec3 nFromLight;
//in vec3 nHalf;

uniform float u_ambient; //ambient
uniform float u_emissive; //emissive
uniform float u_diffuse; //diffuse
uniform float u_specular; //specular
uniform float u_specular_highlight; //specular highlight
uniform float u_reflectivity; //reflectivity
uniform float u_refractive_index; //refractive index
uniform float u_opacity; //opacity

uniform sampler2D textureSampler;
uniform samplerCube cubeMapSampler;

void main()
{
	vec3 normal = normalize(nNormal);

	float diffusePart = dot(nToLight, normal);
	diffusePart = clamp(diffusePart, u_ambient, 1.0);

	vec3 reflected = normalize(reflect(nFromLight, normal));

	float specularPart = dot(nToEye, reflected);
	//float specularPart = dot(normal, nHalf);
	specularPart = clamp(specularPart, 0, 1);

	vec4 finalPhong = vec4(1, 1, 1, u_opacity) * texture(textureSampler, textureCoords) * diffusePart * u_diffuse + u_specular * pow(specularPart, u_specular_highlight);
	vec4 finalReflection = texture(cubeMapSampler, normalize(reflect(-nToEye, normal)));

	//gl_FragColor = finalReflection;
	gl_FragColor = u_reflectivity * finalReflection + (1 - u_reflectivity) * finalPhong;
}