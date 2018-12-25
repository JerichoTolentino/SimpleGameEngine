#pragma once
#include "../Shaders/Shader.h"
#include "../Models/RenderModel.h"
#include "../Models/Entity.h"

namespace SimpleGameEngine::Renderers
{
	class EntityShadowRenderer
	{
	private:
		std::shared_ptr<Shaders::Shader> m_shader;



	public:
		EntityShadowRenderer();
		EntityShadowRenderer(const EntityShadowRenderer & other);
		EntityShadowRenderer(const std::shared_ptr<Shaders::Shader> shader);
		~EntityShadowRenderer();


		// TODO: REMOVE
		void loadModelMatrix(const Math::Mat4 & matrix) const;
		void loadViewMatrix(const Math::Mat4 & matrix) const;
		void loadProjectionMatrix(const Math::Mat4 & matrix) const;

		void loadTextureUnits() const;
		void loadModelViewProjectionMatrix(const Math::Mat4 & modelViewProjectionMatrix) const;
		void loadRenderModel(const Models::RenderModel & renderModel) const;
		void render(const Models::Entity & entity) const;
		void unloadRenderModel() const;



		EntityShadowRenderer & operator=(const EntityShadowRenderer & other);
	};
}
