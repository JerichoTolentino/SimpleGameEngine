#pragma once
#include "../Shaders/Shader.h"

namespace SimpleGameEngine::Renderers
{
	class EntityRenderer
	{
	private:
		Shaders::Shader m_shader;
	public:
		EntityRenderer(Shaders::Shader m_shader);
		~EntityRenderer();



		void loadEntity(Entity* entity, Skybox* skybox) const;
		void render(Entity* e) const;
		void unloadEntity() const;
		void loadProjectionMatrix(Mat4 proj) const;
		void loadCamera(Camera* camera) const;
		void loadLight(Vec3 light) const;
	};
}
