#pragma once
#include <memory>
#include "SkyboxModel.h"

namespace SimpleGameEngine::Models
{
	class SkyboxRenderModel
	{
	private:
		std::shared_ptr<SkyboxModel> m_skyboxModel;
		unsigned int m_skyboxVaoId;
		unsigned int m_textureId;



	public:
		SkyboxRenderModel();
		SkyboxRenderModel(const SkyboxRenderModel & other);
		SkyboxRenderModel(const std::shared_ptr<SkyboxModel> skyboxModel, unsigned int skyboxVaoId, unsigned int textureId);
		virtual ~SkyboxRenderModel();



		std::shared_ptr<SkyboxModel> getSkyboxModel() const;
		unsigned int getSkyboxVaoId() const;
		unsigned int getTextureId() const;



		SkyboxRenderModel & operator=(const SkyboxRenderModel & other);
	};
}
