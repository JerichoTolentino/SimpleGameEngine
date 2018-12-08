#pragma once
#include "WaterRenderModel.h"
#include "SpaceModel.h"

namespace SimpleGameEngine::Models
{
	class WaterEntity
	{
	private:
		std::shared_ptr<WaterRenderModel> m_waterRenderModel;
		std::shared_ptr<SpaceModel> m_spaceModel;


	public:
		WaterEntity();
		WaterEntity(const WaterEntity & other);
		WaterEntity(
			const std::shared_ptr<WaterRenderModel> waterRenderModel,
			const std::shared_ptr<SpaceModel> spaceModel);
		virtual ~WaterEntity();



		std::shared_ptr<WaterRenderModel> getWaterRenderModel() const;
		std::shared_ptr<SpaceModel> getSpaceModel() const;



		WaterEntity & operator=(const WaterEntity & other);
	};
}
