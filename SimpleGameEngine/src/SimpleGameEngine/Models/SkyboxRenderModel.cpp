#include "SkyboxRenderModel.h"

namespace SimpleGameEngine::Models
{
	SkyboxRenderModel::SkyboxRenderModel()
	{
	}

	SkyboxRenderModel::SkyboxRenderModel(const SkyboxRenderModel & other)
		: SkyboxRenderModel(other.m_skyboxModel, other.m_skyboxVaoId, other.m_textureId)
	{
	}

	SkyboxRenderModel::SkyboxRenderModel(SkyboxModel skyboxModel, unsigned int skyboxVaoId, unsigned int textureId)
	{
		m_skyboxModel = skyboxModel;
		m_skyboxVaoId = skyboxVaoId;
		m_textureId = textureId;
	}


	SkyboxRenderModel::~SkyboxRenderModel()
	{
	}



	SkyboxModel SkyboxRenderModel::getSkyboxModel() const
	{
		return m_skyboxModel;
	}

	unsigned int SkyboxRenderModel::getSkyboxVaoId() const
	{
		return m_skyboxVaoId;
	}

	unsigned int SkyboxRenderModel::getTextureId() const
	{
		return m_textureId;
	}



	SkyboxRenderModel & SkyboxRenderModel::operator=(const SkyboxRenderModel & other)
	{
		m_skyboxModel = other.m_skyboxModel;
		m_skyboxVaoId = other.m_skyboxVaoId;
		m_textureId = other.m_textureId;

		return *this;
	}


}
