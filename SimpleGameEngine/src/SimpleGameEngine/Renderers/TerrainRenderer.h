#pragma once
#include <string>
#include <memory>
#include "../Cameras/Camera.h"
#include "../Shaders/Shader.h"
#include "../Math/Mat4.h"
#include "../Math/Vec3.h"
#include "../Models/TerrainRenderModel.h"
#include "../Models/LightSource.h"

namespace SimpleGameEngine::Renderers
{
	class TerrainRenderer
	{
	private:
		std::shared_ptr<Shaders::Shader> m_shader;



	public:
		TerrainRenderer();
		TerrainRenderer(const std::shared_ptr<Shaders::Shader> shader);
		TerrainRenderer(const TerrainRenderer & other);
		~TerrainRenderer();


		void loadTerrain(const Models::TerrainRenderModel & terrain) const;
		void render(const Models::TerrainRenderModel & terrain) const;
		void unloadTerrain() const;
		void loadProjectionMatrix(const Math::Mat4 & proj) const;
		void loadCamera(const Cameras::Camera & camera) const;
		void loadLights(const std::vector<Models::LightSource> & lights) const;



		TerrainRenderer & operator=(const TerrainRenderer & other);
	};
}
