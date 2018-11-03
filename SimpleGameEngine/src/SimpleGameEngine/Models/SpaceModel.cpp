#include "SpaceModel.h"

namespace SimpleGameEngine::Models
{
	SpaceModel::SpaceModel()
	{
	}

	SpaceModel::SpaceModel(Math::Vec3 pos, Math::Vec3 rot, Math::Vec3 scale)
	{
		m_position = pos;
		m_rotation = rot;
		m_scale = scale;
	}

	SpaceModel::SpaceModel(const SpaceModel & other)
		: SpaceModel(other.m_position, other.m_rotation, other.m_scale)
	{
	}

	SpaceModel::~SpaceModel()
	{
	}



	Math::Vec3 SpaceModel::getPosition() const
	{
		return m_position;
	}

	Math::Vec3 SpaceModel::getRotation() const
	{
		return m_rotation;
	}

	Math::Vec3 SpaceModel::getScale() const
	{
		return m_scale;
	}

	void SpaceModel::setPosition(Math::Vec3 position)
	{
		m_position = position;
	}

	void SpaceModel::setRotation(Math::Vec3 rotation)
	{
		m_rotation = rotation;
	}

	void SpaceModel::setScale(Math::Vec3 scale)
	{
		m_scale = scale;
	}



	SpaceModel & SpaceModel::operator=(const SpaceModel & other)
	{
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale = other.m_scale;

		return *this;
	}
}
