#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include "../math/engineMath.h"
#include "../display/window.h"
#include "../terrains/Terrain.h"
#include "Entity.h"

class Camera
{
private:
	Vec3 position;
	Vec3 rotation;
	float groundAngle;
	float aroundAngle;
	float distanceFromEntity;
	bool lockedHorizontal;
	bool lockedVertical;
public:
	Camera();
	~Camera();

	Camera(Vec3 pos, Vec3 rot);

	Vec3 getPosition() const;
	Vec3 getRotation() const;
	float getGroundAngle() const;
	float getAroundAngle() const;
	float getDistanceFromEntity() const;
	bool isLockedHorizontal() const;
	bool isLockedVertical() const;
	Mat4 generateViewMatrix() const;
	Mat4 generateSkyboxViewMatrix() const;

	void setPosition(Vec3 pos);
	void setRotation(Vec3 rot);
	void setGroundAngle(float angle);
	void setAroundAngle(float angle);
	void setDistanceFromEntity(float distance);
	void setLockedHorizontal(bool locked);
	void setLockedVertical(bool locked);

	void moveCamera(Window &window, Terrain *terrain);
	void follow(Entity *entity);
	void zoom(float distance, float timeFactor);
	void rotateVertical(float angle, float timeFactor);
	void rotateAround(float angle, float timeFactor);

	std::string toString() const;
};

#endif