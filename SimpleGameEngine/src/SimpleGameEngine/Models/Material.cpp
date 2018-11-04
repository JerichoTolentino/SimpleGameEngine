#include "Material.h"

namespace SimpleGameEngine::Models
{

	Material::Material()
	{
	}

	Material::Material(LightingModel lightingModel)
	{
		m_lightingModel = lightingModel;
	}

	Material::Material(const Material &other)
		: Material(other.m_lightingModel)
	{
	}

	Material::~Material()
	{
	}



	LightingModel Material::getLightingModel() const
	{
		return m_lightingModel;
	}

	void Material::setLightingModel(LightingModel lightingModel)
	{
		m_lightingModel = lightingModel;
	}



	Material& Material::operator=(const Material &other)
	{
		m_lightingModel = other.m_lightingModel;
		return *this;
	}
}
