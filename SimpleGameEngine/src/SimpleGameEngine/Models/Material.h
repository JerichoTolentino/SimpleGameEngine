#pragma once
#include <memory>
#include "LightingModel.h"

namespace SimpleGameEngine::Models
{
	class Material
	{
	private:
		std::shared_ptr<LightingModel> m_lightingModel;



	public:
		Material();
		Material(const std::shared_ptr<LightingModel> lightingModel);
		Material(const Material &other);
		virtual ~Material();



		std::shared_ptr<LightingModel> getLightingModel() const;
		void setLightingModel(const std::shared_ptr<LightingModel> lightingModel);



		Material & operator=(const Material &other);
	};
}
