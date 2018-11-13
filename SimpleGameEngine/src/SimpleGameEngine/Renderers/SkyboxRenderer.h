#pragma once
#include <memory>
#include "../Cameras/Camera.h"
#include "../Shaders/Shader.h"
#include "../Math/Mat4.h"
#include "../Models/SkyboxRenderModel.h"

namespace SimpleGameEngine::Renderers
{
	class SkyboxRenderer
	{
	private:
		std::shared_ptr<Shaders::Shader> m_shader;



	public:
		SkyboxRenderer();
		SkyboxRenderer(const std::shared_ptr<Shaders::Shader> shader);
		SkyboxRenderer(const SkyboxRenderer & other);
		~SkyboxRenderer();

		
		void loadSkybox(const Models::SkyboxRenderModel & skybox) const;
		void render(const Models::SkyboxRenderModel & skybox) const;
		void unloadSkybox() const;
		void loadProjectionMatrix(const Math::Mat4 & proj) const;
		void loadCamera(const Cameras::Camera & camera) const;



		SkyboxRenderer & operator=(const SkyboxRenderer & other);
	};
}
