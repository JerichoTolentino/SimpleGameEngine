#include "sgepch.h"
#include "RenderScene.h"

using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Renderers
{
	RenderScene::RenderScene()
	{
		m_entityBatches = std::make_shared<EntityBatchMap>();
		m_terrainBatches = std::make_shared<TerrainBatchMap>();
		m_waterBatches = std::make_shared<WaterBatchMap>();
		m_lights = std::make_shared<std::vector<std::shared_ptr<Models::LightSource>>>();
	}

	RenderScene::RenderScene(const RenderScene & other)
	{
		m_entityBatches = other.m_entityBatches;
		m_terrainBatches = other.m_terrainBatches;
		m_waterBatches = other.m_waterBatches;
		m_lights = other.m_lights;
		m_camera = other.m_camera;
		m_skybox = other.m_skybox;
		m_projectionMatrix = other.m_projectionMatrix;
	}


	RenderScene::~RenderScene()
	{
	}



	std::shared_ptr<Models::SkyboxRenderModel> RenderScene::getSkybox() const
	{
		return m_skybox;
	}

	std::shared_ptr<Cameras::Camera> RenderScene::getCamera() const
	{
		return m_camera;
	}

	std::shared_ptr<Math::Mat4> RenderScene::getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	std::shared_ptr<std::vector<std::shared_ptr<Models::LightSource>>> RenderScene::getLights() const
	{
		return m_lights;
	}

	std::shared_ptr<EntityBatchMap> RenderScene::getEntityBatches() const
	{
		return m_entityBatches;
	}

	std::shared_ptr<TerrainBatchMap> RenderScene::getTerrainBatches() const
	{
		return m_terrainBatches;
	}

	std::shared_ptr<WaterBatchMap> RenderScene::getWaterBatches() const
	{
		return m_waterBatches;
	}



	void RenderScene::setProjectionMatrix(const std::shared_ptr<Math::Mat4> projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	void RenderScene::setSkybox(const std::shared_ptr<Models::SkyboxRenderModel> skybox)
	{
		m_skybox = skybox;
	}

	void RenderScene::setCamera(const std::shared_ptr<Cameras::Camera> camera)
	{
		m_camera = camera;
	}



	void RenderScene::addEntity(const std::shared_ptr<Models::Entity> entity)
	{
		auto model = entity->getRenderModel()->getGeometryModel();
		bool modelAlreadyLoaded = m_entityBatches->count(model);

		if (!modelAlreadyLoaded)
			m_entityBatches->insert(std::pair<std::shared_ptr<GeometryModel>, std::vector<std::shared_ptr<Entity>>>(model, std::vector<std::shared_ptr<Entity>>()));

		m_entityBatches->at(model).push_back(entity);
	}

	void RenderScene::addTerrain(const std::shared_ptr<Models::TerrainRenderModel> terrain)
	{
		auto model = terrain->getTerrainModel()->getGeometryModel();
		bool modelAlreadyLoaded = m_terrainBatches->count(model);

		if (!modelAlreadyLoaded)
			m_terrainBatches->insert(std::pair<std::shared_ptr<GeometryModel>, std::vector<std::shared_ptr<TerrainRenderModel>>>(model, std::vector<std::shared_ptr<TerrainRenderModel>>()));

		m_terrainBatches->at(model).push_back(terrain);
	}

	void RenderScene::addLight(const std::shared_ptr<Models::LightSource> light)
	{
		m_lights->push_back(light);
	}

	void RenderScene::addWater(const std::shared_ptr<Models::WaterEntity> water)
	{
		auto model = water->getWaterRenderModel()->getWaterModel();
		bool modelAlreadyLoaded = m_waterBatches->count(model);

		if (!modelAlreadyLoaded)
			m_waterBatches->insert(std::pair<std::shared_ptr<WaterModel>, std::vector<std::shared_ptr<WaterEntity>>>(model, std::vector<std::shared_ptr<WaterEntity>>()));

		m_waterBatches->at(model).push_back(water);
	}



	RenderScene & RenderScene::operator=(const RenderScene & other)
	{
		m_entityBatches = other.m_entityBatches;
		m_terrainBatches = other.m_terrainBatches;
		m_waterBatches = other.m_waterBatches;
		m_lights = other.m_lights;
		m_camera = other.m_camera;
		m_skybox = other.m_skybox;
		m_projectionMatrix = other.m_projectionMatrix;

		return *this;
	}
}
