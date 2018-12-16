#pragma once

namespace SimpleGameEngine::Models
{
	class WaterProperties
	{
	private:
		float m_reflectivity;
		float m_shineDamper;
		float m_fresnelConstant;
		float m_flowSpeed;
		float m_tileFactor;
		float m_waveStrength;



	public:
		WaterProperties();
		WaterProperties(const WaterProperties & other);
		WaterProperties(float reflectivity, float shineDamper, float fresnelConstant, float flowSpeed, float waveStrength, float tileFactor);
		virtual ~WaterProperties();



		float getReflectivity() const;
		float getShineDamper() const;
		float getFresnelConstant() const;
		float getFlowSpeed() const;
		float getTileFactor() const;
		float getWaveStrength() const;

		void setReflectivity(float reflectivity);
		void setShineDamper(float shineDamper);
		void setFresnelConstant(float constant);
		void setFlowSpeed(float speed);
		void setTileFactor(float factor);
		void setWaveStrength(float strength);



		WaterProperties & operator=(const WaterProperties & other);
	};
}
