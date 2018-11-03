#pragma once
#include "Entity.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Models
{
	class DynamicEntity : public Entity
	{
	private:
		float moveSpeed;
		float turnSpeed;
	public:
		DynamicEntity();
		virtual ~DynamicEntity();

		DynamicEntity(GeometryModel* m, Math::Vec3 p, Math::Vec3 r, Math::Vec3 s);
		DynamicEntity(GeometryModel* m, Math::Vec3 p, Math::Vec3 r, Math::Vec3 s, float moveSpeed, float turnSpeed);

		DynamicEntity(const DynamicEntity &other);
		DynamicEntity& operator=(const DynamicEntity&other);

		virtual void moveLeft(float timeFactor);
		virtual void moveRight(float timeFactor);
		virtual void moveForward(float timeFactor);
		virtual void moveBackward(float timeFactor);
		virtual void moveUp(float timeFactor);
		virtual void moveDown(float timeFactor);

		virtual void turnLeft(float timeFactor);
		virtual void turnRight(float timeFactor);
		virtual void turnUp(float timeFactor);		//TODO: Fix this!
		virtual void turnDown(float timeFactor);	//TODO: Fix this!
	};


}
