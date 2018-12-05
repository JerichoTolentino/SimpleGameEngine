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
		const std::shared_ptr<SkyboxRenderer> skyboxRenderer,
		const std::shared_ptr<GuiRenderer> guiRenderer)
		: RenderEngine()
	{
		m_entityRenderer = entityRenderer;
		m_terrainRenderer = terrainRenderer;
		m_skyboxRenderer = skyboxRenderer;
		m_guiRenderer = guiRenderer;
	}

	RenderEngine::RenderEngine(const RenderEngine & other)
		: RenderEngine(other.m_entityRenderer, other.m_terrainRenderer, other.m_skyboxRenderer, other.m_guiRenderer)
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

	std::shared_ptr<GuiRenderer> RenderEngine::getGuiRenderer() const
	{
		return m_guiRenderer;
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

	void RenderEngine::loadGuiRenderElements(const std::vector<std::shared_ptr<Models::GuiRenderElement>>& guiRenderElements)
	{
		for (auto guiRenderElement : guiRenderElements)
		{
			m_guiRenderElements.push_back(guiRenderElement);
		}
	}

	void RenderEngine::render() const
	{
		Camera camera = *m_scene.getCamera();
		auto lights = *m_scene.getLights();
		auto skybox = m_scene.getSkybox();

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
		if (skybox != nullptr)
		{
			m_skyboxRenderer->loadCamera(camera);
			m_skyboxRenderer->loadSkybox(*skybox);
			m_skyboxRenderer->render(*skybox);
			m_skyboxRenderer->unloadSkybox();
		}

		// Render GUI elements
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (const auto & guiRenderElement : m_guiRenderElements)
		{
			m_guiRenderer->loadGuiRenderElement(*guiRenderElement);
			m_guiRenderer->render(*guiRenderElement);
			m_guiRenderer->unloadGuiRenderElement();
		}
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}



	RenderEngine & RenderEngine::operator=(const RenderEngine & other)
	{
		m_entityRenderer = other.m_entityRenderer;
		m_terrainRenderer = other.m_terrainRenderer;
		m_skyboxRenderer = other.m_skyboxRenderer;
		m_guiRenderer = other.m_guiRenderer;

		return *this;
	}
}