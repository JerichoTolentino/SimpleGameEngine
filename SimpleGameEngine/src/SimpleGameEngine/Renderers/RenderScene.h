#pragma once
#include <memory>
#include <map>
#include <vector>
#include "../Models/Entity.h"
#include "../Models/TerrainRenderModel.h"
#include "../Models/SkyboxRenderModel.h"
#include "../Models/LightSource.h"
#include "../Cameras/Camera.h"

typedef std::map<
			std::shared_ptr<SimpleGameEngine::Models::GeometryModel>, 
			std::vector<std::shared_ptr<SimpleGameEngine::Models::Entity>>> EntityBatchMap;
typedef std::map<
			std::shared_ptr<SimpleGameEngine::Models::GeometryModel>, 
			std::vector<std::shared_ptr<SimpleGameEngine::Models::TerrainRenderModel>>> TerrainBatchMap;

namespace SimpleGameEngine::Renderers
{
	class RenderScene
	{
	private:
		std::shared_ptr<EntityBatchMap> m_entityBatches;
		std::shared_ptr<TerrainBatchMap> m_terrainBatches;
		std::shared_ptr<std::vector<std::shared_ptr<Models::LightSource>>> m_lights;

		std::shared_ptr<Models::SkyboxRenderModel> m_skybox;
		std::shared_ptr<Cameras::Camera> m_camera;
		std::shared_ptr<Math::Mat4> m_projectionMatrix;



	public:
		RenderScene();
		RenderScene(const RenderScene & other);
		virtual ~RenderScene();



		std::shared_ptr<Models::SkyboxRenderModel> getSkybox() const;
		std::shared_ptr<Cameras::Camera> getCamera() const;
		std::shared_ptr<Math::Mat4> getProjectionMatrix() const;
		std::shared_ptr<std::vector<std::shared_ptr<Models::LightSource>>> getLights() const;
		std::shared_ptr<EntityBatchMap> getEntityBatches() const;
		std::shared_ptr<TerrainBatchMap> getTerrainBatches() const;

		void setProjectionMatrix(const std::shared_ptr<Math::Mat4> projectionMatrix);
		void setSkybox(const std::shared_ptr<Models::SkyboxRenderModel> skybox);
		void setCamera(const std::shared_ptr<Cameras::Camera> camera);

		void addEntity(const std::shared_ptr<Models::Entity> entity);
		void addTerrain(const std::shared_ptr<Models::TerrainRenderModel> terrain);
		void addLight(const std::shared_ptr<Models::LightSource> light);



		RenderScene & operator=(const RenderScene & other);
	};
}

