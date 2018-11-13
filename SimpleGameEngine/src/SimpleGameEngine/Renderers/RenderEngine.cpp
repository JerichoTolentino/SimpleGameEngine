#include "RenderEngine.h"
#include "../Log.h"

using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Renderers
{
	RenderEngine::RenderEngine()
	{
		m_entityBatches = std::make_shared<std::map<std::shared_ptr<Models::GeometryModel>, std::vector<std::shared_ptr<Models::Entity>>>>();
		m_terrainBatches = std::make_shared<std::map<std::shared_ptr<Models::GeometryModel>, std::vector<std::shared_ptr<Models::TerrainRenderModel>>>>();
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



	std::shared_ptr<Models::SkyboxRenderModel> RenderEngine::getSkybox() const
	{
		return m_skybox;
	}

	std::shared_ptr<Cameras::Camera> RenderEngine::getCamera() const
	{
		return m_camera;
	}

	std::shared_ptr<Math::Vec3> RenderEngine::getLightPosition() const
	{
		return m_lightPosition;
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



	void RenderEngine::loadProjectionMatrix(const Math::Mat4 & proj)
	{
		m_entityRenderer->loadProjectionMatrix(proj);
		m_terrainRenderer->loadProjectionMatrix(proj);
		m_skyboxRenderer->loadProjectionMatrix(proj);

		SGE_CORE_TRACE("Loaded projection matrix into RenderEngine:\n{0}", proj.toString());
	}

	void RenderEngine::loadEntity(const std::shared_ptr<Models::Entity> entity)
	{
		auto model = entity->getRenderModel()->getGeometryModel();
		bool modelAlreadyLoaded = m_entityBatches->count(model);
		
		if (!modelAlreadyLoaded)
			m_entityBatches->insert(std::pair<std::shared_ptr<GeometryModel>, std::vector<std::shared_ptr<Entity>>>(model, std::vector<std::shared_ptr<Entity>>()));

		m_entityBatches->at(model).push_back(entity);
	}

	void RenderEngine::loadTerrain(const std::shared_ptr<Models::TerrainRenderModel> terrain)
	{
		auto model = terrain->getTerrainModel()->getGeometryModel();
		bool modelAlreadyLoaded = m_terrainBatches->count(model);

		if (!modelAlreadyLoaded)
			m_terrainBatches->insert(std::pair<std::shared_ptr<GeometryModel>, std::vector<std::shared_ptr<TerrainRenderModel>>>(model, std::vector<std::shared_ptr<TerrainRenderModel>>()));

		m_terrainBatches->at(model).push_back(terrain);
	}

	void RenderEngine::loadSkybox(const std::shared_ptr<Models::SkyboxRenderModel> skybox)
	{
		m_skybox = skybox;
	}

	void RenderEngine::loadCamera(const std::shared_ptr<Cameras::Camera> camera)
	{
		m_camera = camera;
	}

	void RenderEngine::loadLight(const std::shared_ptr<Math::Vec3> lightPosition)
	{
		m_lightPosition = lightPosition;
	}

	void RenderEngine::render() const
	{
		// Render terrain
		for (auto batchIter = m_terrainBatches->begin(); batchIter != m_terrainBatches->end(); batchIter++)
		{
			auto renderModels = batchIter->second;
			for (auto modelIter = renderModels.begin(); modelIter != renderModels.end(); modelIter++)
			{
				auto renderModel = *modelIter;

				m_terrainRenderer->loadCamera(*m_camera);
				m_terrainRenderer->loadLight(*m_lightPosition);
				m_terrainRenderer->loadTerrain(*renderModel);
				m_terrainRenderer->render(*renderModel);
				m_terrainRenderer->unloadTerrain();
			}
		}

		// Render entities
		for (auto batchIter = m_entityBatches->begin(); batchIter != m_entityBatches->end(); batchIter++)
		{
			auto renderModels = batchIter->second;
			for (auto modelIter = renderModels.begin(); modelIter != renderModels.end(); modelIter++)
			{
				auto entity = *modelIter;

				m_entityRenderer->loadCamera(*m_camera);
				m_entityRenderer->loadLight(*m_lightPosition);
				m_entityRenderer->loadEntity(*entity);
				m_entityRenderer->render(*entity);
				m_entityRenderer->unloadEntity();
			}
		}

		// Render skybox
		m_skyboxRenderer->loadCamera(*m_camera);
		m_skyboxRenderer->loadSkybox(*m_skybox);
		m_skyboxRenderer->render(*m_skybox);
		m_skyboxRenderer->unloadSkybox();

	}



	RenderEngine & RenderEngine::operator=(const RenderEngine & other)
	{
		m_entityBatches = other.m_entityBatches;
		m_terrainBatches = other.m_terrainBatches;
		m_skybox = other.m_skybox;
		m_camera = other.m_camera;
		m_lightPosition = other.m_lightPosition;
		m_entityRenderer = other.m_entityRenderer;
		m_terrainRenderer = other.m_terrainRenderer;
		m_skyboxRenderer = other.m_skyboxRenderer;

		return *this;
	}
}