#pragma once
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class SpaceModel
	{
	private:
		Math::Vec3 m_position;
		Math::Vec3 m_rotation;
		Math::Vec3 m_scale;



	public:
		SpaceModel();
		SpaceModel(Math::Vec3 pos, Math::Vec3 rot, Math::Vec3 scale);
		SpaceModel(const SpaceModel & other);
		virtual ~SpaceModel();



		virtual Math::Vec3 getPosition() const;
		virtual Math::Vec3 getRotation() const;
		virtual Math::Vec3 getScale() const;
		virtual void setPosition(Math::Vec3 position);
		virtual void setRotation(Math::Vec3 rotation);
		virtual void setScale(Math::Vec3 scale);



		virtual SpaceModel & operator=(const SpaceModel & other);
	};
}
