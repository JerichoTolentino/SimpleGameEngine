#pragma once
#include "Model.h"
#include "../Math/Mat4.h"

namespace SimpleGameEngine::Models
{
	class Entity
	{
	private:
		static Model* DEFAULT_MODEL;	//TODO: Make this a cube or something..
		Model* model;
		Math::Vec3 position;
		Math::Vec3 rotation;
		Math::Vec3 scale;
		BoundingBox *boundingBox;
		//TODO: BoundingShape boundingShape;
	public:
		Entity();
		virtual ~Entity();

		Entity(Model* m, Math::Vec3 p, Math::Vec3 r, Math::Vec3 s);

		Entity(const Entity &other);
		Entity& operator=(const Entity&other);

		virtual Math::Mat4 generateTransformationMatrix() const;

		virtual Model* getModel() const;
		virtual Math::Vec3 getPosition() const;
		virtual Math::Vec3 getRotation() const;
		virtual Math::Vec3 getScale() const;
		virtual BoundingBox* getBoundingBox() const;
		//TODO: virtual BoundingShape* getBoundingShape() const;

		virtual void setModel(Model* m);
		virtual void setPosition(Math::Vec3 p);
		virtual void setY(float y);
		virtual void setRotation(Math::Vec3 r);
		virtual void setRotY(float y);
		virtual void setScale(Math::Vec3 s);
		virtual void setBoundingBox(BoundingBox* box);
		//TODO: virtual void setBoundingShape(BoundingShape* bs);

		virtual std::string toString() const;

	private:
		virtual void updateBoundingBox();
	};
}
