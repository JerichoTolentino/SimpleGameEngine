#pragma once
#include "../Cameras/Camera.h"
#include "../Shaders/Shader.h"
#include "../Math/Mat4.h"
#include "../Models/SkyboxRenderModel.h"

namespace SimpleGameEngine::Renderers
{
	class SkyboxRenderer
	{
	private:
		Shaders::Shader m_shader;

	public:
		SkyboxRenderer();
		SkyboxRenderer(Shaders::Shader shader);
		~SkyboxRenderer();

		
		void loadSkybox(Models::SkyboxRenderModel skybox) const;
		void render(Models::SkyboxRenderModel skybox) const;
		void unloadSkybox() const;
		void loadProjectionMatrix(Math::Mat4 proj) const;
		void loadCamera(Cameras::Camera camera) const;
	};
}
