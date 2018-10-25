#pragma once
#include "../entities/Camera.h"
#include "../characters/Character.h"
#include "../terrains/Terrain.h"
#include "../entities/DynamicEntity.h"
#include "../display/window.h"
#include "RayCaster.h"

//FOR DEBUG
#include "../renderer/RenderEngine.h"

#include <map>

#define DEFAULT_ZOOM_SPEED 10.0f
#define DEFAULT_ROTATE_SPEED 10.0f
#define VERY_LARGE_INT 2147483647

class Controller
{
private:
	RayCaster rayCaster;
	std::map<Model*, std::vector<Entity*>*> *entities;
	Character *character;
	Camera *camera;
	float zoomSpeed;
	float rotateSpeedHorizontal;
	float rotateSpeedVertical;
public:
	Controller();
	~Controller();

	Controller(Character *ch, Camera *cam, Window *window, std::map<Model*, std::vector<Entity*>*> *e);
	Controller(Character *ch, Camera *cam, Window *window, std::map<Model*, std::vector<Entity*>*> *e, float zoom, float horizontalSpeed, float verticalSpeed);

	float getZoomSpeed() const;
	float getRotateSpeedHorizontal() const;
	float getRotateSpeedVertical() const;

	void setZoomSpeed(float speed);
	void setRotateSpeedHorizontal(float speed);
	void setRotateSpeedVertical(float speed);

	void readInput(Window &window, Terrain *terrain, Mat4 proj, Camera *camera);
};

