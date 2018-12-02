#include "sgepch.h"
#include "Material.h"

namespace SimpleGameEngine::Models
{

	Material::Material()
	{
	}

	Material::Material(const std::shared_ptr<LightingModel> lightingModel)
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



	std::shared_ptr<LightingModel> Material::getLightingModel() const
	{
		return m_lightingModel;
	}

	void Material::setLightingModel(const std::shared_ptr<LightingModel> lightingModel)
	{
		m_lightingModel = lightingModel;
	}



	Material & Material::operator=(const Material &other)
	{
		m_lightingModel = other.m_lightingModel;
		return *this;
	}
}
