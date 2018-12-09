#pragma once
#include <memory>
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "GuiRenderer.h"
#include "RenderScene.h"
#include "../OpenGL/WaterReflectionFbo.h"
#include "../OpenGL/WaterRefractionFbo.h"

namespace SimpleGameEngine::Renderers
{
	class RenderEngine
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

		RenderScene m_scene;
		std::vector<std::shared_ptr<Models::GuiRenderElement>> m_guiRenderElements;

		OpenGL::FrameBufferObject m_mainFbo;
		OpenGL::WaterReflectionFbo m_waterReflectionFbo;
		OpenGL::WaterRefractionFbo m_waterRefractionFbo;



	public:
		RenderEngine();
		RenderEngine(
			const std::shared_ptr<EntityRenderer> entityRenderer, 
			const std::shared_ptr<TerrainRenderer> terrainRenderer, 
			const std::shared_ptr<SkyboxRenderer> skyboxRenderer,
			const std::shared_ptr<WaterRenderer> waterRenderer,
			const std::shared_ptr<GuiRenderer> guiRenderer);
		RenderEngine(const RenderEngine & other);
		~RenderEngine();



		std::shared_ptr<EntityRenderer> getEntityRenderer() const;
		std::shared_ptr<TerrainRenderer> getTerrainRenderer() const;
		std::shared_ptr<SkyboxRenderer> getSkyboxRenderer() const;
		std::shared_ptr<WaterRenderer> getWaterRenderer() const;
		std::shared_ptr<GuiRenderer> getGuiRenderer() const;
		
		void loadScene(const RenderScene & scene);
		void loadGuiRenderElements(const std::vector<std::shared_ptr<Models::GuiRenderElement>> & guiRenderElements);
		void render() const;



		RenderEngine & operator=(const RenderEngine & other);



	private:
		void renderEntities() const;
		void renderTerrains() const;
		void renderSkybox() const;
		void renderWater() const;
		void renderGui() const;
	};
}

