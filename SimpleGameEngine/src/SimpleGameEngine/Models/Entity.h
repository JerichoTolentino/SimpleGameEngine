#pragma once
#include "Model.h"
#include "../math/engineMath.h"

class BoundingBox;

class Entity
{
private:
	static Model* DEFAULT_MODEL;	//TODO: Make this a cube or something..
	Model* model;
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
	BoundingBox *boundingBox;
	//TODO: BoundingShape boundingShape;
public:
	Entity();
	virtual ~Entity();

	Entity(Model* m, Vec3 p, Vec3 r, Vec3 s);

	Entity(const Entity &other);
	Entity& operator=(const Entity&other);

	virtual Mat4 generateTransformationMatrix() const;

	virtual Model* getModel() const;
	virtual Vec3 getPosition() const;
	virtual Vec3 getRotation() const;
	virtual Vec3 getScale() const;
	virtual BoundingBox* getBoundingBox() const;
	//TODO: virtual BoundingShape* getBoundingShape() const;

	virtual void setModel(Model* m);
	virtual void setPosition(Vec3 p);
	virtual void setY(float y);
	virtual void setRotation(Vec3 r);
	virtual void setRotY(float y);
	virtual void setScale(Vec3 s);
	virtual void setBoundingBox(BoundingBox* box);
	//TODO: virtual void setBoundingShape(BoundingShape* bs);

	virtual std::string toString() const;

private:
	virtual void updateBoundingBox();
};

