#include "Material.h"

namespace SimpleGameEngine::Models
{

	Material::Material()
	{
	}

	Material::Material(GLuint textureId, LightingModel lightingModel)
	{
		m_textureId = textureId;
		m_lightingModel = lightingModel;
	}

	Material::Material(const Material &other)
		: Material(other.m_textureId, other.m_lightingModel)
	{
	}

	Material::~Material()
	{
		//glDeleteTextures(1, &m_textureId); //TODO: Move this to loader when unloading textures
	}


	GLuint Material::getTextureID() const
	{
		return m_textureId;
	}

	LightingModel Material::getLightingModel() const
	{
		return m_lightingModel;
	}

	void Material::setTextureID(GLuint id)
	{
		this->m_textureId = id;
	}

	void Material::setLightingModel(LightingModel lightingModel)
	{
		m_lightingModel = lightingModel;
	}



	Material& Material::operator=(const Material &other)
	{
		m_textureId = other.m_textureId;
		m_lightingModel = other.m_lightingModel;
		return *this;
	}
}
