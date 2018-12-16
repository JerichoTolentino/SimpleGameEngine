#include "sgepch.h"
#include "WaterProperties.h"

namespace SimpleGameEngine::Models
{
	WaterProperties::WaterProperties()
	{
	}

	WaterProperties::WaterProperties(const WaterProperties & other)
		: WaterProperties(
			other.m_reflectivity,
			other.m_shineDamper,
			other.m_fresnelConstant,
			other.m_flowSpeed,
			other.m_waveStrength,
			other.m_tileFactor)
	{
	}

	WaterProperties::WaterProperties(float reflectivity, float shineDamper, float fresnelConstant, float flowSpeed, float waveStrength, float tileFactor)
		: 
		m_reflectivity(reflectivity),
		m_shineDamper(shineDamper), 
		m_fresnelConstant(fresnelConstant), 
		m_flowSpeed(flowSpeed), 
		m_waveStrength(waveStrength), 
		m_tileFactor(tileFactor)
	{
	}

	WaterProperties::~WaterProperties()
	{
	}



	float WaterProperties::getReflectivity() const
	{
		return m_reflectivity;
	}

	float WaterProperties::getShineDamper() const
	{
		return m_shineDamper;
	}

	float WaterProperties::getFresnelConstant() const
	{
		return m_fresnelConstant;
	}

	float WaterProperties::getFlowSpeed() const
	{
		return m_flowSpeed;
	}

	float WaterProperties::getTileFactor() const
	{
		return m_tileFactor;
	}

	float WaterProperties::getWaveStrength() const
	{
		return m_waveStrength;
	}

	void WaterProperties::setReflectivity(float reflectivity)
	{
		m_reflectivity = reflectivity;
	}

	void WaterProperties::setShineDamper(float shineDamper)
	{
		m_shineDamper = shineDamper;
	}

	void WaterProperties::setFresnelConstant(float constant)
	{
		m_fresnelConstant = constant;
	}

	void WaterProperties::setFlowSpeed(float speed)
	{
		m_flowSpeed = speed;
	}

	void WaterProperties::setTileFactor(float factor)
	{
		m_tileFactor = factor;
	}

	void WaterProperties::setWaveStrength(float strength)
	{
		m_waveStrength = strength;
	}



	WaterProperties & WaterProperties::operator=(const WaterProperties & other)
	{
		m_reflectivity = other.m_reflectivity;
		m_flowSpeed = other.m_flowSpeed;
		m_fresnelConstant = other.m_fresnelConstant;
		m_shineDamper = other.m_shineDamper;
		m_tileFactor = other.m_tileFactor;
		m_waveStrength = other.m_waveStrength;

		return *this;
	}
}
