#include "sgepch.h"
#include "RenderEngine.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Cameras;

namespace SimpleGameEngine::Renderers
{
	RenderEngine::RenderEngine()
	{
	}

	RenderEngine::RenderEngine(
		const std::shared_ptr<EntityRenderer> entityRenderer, 
		const std::shared_ptr<TerrainRenderer> terrainRenderer, 
		const std::shared_ptr<SkyboxRenderer> skyboxRenderer)
		: RenderEngine()
	{
		m_entityRenderer = entityRenderer;
		m_terrainRenderer = terrainRenderer;
		m_skyboxRenderer = skyboxRenderer;
	}

	RenderEngine::RenderEngine(const RenderEngine & other)
		: RenderEngine(other.m_entityRenderer, other.m_terrainRenderer, other.m_skyboxRenderer)
	{
	}

	RenderEngine::~RenderEngine()
	{
	}



	std::shared_ptr<EntityRenderer> RenderEngine::getEntityRenderer() const
	{
		return m_entityRenderer;
	}

	std::shared_ptr<TerrainRenderer> RenderEngine::getTerrainRenderer() const
	{
		return m_terrainRenderer;
	}

	std::shared_ptr<SkyboxRenderer> RenderEngine::getSkyboxRenderer() const
	{
		return m_skyboxRenderer;
	}

	void RenderEngine::loadScene(const RenderScene & scene)
	{
		m_scene = scene;

		// Load projection matrix
		Mat4 projectionMatrix = *scene.getProjectionMatrix();
		m_entityRenderer->loadProjectionMatrix(projectionMatrix);
		m_terrainRenderer->loadProjectionMatrix(projectionMatrix);
		m_skyboxRenderer->loadProjectionMatrix(projectionMatrix);
	}

	void RenderEngine::render() const
	{
		Camera camera = *m_scene.getCamera();
		auto lights = *m_scene.getLights();
		SkyboxRenderModel skybox = *m_scene.getSkybox();

		// Render entities
		for (const auto & entityBatch : *m_scene.getEntityBatches())
		{
			auto entities = entityBatch.second;

			m_entityRenderer->loadRenderModel(*entities.at(0)->getRenderModel());

			for (const auto entity : entities)
			{
				m_entityRenderer->loadCamera(camera);
				m_entityRenderer->loadLights(lights);
				m_entityRenderer->loadEntity(*entity);
				m_entityRenderer->render(*entity);
			}

			m_entityRenderer->unloadRenderModel();
		}

		// Render terrain
		for (const auto & terrainBatch : *m_scene.getTerrainBatches())
		{
			auto terrains = terrainBatch.second;
			for (const auto terrain : terrains)
			{
				m_terrainRenderer->loadCamera(camera);
				m_terrainRenderer->loadLights(lights);
				m_terrainRenderer->loadTerrain(*terrain);
				m_terrainRenderer->render(*terrain);
				m_terrainRenderer->unloadTerrain();
			}
		}

		// Render skybox
		m_skyboxRenderer->loadCamera(camera);
		m_skyboxRenderer->loadSkybox(skybox);
		m_skyboxRenderer->render(skybox);
		m_skyboxRenderer->unloadSkybox();
	}



	RenderEngine & RenderEngine::operator=(const RenderEngine & other)
	{
		m_entityRenderer = other.m_entityRenderer;
		m_terrainRenderer = other.m_terrainRenderer;
		m_skyboxRenderer = other.m_skyboxRenderer;

		return *this;
	}
}