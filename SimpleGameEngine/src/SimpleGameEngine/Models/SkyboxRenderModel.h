#pragma once
#include "SkyboxModel.h"

namespace SimpleGameEngine::Models
{
	class SkyboxRenderModel
	{
	private:
		SkyboxModel m_skyboxModel;
		unsigned int m_skyboxVaoId;
		unsigned int m_textureId;



	public:
		SkyboxRenderModel();
		SkyboxRenderModel(const SkyboxRenderModel & other);
		SkyboxRenderModel(SkyboxModel skyboxModel, unsigned int skyboxVaoId, unsigned int textureId);
		virtual ~SkyboxRenderModel();



		SkyboxModel getSkyboxModel() const;
		unsigned int getSkyboxVaoId() const;
		unsigned int getTextureId() const;



		SkyboxRenderModel & operator=(const SkyboxRenderModel & other);
	};
}
