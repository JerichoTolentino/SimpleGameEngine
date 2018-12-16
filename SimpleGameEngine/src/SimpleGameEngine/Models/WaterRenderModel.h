#pragma once
#include "WaterModel.h"

namespace SimpleGameEngine::Models
{
	class WaterRenderModel
	{
	private:
		std::shared_ptr<WaterModel> m_waterModel;
		unsigned int m_vaoId;
		unsigned int m_dudvMapTextureId;
		unsigned int m_normalMapTextureId;



	public:
		WaterRenderModel();
		WaterRenderModel(const WaterRenderModel & other);
		WaterRenderModel(
			std::shared_ptr<WaterModel> waterModel,
			unsigned int vaoId,
			unsigned int dudvMapTextureId,
			unsigned int normalMapTextureId);
		virtual ~WaterRenderModel();



		std::shared_ptr<WaterModel> getWaterModel() const;
		unsigned int getVaoId() const;
		unsigned int getDuDvMapTextureId() const;
		unsigned int getNormalMapTextureId() const;



		WaterRenderModel & operator=(const WaterRenderModel & other);
	};
}
