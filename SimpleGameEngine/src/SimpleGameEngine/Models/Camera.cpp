#include "Camera.h"

#define MOVESPEED 10.0f
#define ROTSPEED 40.0f
#define DEFAULT_GROUND_ANGLE 30.0f
#define DEFAULT_DISTANCE 5.0f
#define DEFAULT_AROUND_ANGLE 0.0f
//#define DEFAULT_GROUND_ANGLE 0.0f
//#define DEFAULT_DISTANCE 0.0f
//#define DEFAULT_AROUND_ANGLE 0.0f

Camera::Camera()
{
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	groundAngle = DEFAULT_GROUND_ANGLE;
	aroundAngle = DEFAULT_AROUND_ANGLE;
	distanceFromEntity = DEFAULT_DISTANCE;
}


Camera::~Camera()
{
}

Camera::Camera(Vec3 pos, Vec3 rot)
{
	position = pos;
	rotation = rot;
	groundAngle = DEFAULT_GROUND_ANGLE;
	aroundAngle = DEFAULT_AROUND_ANGLE;
	distanceFromEntity = DEFAULT_DISTANCE;
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
	return Mat4::generateViewMatrix(position, rotation);
}

Mat4 Camera::generateSkyboxViewMatrix() const
{
	Mat4 view = Mat4::generateViewMatrix(position, rotation);
	//remove the translation part of the matrix (only want to rotate the skybox)
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

void Camera::moveCamera(Window & window, Terrain *terrain)
{
	double mx, my;// , x, y;
	float timeFactor = window.getTimeFactor();
	//window.getMousePos(x, y);
	window.getDeltaMousePos(mx, my);
	//std::cout << "Delta Mouse: (" << mx << "," << my << ") Mouse: (" << x << "," << y << ")\n";

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
		float zFactor = cos(MathUtils::toRadians(rotation.y));
		float xFactor = sin(MathUtils::toRadians(rotation.y));
		position += Vec3(zFactor * MOVESPEED * timeFactor, 0, xFactor * MOVESPEED * timeFactor);
	}
	if (window.isKeyDown(GLFW_KEY_A))
	{
		float zFactor = cos(MathUtils::toRadians(rotation.y));
		float xFactor = sin(MathUtils::toRadians(rotation.y));
		position -= Vec3(zFactor * MOVESPEED * timeFactor, 0, xFactor * MOVESPEED * timeFactor);
	}
	if (window.isKeyDown(GLFW_KEY_W))
	{
		float zFactor = cos(MathUtils::toRadians(rotation.y));
		float xFactor = -sin(MathUtils::toRadians(rotation.y));
		position -= Vec3(MOVESPEED * xFactor * timeFactor, 0, MOVESPEED * zFactor * timeFactor);
	}
	if (window.isKeyDown(GLFW_KEY_S))
	{
		float zFactor = cos(MathUtils::toRadians(rotation.y));
		float xFactor = -sin(MathUtils::toRadians(rotation.y));
		position += Vec3(MOVESPEED * xFactor * timeFactor, 0, MOVESPEED * zFactor * timeFactor);
	}

	position.y = terrain->getHeight(position);
	//Vec3 posRelToTerrain = position - terrain->getPosition();
	//position.y = terrain->getHeightMap()->getHeight(posRelToTerrain.x, posRelToTerrain.z);
}

void Camera::follow(Entity * entity)
{
	position = entity->getPosition();
	//rotation = entity->getRotation();
	//rotation = Vec3(-rotation.x, -rotation.y, -rotation.z);
	//rotation.x += groundAngle;
	//rotation.y += aroundAngle;
	rotation.x = entity->getRotation().x + groundAngle;
	rotation.y = aroundAngle;
	float theta = MathUtils::toRadians(groundAngle);
	float zFactor = cos(MathUtils::toRadians(rotation.y));
	float xFactor = -sin(MathUtils::toRadians(rotation.y));
	position.x += cos(theta) * distanceFromEntity * xFactor;
	position.z += cos(theta) * distanceFromEntity * zFactor;
	position.y += sin(theta) * distanceFromEntity;
	//position.z += 5;	//cos(theta) = adj/hyp --> adj = cos(theta) * hyp
	//position.y += 2;	//sin(theta) = opp/hyp --> opp = sin(theta) * hyp
}

void Camera::zoom(float distance, float timeFactor)
{
	distanceFromEntity += distance * timeFactor;
}

void Camera::rotateVertical(float angle, float timeFactor)
{
	groundAngle += angle * timeFactor;
	//std::cout << "rotation.y: " << std::to_string(rotation.y) << std::endl;
}

void Camera::rotateAround(float angle, float timeFactor)
{
	aroundAngle += angle * timeFactor;
}

std::string Camera::toString() const
{
	return ("--Camera--\nPosition: " + position.toString() + "\nRotation: " + rotation.toString() + "\n--End Camera--");
}
