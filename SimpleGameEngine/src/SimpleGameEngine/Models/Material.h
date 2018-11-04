#pragma once
#include "LightingModel.h"

namespace SimpleGameEngine::Models
{
	class Material
	{
	private:
		LightingModel m_lightingModel;



	public:
		Material();
		Material(LightingModel lightingModel);
		Material(const Material &other);
		virtual ~Material();



		LightingModel getLightingModel() const;
		void setLightingModel(LightingModel lightingModel);



		Material& operator=(const Material &other);
	};
}
