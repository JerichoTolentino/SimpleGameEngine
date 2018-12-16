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
		std::shared_ptr<OpenGL::WaterReflectionFbo> m_waterReflectionFbo;
		std::shared_ptr<OpenGL::WaterRefractionFbo> m_waterRefractionFbo;
		unsigned int m_depthMapTextureId;
		unsigned int m_normalMapTextureId;
		unsigned int m_dudvMapTextureId;
		float m_waterFlowFactor;
		float m_waterFlowSpeed;



	public:
		WaterRenderer();
		WaterRenderer(const std::shared_ptr<Shaders::Shader> shader);
		WaterRenderer(const WaterRenderer & other);
		~WaterRenderer();



		void loadClippingPlanes(float nearPlane, float farPlane) const;
		void loadWaterDepthMap(unsigned int depthMapTextureId);
		void loadSun(const Models::LightSource & light) const;
		void loadFresnelHighlight(float highlight) const;
		void loadWaterFlowSpeed(float speed);
		void loadWaterFlowFactor(float factor);
		void loadWaterDuDvMap(unsigned int dudvMapTextureId);
		void loadWaterNormalMap(unsigned int normalMapTextureId);
		void loadWaterReflectionFbo(const std::shared_ptr<OpenGL::WaterReflectionFbo> waterReflectionFbo);
		void loadWaterRefractionFbo(const std::shared_ptr<OpenGL::WaterRefractionFbo> waterRefractionFbo);
		void loadCamera(const Cameras::Camera & camera) const;
		void loadLights(const std::vector<std::shared_ptr<Models::LightSource>> & lights) const;
		void loadProjectionMatrix(const Math::Mat4 & proj) const;
		void loadWaterRenderModel(const Models::WaterRenderModel & waterRenderModel) const;
		void loadWaterEntity(const Models::WaterEntity & entity) const;
		void render(const Models::WaterEntity & entity) const;
		void unloadWaterRenderModel() const;

		// TODO: REFACTOR THIS
		void updateWaterFlow();



		WaterRenderer & operator=(const WaterRenderer & other);
	};
}
