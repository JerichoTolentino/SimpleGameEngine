#pragma once
#include "WaterModel.h"

namespace SimpleGameEngine::Models
{
	class WaterRenderModel
	{
	private:
		std::shared_ptr<WaterModel> m_waterModel;
		unsigned int m_vaoId;



	public:
		WaterRenderModel();
		WaterRenderModel(const WaterRenderModel & other);
		WaterRenderModel(
			std::shared_ptr<WaterModel> waterModel,
			unsigned int vaoId);
		virtual ~WaterRenderModel();



		std::shared_ptr<WaterModel> getWaterModel() const;
		unsigned int getVaoId() const;



		WaterRenderModel & operator=(const WaterRenderModel & other);
	};
}
