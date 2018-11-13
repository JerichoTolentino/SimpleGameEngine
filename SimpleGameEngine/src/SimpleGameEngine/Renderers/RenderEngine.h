#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../Cameras/Camera.h"
#include "../Models/Entity.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"

/// <summary>
/// Specialize in std::less so <see cref="GeometryModel"/> can be used as a key in a <see cref="std::map"/>.
/// </summary>
template<> struct std::less<SimpleGameEngine::Models::GeometryModel>
{
	bool operator() (const SimpleGameEngine::Models::GeometryModel & lhs, const SimpleGameEngine::Models::GeometryModel & rhs) const
	{
		return lhs.___getObjectId() < rhs.___getObjectId();
	}
};

namespace SimpleGameEngine::Renderers
{
	class RenderEngine
	{
	private:
		std::map<Models::GeometryModel, std::vector<Models::Entity>> m_entityBatches;
		std::map<Models::GeometryModel, std::vector<Models::TerrainRenderModel>> m_terrainBatches;
		Models::SkyboxRenderModel m_skybox;
		std::shared_ptr<Cameras::Camera> m_camera;
		Math::Vec3 m_lightPosition;

		EntityRenderer m_entityRenderer;
		TerrainRenderer m_terrainRenderer;
		SkyboxRenderer m_skyboxRenderer;



	public:
		RenderEngine();
		RenderEngine(EntityRenderer entityRenderer, TerrainRenderer terrainRenderer, SkyboxRenderer skyboxRenderer);
		RenderEngine(const RenderEngine & other);
		~RenderEngine();



		std::map<Models::GeometryModel, std::vector<Models::Entity>> getEntityBatches() const;
		std::map<Models::GeometryModel, std::vector<Models::TerrainRenderModel>> getTerrainBatches() const;
		Models::SkyboxRenderModel getSkybox() const;
		std::shared_ptr<Cameras::Camera> getCamera() const;
		Math::Vec3 getLightPosition() const;
		EntityRenderer getEntityRenderer() const;
		TerrainRenderer getTerrainRenderer() const;
		SkyboxRenderer getSkyboxRenderer() const;


		void loadProjectionMatrix(Math::Mat4 proj);
		void loadEntity(Models::Entity entity);
		void loadTerrain(Models::TerrainRenderModel terrain);
		void loadSkybox(Models::SkyboxRenderModel skybox);
		void loadCamera(const std::shared_ptr<Cameras::Camera> camera);
		void loadLight(Math::Vec3 lightPosition);
		void render() const;



		RenderEngine & operator=(const RenderEngine & other);
	};
}

