#pragma once
#include <memory>
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "GuiRenderer.h"
#include "EntityShadowRenderer.h"
#include "RenderScene.h"
#include "../OpenGL/WaterReflectionFbo.h"
#include "../OpenGL/WaterRefractionFbo.h"
#include "../Events/WindowEvent.h"
#include "../Display/Window.h"
#include "../Projection/OrthoProjectionBox.h"
#include "../OpenGL/ShadowMapFbo.h"

namespace SimpleGameEngine::Renderers
{
	class RenderEngine : public Display::IWindowEventListener
	{
	private:
		static const int MAIN_FBO_WIDTH;
		static const int MAIN_FBO_HEIGHT;
		static const int REFLECTION_FBO_WIDTH;
		static const int REFLECTION_FBO_HEIGHT;
		static const int REFRACTION_FBO_WIDTH;
		static const int REFRACTION_FBO_HEIGHT;




	private:
		std::shared_ptr<EntityRenderer> m_entityRenderer;
		std::shared_ptr<TerrainRenderer> m_terrainRenderer;
		std::shared_ptr<SkyboxRenderer> m_skyboxRenderer;
		std::shared_ptr<GuiRenderer> m_guiRenderer;
		std::shared_ptr<WaterRenderer> m_waterRenderer;
		std::shared_ptr<EntityShadowRenderer> m_entityShadowRenderer;

		RenderScene m_scene;
		std::vector<std::shared_ptr<Models::GuiRenderElement>> m_guiRenderElements;

		std::shared_ptr<OpenGL::FrameBufferObject> m_mainFbo;
		std::shared_ptr<OpenGL::WaterReflectionFbo> m_waterReflectionFbo;
		std::shared_ptr<OpenGL::WaterRefractionFbo> m_waterRefractionFbo;
		std::shared_ptr<OpenGL::ShadowMapFbo> m_shadowMapFbo;

		std::shared_ptr<Projection::OrthoProjectionBox> m_shadowBox;

		float m_waterHeight;

	public:
		RenderEngine();
		RenderEngine(
			const std::shared_ptr<OpenGL::FrameBufferObject> mainFbo,
			const std::shared_ptr<OpenGL::WaterReflectionFbo> waterReflectionFbo,
			const std::shared_ptr<OpenGL::WaterRefractionFbo> waterRefractionFbo,
			const std::shared_ptr<OpenGL::ShadowMapFbo> shadowMapFbo,
			const std::shared_ptr<Projection::OrthoProjectionBox> shadowBox,
			const std::shared_ptr<EntityRenderer> entityRenderer, 
			const std::shared_ptr<TerrainRenderer> terrainRenderer, 
			const std::shared_ptr<SkyboxRenderer> skyboxRenderer,
			const std::shared_ptr<WaterRenderer> waterRenderer,
			const std::shared_ptr<GuiRenderer> guiRenderer,
			const std::shared_ptr<EntityShadowRenderer> entityShadowRenderer);
		RenderEngine(const RenderEngine & other);
		~RenderEngine();



		std::shared_ptr<EntityRenderer> getEntityRenderer() const;
		std::shared_ptr<TerrainRenderer> getTerrainRenderer() const;
		std::shared_ptr<SkyboxRenderer> getSkyboxRenderer() const;
		std::shared_ptr<WaterRenderer> getWaterRenderer() const;
		std::shared_ptr<GuiRenderer> getGuiRenderer() const;
		std::shared_ptr<EntityShadowRenderer> getEntityShadowRenderer() const;
		std::shared_ptr<OpenGL::FrameBufferObject> getMainFbo() const;
		std::shared_ptr<OpenGL::WaterReflectionFbo> getWaterReflectionFbo() const;
		std::shared_ptr<OpenGL::WaterRefractionFbo> getWaterRefractionFbo() const;
		
		void setWaterHeight(float height);
		void loadScene(const RenderScene & scene);
		void loadGuiRenderElements(const std::vector<std::shared_ptr<Models::GuiRenderElement>> & guiRenderElements);
		void render() const;



		RenderEngine & operator=(const RenderEngine & other);



		void onWindowResized(Events::WindowResizeEvent & e) override;



	private:
		void renderEntities(const Cameras::Camera & camera, const std::vector<std::shared_ptr<Models::LightSource>> & lights) const;
		void renderTerrains(const Cameras::Camera & camera, const std::vector<std::shared_ptr<Models::LightSource>> & lights) const;
		void renderSkybox(const Cameras::Camera & camera, const Models::SkyboxRenderModel & skybox) const;
		void renderWater(const Cameras::Camera & camera, const std::vector<std::shared_ptr<Models::LightSource>> & lights) const;
		void renderGui() const;
		void renderEntityShadows(const Cameras::Camera & camera, const Models::LightSource & sun, Projection::OrthoProjectionBox & shadowBox) const;
	};
}

