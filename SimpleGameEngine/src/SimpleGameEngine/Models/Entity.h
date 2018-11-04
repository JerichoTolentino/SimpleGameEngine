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



		Entity& operator=(const Entity&other);
	};
}
