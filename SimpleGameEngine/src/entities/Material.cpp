#include "Material.h"


Material::Material(const Material &other)
{
	this->name = other.name;
	this->textureID = other.textureID;
	this->reflectivity = other.reflectivity;
	this->ambient = other.ambient;
	this->emissive = other.emissive;
	this->diffuse = other.diffuse;
	this->specular = other.specular;
	this->specularHighlight = other.specularHighlight;
	this->refractiveIndex = other.refractiveIndex;
	this->opacity = other.opacity;
}

Material& Material::operator=(const Material &other)
{
	this->name = other.name;
	this->textureID = other.textureID;
	this->reflectivity = other.reflectivity;
	this->ambient = other.ambient;
	this->emissive = other.emissive;
	this->diffuse = other.diffuse;
	this->specular = other.specular;
	this->specularHighlight = other.specularHighlight;
	this->refractiveIndex = other.refractiveIndex;
	this->opacity = other.opacity;
	return *this;
}

Material::Material()
{
	this->name = std::string("ERROR: Empty material!");
	this->textureID = -1;
	this->reflectivity = 0;
	this->ambient = 0.2f;
	this->emissive = 0;
	this->diffuse = 0.5f;
	this->specular = 0;
	this->specularHighlight = 0;
	this->refractiveIndex = 0;
	this->opacity = 1;
}


Material::~Material()
{
	glDeleteTextures(1, &textureID);
}

Material::Material(const char* file, const char* n, GLuint texture, float a, float e, float d, float s, float sh, float ri, float r, float o)
{
	this->name = std::string(file);
	name += ":";
	name.append(n);
	this->textureID = texture;
	this->reflectivity = r;
	this->opacity = o;
	this->ambient = a;
	this->emissive = e;
	this->diffuse = d;
	this->specular = s;
	this->specularHighlight = sh;
	this->refractiveIndex = ri;
}

GLuint Material::getTextureID() const
{
	return textureID;
}

float Material::getReflectivity() const
{
	return reflectivity;
}

float Material::getOpacity() const
{
	return opacity;
}

float Material::getAmbient() const
{
	return ambient;
}

float Material::getEmissive() const
{
	return emissive;
}

float Material::getDiffuse() const
{
	return diffuse;
}

float Material::getSpecular() const
{
	return specular;
}

float Material::getSpecularHighlight() const
{
	return specularHighlight;
}

float Material::getRefractiveIndex() const
{
	return refractiveIndex;
}

void Material::setTextureID(GLuint id)
{
	this->textureID = id;
}

void Material::setReflectivity(float r)
{
	this->reflectivity = r;
}

void Material::setOpacity(float o)
{
	this->opacity = o;
}

void Material::setAmbient(float a)
{
	this->ambient = a;
}

void Material::setEmissive(float e)
{
	this->emissive = e;
}

void Material::setDiffuse(float d)
{
	this->diffuse = d;
}

void Material::setSpecular(float s)
{
	this->specular = s;
}

void Material::setSpecularHighlight(float sh)
{
	this->specularHighlight = sh;
}

void Material::setRefractiveIndex(float ri)
{
	this->refractiveIndex = ri;
}

std::string Material::toString() const
{
	return ("--Material--\nName: " + std::string(name) + "\nTextureID: " + std::to_string(textureID) + "\nAmbient: " + std::to_string(ambient) + "\nEmissive: " + std::to_string(emissive) + "\nDiffuse: " + std::to_string(diffuse) + "\nSpecular: " + std::to_string(specular) + "\nSpecularHighlight: " + std::to_string(specularHighlight) + "\nRefractiveIndex: " + std::to_string(refractiveIndex) + "\nReflectivity: " + std::to_string(reflectivity) + "\nOpacity: " + std::to_string(opacity) + "\n--End Material--");
}