#pragma once
#include <memory>
#include "../Cameras/Camera.h"
#include "../Shaders/Shader.h"
#include "../Models/Entity.h"
#include "../Models/LightSource.h"
#include "../Math/Mat4.h"

namespace SimpleGameEngine::Renderers
{
	class EntityRenderer
	{
	private:
		std::shared_ptr<Shaders::Shader> m_shader;



	public:
		EntityRenderer();
		EntityRenderer(const std::shared_ptr<Shaders::Shader> shader);
		EntityRenderer(const EntityRenderer & other);
		~EntityRenderer();

		void loadClippingPlane(const Math::Vec4 & clippingPlane) const;
		void loadCamera(const Cameras::Camera & camera) const;
		void loadLights(const std::vector<std::shared_ptr<Models::LightSource>> & lights) const;
		void loadProjectionMatrix(const Math::Mat4 & proj) const;
		void loadRenderModel(const Models::RenderModel & entityModel) const;
		void loadEntity(const Models::Entity & entity) const;
		void render(const Models::Entity & entity) const;
		void unloadRenderModel() const;



		EntityRenderer & operator=(const EntityRenderer & other);
	};
}
