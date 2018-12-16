#pragma once
#include "WaterRenderModel.h"
#include "SpaceModel.h"
#include "WaterProperties.h"

namespace SimpleGameEngine::Models
{
	class WaterEntity
	{
	private:
		std::shared_ptr<WaterRenderModel> m_waterRenderModel;
		std::shared_ptr<SpaceModel> m_spaceModel;
		std::shared_ptr<WaterProperties> m_waterProperties;
		float m_flowFactor;


	public:
		WaterEntity();
		WaterEntity(const WaterEntity & other);
		WaterEntity(
			const std::shared_ptr<WaterRenderModel> waterRenderModel,
			const std::shared_ptr<SpaceModel> spaceModel,
			const std::shared_ptr<WaterProperties> waterProperties);
		virtual ~WaterEntity();


		/// <summary>
		/// Updates the flow factor of this <see cref="WaterEntity"/>
		/// and returns the updated value.
		/// </summary>
		float updateFlowFactor(float timeDelta);

		std::shared_ptr<WaterRenderModel> getWaterRenderModel() const;
		std::shared_ptr<SpaceModel> getSpaceModel() const;
		std::shared_ptr<WaterProperties> getWaterProperties() const;
		float getFlowFactor() const;



		WaterEntity & operator=(const WaterEntity & other);
	};
}
