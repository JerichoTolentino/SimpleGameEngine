#pragma once
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class LightSource
	{
	private:
		Math::Vec3 m_position;
		Math::Vec3 m_color;
		Math::Vec3 m_attenuation;



	public:
		LightSource();
		LightSource(const LightSource & other);
		LightSource(const Math::Vec3 & position, const Math::Vec3 & color);
		LightSource(const Math::Vec3 & position, const Math::Vec3 & color, const Math::Vec3 & attenuation);
		virtual ~LightSource();

		Math::Vec3 getPosition() const;
		Math::Vec3 getColor() const;
		Math::Vec3 getAttenuation() const;

		void translate(const Math::Vec3 & translation);



		LightSource & operator=(const LightSource & other);
	};
}
