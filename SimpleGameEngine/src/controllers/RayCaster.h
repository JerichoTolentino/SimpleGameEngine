#pragma once
#include "../display/window.h"
#include "../math/engineMath.h"
#include "../utils/MessageHandler.h"

class RayCaster
{
private:
	Window* window;
public:
	RayCaster();
	~RayCaster();

	RayCaster(Window *w);

	//returns a direction vector representing the 3D ray starting from the mouse position
	Vec3 castRay(Mat4 proj, Mat4 view);
	
};

