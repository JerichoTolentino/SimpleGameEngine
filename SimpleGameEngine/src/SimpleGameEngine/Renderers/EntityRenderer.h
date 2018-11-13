#pragma once
#include <memory>
#include "../Cameras/Camera.h"
#include "../Shaders/Shader.h"
#include "../Models/Entity.h"
#include "../Math/Mat4.h"

namespace SimpleGameEngine::Renderers
{
	class EntityRenderer
	{
	private:
		Shaders::Shader m_shader;



	public:
		EntityRenderer();
		EntityRenderer(Shaders::Shader m_shader);
		EntityRenderer(const EntityRenderer & other);
		~EntityRenderer();

		void loadCamera(const std::shared_ptr<Cameras::Camera> camera) const;
		void loadLight(Math::Vec3 light) const;
		void loadProjectionMatrix(Math::Mat4 proj) const;
		void loadEntity(Models::Entity entity) const;
		void loadEntity(Models::Entity entity, GLuint reflectionMapTextureId) const;
		void render(Models::Entity entity) const;
		void unloadEntity() const;



		EntityRenderer & operator=(const EntityRenderer & other);
	};
}
