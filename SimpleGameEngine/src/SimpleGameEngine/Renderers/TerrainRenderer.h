#pragma once
#include <string>
#include "../Cameras/Camera.h"
#include "../Shaders/Shader.h"
#include "../Math/Mat4.h"
#include "../Math/Vec3.h"
#include "../Models/TerrainRenderModel.h"

namespace SimpleGameEngine::Renderers
{
	class TerrainRenderer
	{
	private:
		Shaders::Shader m_shader;



	public:
		TerrainRenderer();
		TerrainRenderer(Shaders::Shader shader);
		TerrainRenderer(const TerrainRenderer & other);
		~TerrainRenderer();


		void loadTerrain(Models::TerrainRenderModel terrain) const;
		void render(Models::TerrainRenderModel terrain) const;
		void unloadTerrain() const;
		void loadProjectionMatrix(Math::Mat4 proj) const;
		void loadCamera(Cameras::Camera camera) const;
		void loadLight(Math::Vec3 light) const;



		TerrainRenderer & operator=(const TerrainRenderer & other);
	};
}
