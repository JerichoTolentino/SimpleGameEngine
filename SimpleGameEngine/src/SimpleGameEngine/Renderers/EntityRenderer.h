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
		std::shared_ptr<Shaders::Shader> m_shader;



	public:
		EntityRenderer();
		EntityRenderer(const std::shared_ptr<Shaders::Shader> m_shader);
		EntityRenderer(const EntityRenderer & other);
		~EntityRenderer();

		void loadCamera(const Cameras::Camera & camera) const;
		void loadLight(const Math::Vec3 & light) const;
		void loadProjectionMatrix(const Math::Mat4 & proj) const;
		void loadEntity(const Models::Entity & entity) const;
		void render(const Models::Entity & entity) const;
		void unloadEntity() const;



		EntityRenderer & operator=(const EntityRenderer & other);
	};
}
