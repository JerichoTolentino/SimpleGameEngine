#include "sgepch.h"
#include "WaterEntity.h"

namespace SimpleGameEngine::Models
{
	WaterEntity::WaterEntity()
	{
	}

	WaterEntity::WaterEntity(const WaterEntity & other)
		: WaterEntity(other.m_waterRenderModel, other.m_spaceModel, other.m_waterProperties)
	{
		m_flowFactor = other.m_flowFactor;
	}

	WaterEntity::WaterEntity(const std::shared_ptr<WaterRenderModel> waterRenderModel, const std::shared_ptr<SpaceModel> spaceModel, const std::shared_ptr<WaterProperties> waterProperties)
		: m_waterRenderModel(waterRenderModel), m_spaceModel(spaceModel), m_waterProperties(waterProperties)
	{
		m_flowFactor = 0;
	}

	WaterEntity::~WaterEntity()
	{
	}



	float WaterEntity::updateFlowFactor(float timeDelta)
	{
		m_flowFactor += m_waterProperties->getFlowSpeed();
		m_flowFactor = std::fmodf(m_flowFactor, 1);

		return m_flowFactor;
	}

	std::shared_ptr<WaterRenderModel> WaterEntity::getWaterRenderModel() const
	{
		return m_waterRenderModel;
	}
	
	std::shared_ptr<SpaceModel> WaterEntity::getSpaceModel() const
	{
		return m_spaceModel;
	}

	std::shared_ptr<WaterProperties> WaterEntity::getWaterProperties() const
	{
		return m_waterProperties;
	}

	float WaterEntity::getFlowFactor() const
	{
		return m_flowFactor;
	}
	
	
	
	WaterEntity & WaterEntity::operator=(const WaterEntity & other)
	{
		m_waterRenderModel = other.m_waterRenderModel;
		m_spaceModel = other.m_spaceModel;
		m_waterProperties = other.m_waterProperties;
		m_flowFactor = other.m_flowFactor;

		return *this;
	}
}
