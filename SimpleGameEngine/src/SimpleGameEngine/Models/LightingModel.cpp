#include "LightingModel.h"

namespace SimpleGameEngine::Models
{
	LightingModel::LightingModel()
	{
	}

	LightingModel::LightingModel(
		float reflectivity, 
		float opacity, 
		float ambient, 
		float emissive, 
		float diffuse, 
		float specular, 
		float specularHighlight, 
		float refractiveIndex)
	{
		m_reflectivity = reflectivity;
		m_opacity = opacity;
		m_ambient = ambient;
		m_emissive = emissive;
		m_diffuse = diffuse;
		m_specular = specular;
		m_specularHighlight = specularHighlight;
		m_refractiveIndex = refractiveIndex;
	}

	LightingModel::LightingModel(const LightingModel & other)
		: LightingModel(
			other.m_reflectivity,
			other.m_opacity,
			other.m_ambient,
			other.m_emissive,
			other.m_diffuse,
			other.m_specular,
			other.m_specularHighlight,
			other.m_refractiveIndex
		)
	{
	}

	LightingModel::~LightingModel()
	{
	}


	
	float LightingModel::getReflectivity() const
	{
		return m_reflectivity;
	}

	float LightingModel::getOpacity() const
	{
		return m_opacity;
	}

	float LightingModel::getAmbient() const
	{
		return m_ambient;
	}

	float LightingModel::getEmissive() const
	{
		return m_emissive;
	}

	float LightingModel::getDiffuse() const
	{
		return m_diffuse;
	}

	float LightingModel::getSpecular() const
	{
		return m_specular;
	}

	float LightingModel::getSpecularHighlight() const
	{
		return m_specularHighlight;
	}

	float LightingModel::getRefractiveIndex() const
	{
		return m_refractiveIndex;
	}

	void LightingModel::setReflectivity(float r)
	{
		m_reflectivity = r;
	}

	void LightingModel::setOpacity(float o)
	{
		m_opacity = o;
	}

	void LightingModel::setAmbient(float a)
	{
		m_ambient = a;
	}

	void LightingModel::setEmissive(float e)
	{
		m_emissive = e;
	}

	void LightingModel::setDiffuse(float d)
	{
		m_diffuse = d;
	}

	void LightingModel::setSpecular(float s)
	{
		m_specular = s;
	}

	void LightingModel::setSpecularHighlight(float sh)
	{
		m_specularHighlight = sh;
	}

	void LightingModel::setRefractiveIndex(float ri)
	{
		m_refractiveIndex = ri;
	}



	LightingModel & LightingModel::operator=(const LightingModel & other)
	{
		m_ambient = other.m_ambient;
		m_diffuse = other.m_diffuse;
		m_emissive = other.m_emissive;
		m_opacity = other.m_opacity;
		m_reflectivity = other.m_reflectivity;
		m_refractiveIndex = other.m_refractiveIndex;
		m_specular = other.m_specular;
		m_specularHighlight = other.m_specularHighlight;

		return *this;
	}
}
