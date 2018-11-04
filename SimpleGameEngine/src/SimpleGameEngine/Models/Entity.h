#pragma once
#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	class Entity
	{
	private:
		RenderModel m_renderModel;
		


	public:
		Entity();
		Entity(RenderModel renderModel);
		Entity(const Entity &other);
		virtual ~Entity();



		RenderModel getRenderModel() const;

		void move(Math::Vec3 deltaPos) const;
		void rotate(Math::Vec3 deltaRot) const;
		void scale(Math::Vec3 deltaScale) const;



		Entity& operator=(const Entity&other);
	};
}
