#include "RayCaster.h"


#define MAXRANGE 50

RayCaster::RayCaster()
{
}


RayCaster::~RayCaster()
{
}

RayCaster::RayCaster(Window *w)
{
	this->window = w;
}

Vec3 RayCaster::castRay(Mat4 proj, Mat4 view)
{
	double x, y, z = -1.0f, w = 0.0f;
	double px, py, pz;
	double mx, my;
	window->getMousePos(mx, my);
	std::cout << "Mouse(" << mx << "," << my << ")\n";

	//to NDC
	int width, height;
	window->getWindowSize(width, height);
	//std::cout << "WindowSize - w: " << width << " h: " << height << "\n";
	x = (2.0f * mx / width) - 1.0f;
	y = 1.0f - (2.0f * my / height);
	px = x; py = y;

	//to eye coords
	proj.inverse();
	//x = x * proj.elements[0] + y * proj.elements[4] + z * proj.elements[8] + proj.elements[12];
	//y = x * proj.elements[1] + y * proj.elements[5] + z * proj.elements[9] + proj.elements[13];
	x = px * proj.elements[0] + py * proj.elements[4] - proj.elements[8] + proj.elements[12];
	y = px * proj.elements[1] + py * proj.elements[5] - proj.elements[9] + proj.elements[13];
	px = x; py = y;

	//to world coords
	view.inverse();
	x = px * view.elements[0] + py * view.elements[4] - view.elements[8];
	y = px * view.elements[1] + py * view.elements[5] - view.elements[9];
	//z = x * view.elements[2] + y * view.elements[6] + z * view.elements[10];
	z = px * view.elements[2] + py * view.elements[6] - view.elements[10];

	//normalize
	float length = sqrt(x * x + y * y + z * z);
	x /= length;
	y /= length;
	z /= length;

	//std::cout << "Mouse: (" << mx << "," << my << ")\tVec3: (" << x << "," << y << "," << z << ")\n";

	return Vec3(x, y, z);
}