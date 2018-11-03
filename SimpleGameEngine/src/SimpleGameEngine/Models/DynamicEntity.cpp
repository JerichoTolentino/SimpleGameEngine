#include "DynamicEntity.h"
#define DEFAULT_MOVE_SPEED 0.04f
#define DEFAULT_TURN_SPEED 0.08f

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	DynamicEntity::DynamicEntity()
		: Entity()
	{
		this->moveSpeed = DEFAULT_MOVE_SPEED;
		this->turnSpeed = DEFAULT_TURN_SPEED;
	}


	DynamicEntity::~DynamicEntity()
	{
	}


	DynamicEntity::DynamicEntity(GeometryModel * m, Vec3 p, Vec3 r, Vec3 s)
		: Entity(m, p, r, s)
	{
		this->moveSpeed = DEFAULT_MOVE_SPEED;
		this->turnSpeed = DEFAULT_TURN_SPEED;
	}

	DynamicEntity::DynamicEntity(GeometryModel * m, Vec3 p, Vec3 r, Vec3 s, float moveSpeed, float turnSpeed)
		: Entity(m, p, r, s)
	{
		this->moveSpeed = moveSpeed;
		this->turnSpeed = turnSpeed;
	}

	DynamicEntity::DynamicEntity(const DynamicEntity & other)
		: Entity(other.getModel(), other.getPosition(), other.getRotation(), other.getScale())
	{
		this->moveSpeed = other.moveSpeed;
		this->turnSpeed = other.turnSpeed;
	}

	DynamicEntity & DynamicEntity::operator=(const DynamicEntity & other)
	{
		Entity::setModel(other.getModel());
		Entity::setPosition(other.getPosition());
		Entity::setRotation(other.getRotation());
		Entity::setScale(other.getScale());
		this->moveSpeed = other.moveSpeed;
		this->turnSpeed = other.turnSpeed;
		return *this;
	}

	void DynamicEntity::moveLeft(float timeFactor)
	{
		//Entity::setPosition(Entity::getPosition() -= Vec3(moveSpeed, 0, 0));
		float zFactor = cos(MathUtils::toRadians((Entity::getRotation().y)));
		float xFactor = sin(MathUtils::toRadians((Entity::getRotation().y)));
		Entity::setPosition(Entity::getPosition() - Vec3(zFactor * moveSpeed * timeFactor, 0, xFactor * moveSpeed * timeFactor));
	}

	void DynamicEntity::moveRight(float timeFactor)
	{
		//Entity::setPosition(Entity::getPosition() += Vec3(moveSpeed, 0, 0));
		float zFactor = cos(MathUtils::toRadians(Entity::getRotation().y));
		float xFactor = sin(MathUtils::toRadians(Entity::getRotation().y));
		Entity::setPosition(Entity::getPosition() + Vec3(zFactor * moveSpeed * timeFactor, 0, xFactor * moveSpeed * timeFactor));
	}

	void DynamicEntity::moveForward(float timeFactor)
	{
		//Entity::setPosition(Entity::getPosition() -= Vec3(0, 0, moveSpeed));
		float zFactor = cos(MathUtils::toRadians(Entity::getRotation().y));
		float xFactor = sin(MathUtils::toRadians(Entity::getRotation().y));
		Entity::setPosition(Entity::getPosition() - Vec3(moveSpeed * xFactor * timeFactor, 0, moveSpeed * zFactor * timeFactor));
	}

	void DynamicEntity::moveBackward(float timeFactor)
	{
		//Entity::setPosition(Entity::getPosition() += Vec3(0, 0, moveSpeed));
		float zFactor = cos(MathUtils::toRadians(Entity::getRotation().y));
		float xFactor = sin(MathUtils::toRadians(Entity::getRotation().y));
		Entity::setPosition(Entity::getPosition() + Vec3(moveSpeed * xFactor * timeFactor, 0, moveSpeed * zFactor * timeFactor));
	}

	void DynamicEntity::moveUp(float timeFactor)
	{
		Entity::setPosition(Entity::getPosition() += Vec3(0, moveSpeed * timeFactor, 0));
	}

	void DynamicEntity::moveDown(float timeFactor)
	{
		Entity::setPosition(Entity::getPosition() -= Vec3(0, moveSpeed * timeFactor, 0));
	}

	void DynamicEntity::turnLeft(float timeFactor)
	{
		Entity::setRotation(Entity::getRotation() -= Vec3(0, turnSpeed * timeFactor, 0));
	}

	void DynamicEntity::turnRight(float timeFactor)
	{
		Entity::setRotation(Entity::getRotation() += Vec3(0, turnSpeed * timeFactor, 0));
	}

	void DynamicEntity::turnUp(float timeFactor)
	{
		Entity::setRotation(Entity::getRotation() += Vec3(turnSpeed * timeFactor, 0, 0));
	}

	void DynamicEntity::turnDown(float timeFactor)
	{
		Entity::setRotation(Entity::getRotation() -= Vec3(turnSpeed * timeFactor, 0, 0));
	}
}
