#include "RenderEngine.h"

using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Renderers
{
	RenderEngine::RenderEngine()
	{
	}

	RenderEngine::RenderEngine(EntityRenderer entityRenderer, TerrainRenderer terrainRenderer, SkyboxRenderer skyboxRenderer)
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



	std::map<Models::GeometryModel, std::vector<Models::Entity>> RenderEngine::getEntityBatches() const
	{
		return m_entityBatches;
	}

	std::map<Models::GeometryModel, std::vector<Models::TerrainRenderModel>> RenderEngine::getTerrainBatches() const
	{
		return m_terrainBatches;
	}

	Models::SkyboxRenderModel RenderEngine::getSkybox() const
	{
		return m_skybox;
	}

	Cameras::Camera RenderEngine::getCamera() const
	{
		return m_camera;
	}

	Math::Vec3 RenderEngine::getLightPosition() const
	{
		return m_lightPosition;
	}
	EntityRenderer RenderEngine::getEntityRenderer() const
	{
		return m_entityRenderer;
	}

	TerrainRenderer RenderEngine::getTerrainRenderer() const
	{
		return m_terrainRenderer;
	}

	SkyboxRenderer RenderEngine::getSkyboxRenderer() const
	{
		return m_skyboxRenderer;
	}



	void RenderEngine::loadProjectionMatrix(Math::Mat4 proj)
	{
		m_entityRenderer.loadProjectionMatrix(proj);
		m_terrainRenderer.loadProjectionMatrix(proj);
		m_skyboxRenderer.loadProjectionMatrix(proj);
	}

	void RenderEngine::loadEntity(Models::Entity entity)
	{
		GeometryModel model = entity.getRenderModel().getGeometryModel();
		bool modelAlreadyLoaded = m_entityBatches.count(model);
		
		if (!modelAlreadyLoaded)
			m_entityBatches.insert(std::pair<GeometryModel, std::vector<Entity>>(model, std::vector<Entity>()));

		m_entityBatches[model].push_back(entity);
	}

	void RenderEngine::loadTerrain(Models::TerrainRenderModel terrain)
	{
		GeometryModel model = terrain.getTerrainModel().getGeometryModel();
		bool modelAlreadyLoaded = m_terrainBatches.count(model);

		if (!modelAlreadyLoaded)
			m_terrainBatches.insert(std::pair<GeometryModel, std::vector<TerrainRenderModel>>(model, std::vector<TerrainRenderModel>()));

		m_terrainBatches[model].push_back(terrain);
	}

	void RenderEngine::loadSkybox(Models::SkyboxRenderModel skybox)
	{
		m_skybox = skybox;
	}

	void RenderEngine::loadCamera(Cameras::Camera camera)
	{
		m_camera = camera;
	}

	void RenderEngine::loadLight(Math::Vec3 lightPosition)
	{
		m_lightPosition = lightPosition;
	}

	void RenderEngine::render() const
	{
		// Render terrain
		for (auto batchIter = m_terrainBatches.begin(); batchIter != m_terrainBatches.end(); batchIter++)
		{
			auto renderModels = batchIter->second;
			for (auto modelIter = renderModels.begin(); modelIter != renderModels.end(); modelIter++)
			{
				TerrainRenderModel renderModel = *modelIter;

				m_terrainRenderer.loadCamera(m_camera);
				m_terrainRenderer.loadLight(m_lightPosition);
				m_terrainRenderer.loadTerrain(renderModel);
				m_terrainRenderer.render(renderModel);
				m_terrainRenderer.unloadTerrain();
			}
		}

		// Render entities
		for (auto batchIter = m_entityBatches.begin(); batchIter != m_entityBatches.end(); batchIter++)
		{
			auto renderModels = batchIter->second;
			for (auto modelIter = renderModels.begin(); modelIter != renderModels.end(); modelIter++)
			{
				Entity entity = *modelIter;

				m_entityRenderer.loadCamera(m_camera);
				m_entityRenderer.loadLight(m_lightPosition);
				m_entityRenderer.loadEntity(entity);
				m_entityRenderer.render(entity);
				m_entityRenderer.unloadEntity();
			}
		}

		// Render skybox
		m_skyboxRenderer.loadCamera(m_camera);
		m_skyboxRenderer.loadSkybox(m_skybox);
		m_skyboxRenderer.render(m_skybox);
		m_skyboxRenderer.unloadSkybox();

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