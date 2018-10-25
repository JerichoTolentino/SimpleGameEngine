#include "Controller.h"
#include "../entities/BoundingBox.h"


Controller::Controller()
{
	character = nullptr;
	camera = nullptr;
	entities = nullptr;
	zoomSpeed = DEFAULT_ZOOM_SPEED;
	rotateSpeedHorizontal = DEFAULT_ROTATE_SPEED;
	rotateSpeedVertical = DEFAULT_ROTATE_SPEED;
	MessageHandler::printMessage("WARNING: Default Controller constructor called!\n");
}


Controller::~Controller()
{
}

Controller::Controller(Character *ch, Camera *cam, Window *window, std::map<Model*, std::vector<Entity*>*> *e)
{
	rayCaster = RayCaster(window);
	character = ch;
	camera = cam;
	entities = e;
	zoomSpeed = DEFAULT_ZOOM_SPEED;
	rotateSpeedHorizontal = DEFAULT_ROTATE_SPEED;
	rotateSpeedVertical = DEFAULT_ROTATE_SPEED;
}

Controller::Controller(Character *ch, Camera *cam, Window *window, std::map<Model*, std::vector<Entity*>*> *e, float zoom, float horizontalSpeed, float verticalSpeed)
{
	rayCaster = RayCaster(window);
	character = ch;
	camera = cam;
	entities = e;
	zoomSpeed = zoom;
	rotateSpeedHorizontal = horizontalSpeed;
	rotateSpeedVertical = verticalSpeed;
}

float Controller::getZoomSpeed() const
{
	return zoomSpeed;
}

float Controller::getRotateSpeedHorizontal() const
{
	return rotateSpeedHorizontal;
}

float Controller::getRotateSpeedVertical() const
{
	return rotateSpeedVertical;
}

void Controller::setZoomSpeed(float speed)
{
	zoomSpeed = speed;
}

void Controller::setRotateSpeedHorizontal(float speed)
{
	rotateSpeedHorizontal = speed;
}

void Controller::setRotateSpeedVertical(float speed)
{
	rotateSpeedVertical = speed;
}

void Controller::readInput(Window &window, Terrain *terrain, Mat4 proj, Camera *camera)
{
	DynamicEntity *entity = character->getEntity();
	float timeFactor = window.getTimeFactor();
	double mx, my;
	window.getDeltaMousePos(mx, my);

	//--CAMERA PLACEMENT--//

	if (window.isKeyDown(GLFW_KEY_PAGE_UP))
		entity->moveUp(timeFactor / 4);
		//camera->zoom(-zoomSpeed, timeFactor);
	if (window.isKeyDown(GLFW_KEY_PAGE_DOWN))
		entity->moveDown(timeFactor / 4);
		//camera->zoom(zoomSpeed, timeFactor);

	camera->setLockedHorizontal(window.isMouseButtonDown(1));
	camera->setLockedVertical(window.isMouseButtonDown(0));

	if (!camera->isLockedHorizontal())
		camera->rotateAround(mx * rotateSpeedHorizontal, timeFactor);

	if(!camera->isLockedVertical())
		camera->rotateVertical(my * rotateSpeedVertical, timeFactor);

	//--END CAMERA PLACEMENT--//

	//--CHARACTER MOVEMENT--//

	if (window.isKeyDown(GLFW_KEY_W) && window.isKeyDown(GLFW_KEY_A))
	{
		entity->setRotY(-camera->getRotation().y + 45.0f);
		entity->moveForward(timeFactor);
	}
	else if (window.isKeyDown(GLFW_KEY_W) && window.isKeyDown(GLFW_KEY_D))
	{
		entity->setRotY(-camera->getRotation().y - 45.0f);
		entity->moveForward(timeFactor);
	}
	else if (window.isKeyDown(GLFW_KEY_S) && window.isKeyDown(GLFW_KEY_A))
	{
		entity->setRotY(-camera->getRotation().y + 135.0f);
		entity->moveForward(timeFactor);
	}
	else if (window.isKeyDown(GLFW_KEY_S) && window.isKeyDown(GLFW_KEY_D))
	{
		entity->setRotY(-camera->getRotation().y - 135.0f);
		entity->moveForward(timeFactor);
	}
	else
	{
		if (window.isKeyDown(GLFW_KEY_W))
		{
			entity->setRotY(-camera->getRotation().y);
			entity->moveForward(timeFactor);
		}
		if (window.isKeyDown(GLFW_KEY_S))
		{
			entity->setRotY(-camera->getRotation().y - 180.0f);
			entity->moveForward(timeFactor);
			//entity->moveBackward(timeFactor);
		}
		if (window.isKeyDown(GLFW_KEY_A))
		{
			entity->setRotY(-camera->getRotation().y + 90.0f);
			entity->moveForward(timeFactor);
			//entity->turnRight(timeFactor);
		}
		if (window.isKeyDown(GLFW_KEY_D))
		{
			entity->setRotY(-camera->getRotation().y - 90.0f);
			entity->moveForward(timeFactor);
			//entity->turnLeft(timeFactor);
		}
	}

	entity->setY(terrain->getHeight(entity->getPosition()));

	//--END CHARACTER MOVEMENT--//

	//Camera should follow the character
	camera->follow(character->getEntity());



	//--RAY CASTING--//

	if (window.isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		//Need to be able to check which object hit first (use distance! ie t value in for loop)
		Vec3 ray = rayCaster.castRay(proj, camera->generateViewMatrix());
		RenderEngine::drawRay(ray, camera->getPosition(), true);
		//MessageHandler::printMessage(camera->getPosition().toString());
		//std::cout << "Ray: " << ray.toString() << std::endl;
		std::vector<Entity*> *vecEntities;
		Entity *entityHit = nullptr, *currEntity = nullptr;
		int numRayIterations = VERY_LARGE_INT;

		std::map<Model*, std::vector<Entity*>*>::iterator iter;
		for (iter = entities->begin(); iter != entities->end(); iter++)
		{
			vecEntities = iter->second;
			for (int i = 0; i < vecEntities->size(); i++)
			{
				currEntity = vecEntities->at(i);
				int numIters = currEntity->getBoundingBox()->intersect(ray, camera);
				if (numIters > 0 && numIters < numRayIterations)
				{
					numRayIterations = numIters;
					entityHit = currEntity;
				}
			}
		}

		static int hitCount = 0;

		if (entityHit != nullptr)
		{
			hitCount++;
			MessageHandler::printMessage("HIT #" + std::to_string(hitCount) + " at (" + ray.multiply(numRayIterations).toString() +  "!\n");
		}
		//else
		//	std::cout << "Not hit!\n";
		//std::cout << "Camera Y: " << camera->getPosition().y << " Ray: " << ray.toString() << "\n";

		/*
		float precision = 0.1f;
		int distance = 100;
		Vec3 dir, ray;
		dir = rayCaster.castRay(proj, camera->generateViewMatrix());
		dir.multiply(precision);

		for (int i = 0; i < distance; i ++)
		{
		//std::cout << ray.toString() << std::endl;
		ray += dir;
		}
		*/
	}

	//--END RAY CASTING--//
}
