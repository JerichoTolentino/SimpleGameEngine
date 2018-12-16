#include "sgepch.h"
#include "WaterRenderModel.h"

namespace SimpleGameEngine::Models
{
	WaterRenderModel::WaterRenderModel()
	{
	}

	WaterRenderModel::WaterRenderModel(const WaterRenderModel & other)
		: WaterRenderModel(other.m_waterModel, other.m_vaoId, other.m_dudvMapTextureId, other.m_normalMapTextureId)
	{
	}

	WaterRenderModel::WaterRenderModel(std::shared_ptr<WaterModel> waterModel, unsigned int vaoId, unsigned int dudvMapTextureId, unsigned int normalMapTextureId)
		: m_waterModel(waterModel), m_vaoId(vaoId), m_dudvMapTextureId(dudvMapTextureId), m_normalMapTextureId(normalMapTextureId)
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

	unsigned int WaterRenderModel::getDuDvMapTextureId() const
	{
		return m_dudvMapTextureId;
	}

	unsigned int WaterRenderModel::getNormalMapTextureId() const
	{
		return m_normalMapTextureId;
	}



	WaterRenderModel & WaterRenderModel::operator=(const WaterRenderModel & other)
	{
		m_waterModel = other.m_waterModel;
		m_vaoId = other.m_vaoId;
		m_dudvMapTextureId = other.m_dudvMapTextureId;
		m_normalMapTextureId = other.m_normalMapTextureId;

		return *this;
	}
}
