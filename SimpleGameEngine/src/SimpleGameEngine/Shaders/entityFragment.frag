#version 430 core

in vec2 vTextureCoordinates;
in vec3 vToLight;
in vec3 vToEye;
in vec3 vNormal;
in vec3 vFromLight;
out vec3 vLightReflection;
out vec3 vEyeReflection;
in vec3 vRefracted;

uniform float u_ambient;
uniform float u_emissive;
uniform float u_diffuse;
uniform float u_specular;
uniform float u_specular_highlight;
uniform float u_reflectivity;
uniform float u_opacity;

uniform sampler2D u_texture_sampler;
uniform samplerCube u_cubemap_sampler;

void main()
{
	// Calculate diffuse portion of color
	float diffuse_part = dot(vToLight, vNormal);
	diffuse_part = clamp(diffuse_part, u_ambient, 1.0);

	// Calculate specular portion of color
	float specular_part = dot(vToEye, vLightReflection);
	specular_part = clamp(specular_part, 0, 1);

	// Calculate phong shading color of fragment
	vec4 texture_color = texture(u_texture_sampler, vTextureCoordinates);
	vec4 final_phong = vec4(1, 1, 1, u_opacity) * texture_color * diffuse_part * u_diffuse + u_specular * pow(specular_part, u_specular_highlight);

	// Calculate color from environment map reflections/refractions
	vec4 finalReflection = texture(u_cubemap_sampler, reflect(-vToEye, vNormal));
	vec4 finalRefracted = texture(u_cubemap_sampler, vRefracted);
	vec4 environmentColor = mix(finalReflection, finalRefracted, 0.5);

	gl_FragColor = mix(environmentColor, final_phong, 0.5);
	//gl_FragColor = u_reflectivity * finalReflection + (1 - u_reflectivity) * final_phong;
}