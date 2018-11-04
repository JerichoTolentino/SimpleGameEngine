#include "Entity.h"
#include "../Logic/ModelTransformer.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Logic;

namespace SimpleGameEngine::Models
{
	Entity::Entity()
	{
	}

	Entity::Entity(RenderModel renderModel, SpaceModel spaceModel)
	{
		m_renderModel = renderModel;
		m_spaceModel = spaceModel;
	}

	Entity::Entity(const Entity & other)
		: Entity(other.m_renderModel, other.m_spaceModel)
	{
	}

	Entity::~Entity()
	{
	}



	RenderModel Entity::getRenderModel() const
	{
		return m_renderModel;
	}

	SpaceModel Entity::getSpaceModel() const
	{
		return m_spaceModel;
	}

	void Entity::move(Math::Vec3 deltaPos)
	{
		ModelTransformer::translate(m_spaceModel, deltaPos);
	}

	void Entity::rotate(Math::Vec3 deltaRot)
	{
		ModelTransformer::rotate(m_spaceModel, deltaRot);
	}

	void Entity::scale(Math::Vec3 deltaScale)
	{
		ModelTransformer::scale(m_spaceModel, deltaScale);
	}



	Entity & Entity::operator=(const Entity & other)
	{
		m_renderModel = other.m_renderModel;
		m_spaceModel = other.m_spaceModel;

		return *this;
	}
}
