#pragma once

namespace SimpleGameEngine::Models
{
	class LightingModel
	{
	private:
		float m_reflectivity;
		float m_opacity;
		float m_ambient;
		float m_emissive;
		float m_diffuse;
		float m_specular;
		float m_specularHighlight;
		float m_refractiveIndex;



	public:
		LightingModel();
		LightingModel(
			float reflectivity,
			float opacity,
			float ambient,
			float emissive,
			float diffuse,
			float specular,
			float specularHighlight,
			float refractiveIndex);
		LightingModel(const LightingModel & other);
		virtual ~LightingModel();



		float getReflectivity() const;
		float getOpacity() const;
		float getAmbient() const;
		float getEmissive() const;
		float getDiffuse() const;
		float getSpecular() const;
		float getSpecularHighlight() const;
		float getRefractiveIndex() const;
		void setReflectivity(float r);
		void setOpacity(float o);
		void setAmbient(float a);
		void setEmissive(float e);
		void setDiffuse(float d);
		void setSpecular(float s);
		void setSpecularHighlight(float sh);
		void setRefractiveIndex(float ri);



		LightingModel & operator=(const LightingModel & other);
	};
}
