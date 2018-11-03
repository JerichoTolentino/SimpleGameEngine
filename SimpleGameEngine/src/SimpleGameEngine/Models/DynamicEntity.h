#pragma once
#include "Entity.h"

class DynamicEntity : public Entity
{
private:
	float moveSpeed;
	float turnSpeed;
public:
	DynamicEntity();
	virtual ~DynamicEntity();

	DynamicEntity(Model* m, Vec3 p, Vec3 r, Vec3 s);
	DynamicEntity(Model* m, Vec3 p, Vec3 r, Vec3 s, float moveSpeed, float turnSpeed);

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

