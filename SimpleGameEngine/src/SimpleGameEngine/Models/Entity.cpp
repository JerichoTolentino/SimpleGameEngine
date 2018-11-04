#include "Entity.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	Entity::Entity()
	{
	}

	Entity::Entity(RenderModel renderModel)
	{
		m_renderModel = renderModel;
	}

	Entity::Entity(const Entity & other)
		: Entity(other.m_renderModel)
	{
	}

	Entity::~Entity()
	{
	}



	RenderModel Entity::getRenderModel() const
	{
		return m_renderModel;
	}

	void Entity::move(Math::Vec3 deltaPos) const
	{
		Vec3 pos = m_renderModel.getSpaceModel().getPosition();
		pos += deltaPos;
		
		m_renderModel.getSpaceModel().setPosition(pos);
	}



	Entity & Entity::operator=(const Entity & other)
	{
		m_renderModel = other.m_renderModel;

		return *this;
	}
}
