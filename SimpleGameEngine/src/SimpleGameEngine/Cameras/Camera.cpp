#include "sgepch.h"
#include "Camera.h"

#define MOVESPEED 10.0f
#define ROTSPEED 40.0f
#define DEFAULT_GROUND_ANGLE 30.0f
#define DEFAULT_DISTANCE 5.0f
#define DEFAULT_AROUND_ANGLE 0.0f

using namespace SimpleGameEngine::Display;
using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Cameras
{
	Camera::Camera()
	{
		position = Vec3(0, 0, 0);
		rotation = Vec3(0, 0, 0);
		groundAngle = DEFAULT_GROUND_ANGLE;
		aroundAngle = DEFAULT_AROUND_ANGLE;
		distanceFromEntity = DEFAULT_DISTANCE;
	}

	Camera::Camera(Vec3 pos, Vec3 rot)
	{
		position = pos;
		rotation = rot;
		groundAngle = DEFAULT_GROUND_ANGLE;
		aroundAngle = DEFAULT_AROUND_ANGLE;
		distanceFromEntity = DEFAULT_DISTANCE;
	}

	Camera::Camera(const Camera & other)
		: Camera(other.position, other.rotation)
	{
	}

	Camera::~Camera()
	{
	}



	Vec3 Camera::getPosition() const
	{
		return position;
	}

	Vec3 Camera::getRotation() const
	{
		return rotation;
	}

	float Camera::getGroundAngle() const
	{
		return groundAngle;
	}

	float Camera::getAroundAngle() const
	{
		return aroundAngle;
	}

	float Camera::getDistanceFromEntity() const
	{
		return distanceFromEntity;
	}

	bool Camera::isLockedHorizontal() const
	{
		return lockedHorizontal;
	}

	bool Camera::isLockedVertical() const
	{
		return lockedVertical;
	}

	Mat4 Camera::generateViewMatrix() const
	{
		return Mat4::GenerateViewMatrix(position, rotation);
	}

	Mat4 Camera::generateSkyboxViewMatrix() const
	{
		Mat4 view = Mat4::GenerateViewMatrix(position, rotation);

		// Remove the translation part of the matrix (only want to rotate the skybox)
		view.elements[12] = 0;
		view.elements[13] = 0;
		view.elements[14] = 0;
		
		return view;
	}

	void Camera::setPosition(Vec3 pos)
	{
		position = pos;
	}

	void Camera::setRotation(Vec3 rot)
	{
		rotation = rot;
	}

	void Camera::setGroundAngle(float angle)
	{
		groundAngle = angle;
	}

	void Camera::setAroundAngle(float angle)
	{
		aroundAngle = angle;
	}

	void Camera::setDistanceFromEntity(float distance)
	{
		distanceFromEntity = distance;
	}

	void Camera::setLockedHorizontal(bool locked)
	{
		lockedHorizontal = locked;
	}

	void Camera::setLockedVertical(bool locked)
	{
		lockedVertical = locked;
	}

	void Camera::moveCamera(Window window)
	{
		double mx, my;
		float timeFactor = window.getTimeFactor();
		window.getDeltaMousePos(mx, my);

		rotation += Vec3(ROTSPEED * my * timeFactor, ROTSPEED * mx * timeFactor, 0);

		if (window.isKeyDown(GLFW_KEY_PAGE_UP))
		{
			position += Vec3(0, MOVESPEED * timeFactor, 0);
		}
		if (window.isKeyDown(GLFW_KEY_PAGE_DOWN))
		{
			position -= Vec3(0, MOVESPEED * timeFactor, 0);
		}
		if (window.isKeyDown(GLFW_KEY_D))
		{
			float zFactor = cos(MathUtils::ToRadians(rotation.y));
			float xFactor = sin(MathUtils::ToRadians(rotation.y));
			position += Vec3(zFactor * MOVESPEED * timeFactor, 0, xFactor * MOVESPEED * timeFactor);
		}
		if (window.isKeyDown(GLFW_KEY_A))
		{
			float zFactor = cos(MathUtils::ToRadians(rotation.y));
			float xFactor = sin(MathUtils::ToRadians(rotation.y));
			position -= Vec3(zFactor * MOVESPEED * timeFactor, 0, xFactor * MOVESPEED * timeFactor);
		}
		if (window.isKeyDown(GLFW_KEY_W))
		{
			float zFactor = cos(MathUtils::ToRadians(rotation.y));
			float xFactor = -sin(MathUtils::ToRadians(rotation.y));
			position -= Vec3(MOVESPEED * xFactor * timeFactor, 0, MOVESPEED * zFactor * timeFactor);
		}
		if (window.isKeyDown(GLFW_KEY_S))
		{
			float zFactor = cos(MathUtils::ToRadians(rotation.y));
			float xFactor = -sin(MathUtils::ToRadians(rotation.y));
			position += Vec3(MOVESPEED * xFactor * timeFactor, 0, MOVESPEED * zFactor * timeFactor);
		}
	}

	void Camera::follow(SpaceModel spaceModel)
	{
		position = spaceModel.getPosition();
		rotation.x = spaceModel.getRotation().x + groundAngle;
		rotation.y = aroundAngle;

		float theta = MathUtils::ToRadians(groundAngle);
		float zFactor = cos(MathUtils::ToRadians(rotation.y));
		float xFactor = -sin(MathUtils::ToRadians(rotation.y));
		
		position.x += cos(theta) * distanceFromEntity * xFactor;
		position.z += cos(theta) * distanceFromEntity * zFactor;
		position.y += sin(theta) * distanceFromEntity;
	}

	void Camera::zoom(float distance, float timeFactor)
	{
		distanceFromEntity += distance * timeFactor;
	}

	void Camera::rotateVertical(float angle, float timeFactor)
	{
		groundAngle += angle * timeFactor;
	}

	void Camera::rotateAround(float angle, float timeFactor)
	{
		aroundAngle += angle * timeFactor;
	}

	Camera & Camera::operator=(const Camera & other)
	{
		this->position = other.position;
		this->rotation = other.rotation;
		this->groundAngle = other.groundAngle;
		this->aroundAngle = other.aroundAngle;
		this->distanceFromEntity = other.distanceFromEntity;
		this->lockedHorizontal = other.lockedHorizontal;
		this->lockedVertical = other.lockedVertical;

		return *this;
	}
}
