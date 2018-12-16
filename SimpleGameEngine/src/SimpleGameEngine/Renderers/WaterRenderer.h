#pragma once
#include "../Shaders/Shader.h"
#include "../Cameras/Camera.h"
#include "../Models/LightSource.h"
#include "../Models/WaterEntity.h"
#include "../OpenGL/WaterReflectionFbo.h"
#include "../OpenGL/WaterRefractionFbo.h"

namespace SimpleGameEngine::Renderers
{
	class WaterRenderer
	{
	private:
		std::shared_ptr<Shaders::Shader> m_shader;
		unsigned int m_reflectionTextureId;
		unsigned int m_refractionTextureId;
		unsigned int m_depthTextureId;



	public:
		WaterRenderer();
		WaterRenderer(
			const std::shared_ptr<Shaders::Shader> shader,
			unsigned int reflectionTextureId,
			unsigned int refractionTextureId,
			unsigned int depthTextureId);
		WaterRenderer(const WaterRenderer & other);
		~WaterRenderer();



		void loadClippingPlanes(float nearPlane, float farPlane) const;
		void loadSun(const Models::LightSource & light) const;
		void loadCamera(const Cameras::Camera & camera) const;
		void loadLights(const std::vector<std::shared_ptr<Models::LightSource>> & lights) const;
		void loadProjectionMatrix(const Math::Mat4 & proj) const;
		void loadWaterRenderModel(const Models::WaterRenderModel & waterRenderModel) const;
		void loadWaterEntity(const Models::WaterEntity & entity) const;
		void render(const Models::WaterEntity & entity) const;
		void unloadWaterRenderModel() const;



		WaterRenderer & operator=(const WaterRenderer & other);
	};
}
