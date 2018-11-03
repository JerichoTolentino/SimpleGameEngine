#include "Entity.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	GeometryModel * Entity::DEFAULT_MODEL = new GeometryModel;

	Entity::Entity()
	{
		model = DEFAULT_MODEL;
		position = Vec3(0, 0, 0);
		rotation = Vec3(0, 0, 0);
		scale = Vec3(1, 1, 1);
		boundingBox = model->getBaseBoundingBox();
	}


	Entity::~Entity()
	{
		delete model;	//TODO: might not want to delete this here... (temporary entities to reuse same model)
		delete boundingBox;
	}

	Entity::Entity(GeometryModel* m, Vec3 p, Vec3 r, Vec3 s)
	{
		this->model = m;
		this->position = p;
		this->rotation = r;
		this->scale = s;
		this->boundingBox = new BoundingBox(*(this->model->getBaseBoundingBox()));
		updateBoundingBox();
	}

	Entity::Entity(const Entity & other)
	{
		this->model = other.model;
		this->position = other.position;
		this->rotation = other.rotation;
		this->scale = other.scale;
		this->boundingBox = new BoundingBox(*(other.getBoundingBox()));
	}

	Entity & Entity::operator=(const Entity & other)
	{
		this->model = other.model;
		this->position = other.position;
		this->rotation = other.rotation;
		this->scale = other.scale;
		*(this->boundingBox) = *(other.boundingBox);
		return *this;
	}

	Mat4 Entity::generateTransformationMatrix() const
	{
		Mat4 transformations;

		transformations.setIdentity();
		transformations.transform(this->position, this->rotation, this->scale);

		return transformations;
	}

	GeometryModel* Entity::getModel() const
	{
		return this->model;
	}

	Vec3 Entity::getPosition() const
	{
		return this->position;
	}

	Vec3 Entity::getRotation() const
	{
		return this->rotation;
	}

	Vec3 Entity::getScale() const
	{
		return this->scale;
	}

	BoundingBox * Entity::getBoundingBox() const
	{
		return boundingBox;
	}

	void Entity::setModel(GeometryModel* m)
	{
		this->model = m;
	}

	void Entity::setPosition(Vec3 p)
	{
		this->position = p;
		updateBoundingBox();
	}

	void Entity::setY(float y)
	{
		position.y = y;
	}

	void Entity::setRotation(Vec3 r)
	{
		this->rotation = r;
	}

	void Entity::setRotY(float y)
	{
		rotation.y = y;
	}

	void Entity::setScale(Vec3 s)
	{
		this->scale = s;
		updateBoundingBox();
	}

	void Entity::setBoundingBox(BoundingBox * box)
	{
		boundingBox = box;
	}

	std::string Entity::toString() const
	{
		return ("--Entity--\nPosition: " + position.toString() + "\nRotation: " + rotation.toString() + "\nScale: " + scale.toString() + "\n" + model->toString() + "\n--End Entity--");
	}

	void Entity::updateBoundingBox()
	{
		//std::cout << "Before update:\n" << boundingBox->toString() << std::endl;
		//this->boundingBox->scale(this->scale);
		//this->boundingBox->translate(this->position);
		this->boundingBox->transform(this->scale, this->position);
		//std::cout << "After update:\n" << boundingBox->toString() << std::endl;
	}
}
