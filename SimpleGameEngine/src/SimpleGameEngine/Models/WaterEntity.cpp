#include "sgepch.h"
#include "WaterEntity.h"

namespace SimpleGameEngine::Models
{
	WaterEntity::WaterEntity()
	{
	}

	WaterEntity::WaterEntity(const WaterEntity & other)
		: WaterEntity(other.m_waterRenderModel, other.m_spaceModel)
	{
	}

	WaterEntity::WaterEntity(const std::shared_ptr<WaterRenderModel> waterRenderModel, const std::shared_ptr<SpaceModel> spaceModel)
		: m_waterRenderModel(waterRenderModel), m_spaceModel(spaceModel)
	{
	}

	WaterEntity::~WaterEntity()
	{
	}



	std::shared_ptr<WaterRenderModel> WaterEntity::getWaterRenderModel() const
	{
		return m_waterRenderModel;
	}
	
	std::shared_ptr<SpaceModel> WaterEntity::getSpaceModel() const
	{
		return m_spaceModel;
	}
	
	
	
	WaterEntity & WaterEntity::operator=(const WaterEntity & other)
	{
		m_waterRenderModel = other.m_waterRenderModel;
		m_spaceModel = other.m_spaceModel;

		return *this;
	}
}
