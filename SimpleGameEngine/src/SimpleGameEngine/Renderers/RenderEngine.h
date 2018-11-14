#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../Cameras/Camera.h"
#include "../Models/Entity.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"

namespace SimpleGameEngine::Renderers
{
	class RenderEngine
	{
	private:
		std::shared_ptr<std::map<
			std::shared_ptr<Models::GeometryModel>, 
			std::vector<std::shared_ptr<Models::Entity>>>> m_entityBatches;
		std::shared_ptr<std::map<
			std::shared_ptr<Models::GeometryModel>, 
			std::vector<std::shared_ptr<Models::TerrainRenderModel>>>> m_terrainBatches;

		std::shared_ptr<Models::SkyboxRenderModel> m_skybox;
		std::shared_ptr<Cameras::Camera> m_camera;
		std::shared_ptr<Math::Vec3> m_lightPosition;

		std::shared_ptr<EntityRenderer> m_entityRenderer;
		std::shared_ptr<TerrainRenderer> m_terrainRenderer;
		std::shared_ptr<SkyboxRenderer> m_skyboxRenderer;



	public:
		RenderEngine();
		RenderEngine(
			const std::shared_ptr<EntityRenderer> entityRenderer, 
			const std::shared_ptr<TerrainRenderer> terrainRenderer, 
			const std::shared_ptr<SkyboxRenderer> skyboxRenderer);
		RenderEngine(const RenderEngine & other);
		~RenderEngine();


		std::shared_ptr<Models::SkyboxRenderModel> getSkybox() const;
		std::shared_ptr<Cameras::Camera> getCamera() const;
		std::shared_ptr<Math::Vec3> getLightPosition() const;
		std::shared_ptr<EntityRenderer> getEntityRenderer() const;
		std::shared_ptr<TerrainRenderer> getTerrainRenderer() const;
		std::shared_ptr<SkyboxRenderer> getSkyboxRenderer() const;


		void loadProjectionMatrix(const Math::Mat4 & proj);
		void loadEntity(const std::shared_ptr<Models::Entity> entity);
		void loadTerrain(const std::shared_ptr<Models::TerrainRenderModel> terrain);
		void loadSkybox(const std::shared_ptr<Models::SkyboxRenderModel> skybox);
		void loadCamera(const std::shared_ptr<Cameras::Camera> camera);
		void loadLight(const std::shared_ptr<Math::Vec3> lightPosition);
		void render() const;



		RenderEngine & operator=(const RenderEngine & other);
	};
}

