#include "sgepch.h"
#include "RenderEngine.h"

#include "../Loaders/FboLoader.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Loaders;

namespace SimpleGameEngine::Renderers
{
	const int RenderEngine::MAIN_FBO_WIDTH = 1200;
	const int RenderEngine::MAIN_FBO_HEIGHT = 800;
	const int RenderEngine::REFLECTION_FBO_WIDTH = 320;
	const int RenderEngine::REFLECTION_FBO_HEIGHT= 180;
	const int RenderEngine::REFRACTION_FBO_WIDTH= 1280;
	const int RenderEngine::REFRACTION_FBO_HEIGHT= 720;

	RenderEngine::RenderEngine()
	{
	}

	RenderEngine::RenderEngine(
		const std::shared_ptr<EntityRenderer> entityRenderer,
		const std::shared_ptr<TerrainRenderer> terrainRenderer,
		const std::shared_ptr<SkyboxRenderer> skyboxRenderer,
		const std::shared_ptr<WaterRenderer> waterRenderer,
		const std::shared_ptr<GuiRenderer> guiRenderer)
		:
		m_entityRenderer(entityRenderer),
		m_terrainRenderer(terrainRenderer),
		m_skyboxRenderer(skyboxRenderer),
		m_waterRenderer(waterRenderer),
		m_guiRenderer(guiRenderer)
	{
		// Initialize default FBO
		m_mainFbo = OpenGL::FrameBufferObject(0, MAIN_FBO_WIDTH, MAIN_FBO_HEIGHT);

		// Initialize water FBOs
		m_waterReflectionFbo = FboLoader::CreateWaterReflectionFbo(REFLECTION_FBO_WIDTH, REFLECTION_FBO_HEIGHT);
		m_waterRefractionFbo = FboLoader::CreateWaterRefractionFbo(REFRACTION_FBO_WIDTH, REFRACTION_FBO_HEIGHT);
	}

	RenderEngine::RenderEngine(const RenderEngine & other)
		: RenderEngine(other.m_entityRenderer, other.m_terrainRenderer, other.m_skyboxRenderer, other.m_waterRenderer, other.m_guiRenderer)
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

	std::shared_ptr<WaterRenderer> RenderEngine::getWaterRenderer() const
	{
		return m_waterRenderer;
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
		m_waterRenderer->loadProjectionMatrix(projectionMatrix);
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

		// Render to water FBO
		FboLoader::BindFrameBuffer(m_waterReflectionFbo);
		renderEntities();
		renderTerrains();
		renderSkybox();
		
		// Render to main FBO
		FboLoader::BindFrameBuffer(m_mainFbo);
		renderEntities();
		renderTerrains();
		renderSkybox();
		renderWater();

		// Render GUI elements
		renderGui();
	}



	RenderEngine & RenderEngine::operator=(const RenderEngine & other)
	{
		m_entityRenderer = other.m_entityRenderer;
		m_terrainRenderer = other.m_terrainRenderer;
		m_skyboxRenderer = other.m_skyboxRenderer;
		m_waterRenderer = other.m_waterRenderer;
		m_guiRenderer = other.m_guiRenderer;

		return *this;
	}



	void RenderEngine::renderEntities() const
	{
		Camera camera = *m_scene.getCamera();
		auto lights = *m_scene.getLights();

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
	}

	void RenderEngine::renderTerrains() const
	{
		Camera camera = *m_scene.getCamera();
		auto lights = *m_scene.getLights();

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
	}
	
	void RenderEngine::renderSkybox() const
	{
		Camera camera = *m_scene.getCamera();
		auto skybox = m_scene.getSkybox();

		if (skybox != nullptr)
		{
			m_skyboxRenderer->loadCamera(camera);
			m_skyboxRenderer->loadSkybox(*skybox);
			m_skyboxRenderer->render(*skybox);
			m_skyboxRenderer->unloadSkybox();
		}
	}
	
	void RenderEngine::renderWater() const
	{
		Camera camera = *m_scene.getCamera();
		auto lights = *m_scene.getLights();

		glDisable(GL_CULL_FACE);
		for (const auto & waterBatch : *m_scene.getWaterBatches())
		{
			auto waters = waterBatch.second;

			m_waterRenderer->loadWaterRenderModel(*waters.at(0)->getWaterRenderModel());

			for (const auto water : waters)
			{
				m_waterRenderer->loadCamera(camera);
				m_waterRenderer->loadLights(lights);
				m_waterRenderer->loadWaterEntity(*water);
				m_waterRenderer->render(*water);
			}

			m_waterRenderer->unloadWaterRenderModel();
		}
		glEnable(GL_CULL_FACE);
	}
	
	void RenderEngine::renderGui() const
	{
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
}