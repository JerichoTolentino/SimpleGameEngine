#pragma once
#include <memory>
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "RenderScene.h"

namespace SimpleGameEngine::Renderers
{
	class RenderEngine
	{
	private:
		std::shared_ptr<EntityRenderer> m_entityRenderer;
		std::shared_ptr<TerrainRenderer> m_terrainRenderer;
		std::shared_ptr<SkyboxRenderer> m_skyboxRenderer;
		RenderScene m_scene;


	public:
		RenderEngine();
		RenderEngine(
			const std::shared_ptr<EntityRenderer> entityRenderer, 
			const std::shared_ptr<TerrainRenderer> terrainRenderer, 
			const std::shared_ptr<SkyboxRenderer> skyboxRenderer);
		RenderEngine(const RenderEngine & other);
		~RenderEngine();



		std::shared_ptr<EntityRenderer> getEntityRenderer() const;
		std::shared_ptr<TerrainRenderer> getTerrainRenderer() const;
		std::shared_ptr<SkyboxRenderer> getSkyboxRenderer() const;
		
		void loadScene(const RenderScene & scene);
		void render() const;



		RenderEngine & operator=(const RenderEngine & other);
	};
}

