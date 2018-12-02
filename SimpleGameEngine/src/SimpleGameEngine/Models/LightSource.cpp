#include "sgepch.h"
#include "LightSource.h"

namespace SimpleGameEngine::Models
{
	LightSource::LightSource()
		: LightSource(Math::Vec3(0, 0, 0), Math::Vec3(0, 0, 0), Math::Vec3(0, 0, 0))
	{
	}

	LightSource::LightSource(const LightSource & other)
		: LightSource(other.m_position, other.m_color, other.m_attenuation)
	{
	}

	LightSource::LightSource(const Math::Vec3 & position, const Math::Vec3 & color)
		: LightSource(position, color, Math::Vec3(1, 0, 0))
	{
	}

	LightSource::LightSource(const Math::Vec3 & position, const Math::Vec3 & color, const Math::Vec3 & attenuation)
	{
		m_position = position;
		m_color = color;
		m_attenuation = attenuation;
	}


	LightSource::~LightSource()
	{
	}



	Math::Vec3 LightSource::getPosition() const
	{
		return m_position;
	}
	Math::Vec3 LightSource::getColor() const
	{
		return m_color;
	}

	Math::Vec3 LightSource::getAttenuation() const
	{
		return m_attenuation;
	}

	void LightSource::translate(const Math::Vec3 & translation)
	{
		m_position += translation;
	}



	LightSource & LightSource::operator=(const LightSource & other)
	{
		m_position = other.m_position;
		m_color = other.m_color;

		return *this;
	}
}
