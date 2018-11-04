#pragma once
#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	class Entity
	{
	private:
		RenderModel m_renderModel;
		SpaceModel m_spaceModel;
		


	public:
		Entity();
		Entity(RenderModel renderModel, SpaceModel spaceModel);
		Entity(const Entity &other);
		virtual ~Entity();



		RenderModel getRenderModel() const;
		SpaceModel getSpaceModel() const;

		void move(Math::Vec3 deltaPos);
		void rotate(Math::Vec3 deltaRot);
		void scale(Math::Vec3 deltaScale);



		Entity& operator=(const Entity&other);
	};
}
