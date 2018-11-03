#pragma once

namespace SimpleGameEngine::Models
{
	class Entity
	{
	private:
		GeometryModel* model;
		BoundingBox *boundingBox;
		


	public:
		Entity();
		Entity(const Entity &other);
		virtual ~Entity();		



		virtual GeometryModel* getModel() const;
		virtual BoundingBox* getBoundingBox() const;
		virtual void setModel(GeometryModel* m);
		virtual void setBoundingBox(BoundingBox* box);



		Entity& operator=(const Entity&other);
	};
}
