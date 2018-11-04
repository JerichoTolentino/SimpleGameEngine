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

	void Entity::rotate(Math::Vec3 deltaRot) const
	{
		Vec3 rot = m_renderModel.getSpaceModel().getRotation();
		rot += deltaRot;

		m_renderModel.getSpaceModel().setRotation(rot);
	}

	void Entity::scale(Math::Vec3 deltaScale) const
	{
		Vec3 scale = m_renderModel.getSpaceModel().getScale();
		scale += deltaScale;

		m_renderModel.getSpaceModel().setScale(scale);
	}



	Entity & Entity::operator=(const Entity & other)
	{
		m_renderModel = other.m_renderModel;

		return *this;
	}
}
