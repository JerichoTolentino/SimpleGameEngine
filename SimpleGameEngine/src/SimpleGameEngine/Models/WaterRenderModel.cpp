#include "sgepch.h"
#include "WaterRenderModel.h"

namespace SimpleGameEngine::Models
{
	WaterRenderModel::WaterRenderModel()
	{
	}

	WaterRenderModel::WaterRenderModel(const WaterRenderModel & other)
		: WaterRenderModel(other.m_waterModel, other.m_vaoId)
	{
	}

	WaterRenderModel::WaterRenderModel(std::shared_ptr<WaterModel> waterModel, unsigned int vaoId)
		: m_waterModel(waterModel), m_vaoId(vaoId)
	{
	}

	WaterRenderModel::~WaterRenderModel()
	{
	}



	std::shared_ptr<WaterModel> WaterRenderModel::getWaterModel() const
	{
		return m_waterModel;
	}

	unsigned int WaterRenderModel::getVaoId() const
	{
		return m_vaoId;
	}



	WaterRenderModel & WaterRenderModel::operator=(const WaterRenderModel & other)
	{
		m_waterModel = other.m_waterModel;
		m_vaoId = other.m_vaoId;

		return *this;
	}
}
