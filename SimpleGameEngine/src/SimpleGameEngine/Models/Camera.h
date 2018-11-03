#pragma once
#include "Entity.h"
#include "../Math/Vec3.h"
#include "../Math/Mat4.h"
#include "../Display/Window.h"

namespace SimpleGameEngine::Models
{
	class Camera
	{
	private:
		Math::Vec3 position;
		Math::Vec3 rotation;
		float groundAngle;
		float aroundAngle;
		float distanceFromEntity;
		bool lockedHorizontal;
		bool lockedVertical;
	public:
		Camera();
		~Camera();

		Camera(Math::Vec3 pos, Math::Vec3 rot);

		Math::Vec3 getPosition() const;
		Math::Vec3 getRotation() const;
		float getGroundAngle() const;
		float getAroundAngle() const;
		float getDistanceFromEntity() const;
		bool isLockedHorizontal() const;
		bool isLockedVertical() const;
		Math::Mat4 generateViewMatrix() const;
		Math::Mat4 generateSkyboxViewMatrix() const;

		void setPosition(Math::Vec3 pos);
		void setRotation(Math::Vec3 rot);
		void setGroundAngle(float angle);
		void setAroundAngle(float angle);
		void setDistanceFromEntity(float distance);
		void setLockedHorizontal(bool locked);
		void setLockedVertical(bool locked);

		// TODO: Fix this
		//void moveCamera(Display::Window &window, Terrain *terrain);
		void follow(Entity *entity);
		void zoom(float distance, float timeFactor);
		void rotateVertical(float angle, float timeFactor);
		void rotateAround(float angle, float timeFactor);

		std::string toString() const;
	};
}
