#pragma once
#include <memory>
#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	class Entity
	{
	private:
		std::shared_ptr<RenderModel> m_renderModel;
		std::shared_ptr<SpaceModel> m_spaceModel;
		


	public:
		Entity();
		Entity(const std::shared_ptr<RenderModel> renderModel, const std::shared_ptr<SpaceModel> spaceModel);
		Entity(const Entity &other);
		virtual ~Entity();



		std::shared_ptr<RenderModel> getRenderModel() const;
		std::shared_ptr<SpaceModel> getSpaceModel() const;

		void move(Math::Vec3 deltaPos);
		void rotate(Math::Vec3 deltaRot);
		void scale(Math::Vec3 deltaScale);



		Entity & operator=(const Entity&other);
	};
}
