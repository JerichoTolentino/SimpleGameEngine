#include "BoundingBox.h"



BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}

BoundingBox::BoundingBox(float iminx, float iminy, float iminz, float imaxx, float imaxy, float imaxz)
{
	minx = iminx;
	miny = iminy;
	minz = iminz;
	maxx = imaxx;
	maxy = imaxy;
	maxz = imaxz;

	mx = iminx;
	my = iminy;
	mz = iminz;
	mmx = imaxx;
	mmy = imaxy;
	mmz = imaxz;
}

//TODO: This makes this base values equal to the others transformed values!!
BoundingBox::BoundingBox(const BoundingBox & other)
{
	minx = other.getMinX();
	miny = other.getMinY();
	minz = other.getMinZ();
	maxx = other.getMaxX();
	maxy = other.getMaxY();
	maxz = other.getMaxZ();

	mx = other.getMinX();
	my = other.getMinY();
	mz = other.getMinZ();
	mmx = other.getMaxX();
	mmy = other.getMaxY();
	mmz = other.getMaxZ();
}

//TODO: This makes this base values equal to the others transformed values!!
BoundingBox & BoundingBox::operator=(const BoundingBox & other)
{
	minx = other.getMinX();
	miny = other.getMinY();
	minz = other.getMinZ();
	maxx = other.getMaxX();
	maxy = other.getMaxY();
	maxz = other.getMaxZ();

	mx = other.getMinX();
	my = other.getMinY();
	mz = other.getMinZ();
	mmx = other.getMaxX();
	mmy = other.getMaxY();
	mmz = other.getMaxZ();

	return *this;
}

int BoundingBox::intersect(const Vec3 & ray, Camera * cam) const
{
	Vec3 pos = cam->getPosition();
	Vec3 rot = cam->getRotation();

	float rx = pos.x;
	float ry = pos.y;
	float rz = pos.z;

	for (int i = 0; i < 5000; i++)
	{
		rx += ray.x * 0.01f;
		ry += ray.y * 0.01f;
		rz += ray.z * 0.01f;

		if (rx > minx && rx < maxx && ry > miny && ry < maxy && rz > minz && rz < maxz)
			return i;
	}
	return -1;
}

/*
void BoundingBox::translate(const Vec3 & translate)
{
	minx = mx + translate.x;
	maxx = mmx + translate.x;

	miny = my + translate.y;
	maxy = mmy + translate.y;

	minz = mz + translate.z;
	maxz = mmz + translate.z;
}

void BoundingBox::scale(const Vec3 & scale)
{
	//minx *= scale.x;
	//maxx *= scale.x;
	//
	//miny *= scale.y;
	//maxy *= scale.y;
	//
	//minz *= scale.z;
	//maxz *= scale.z;

	std::cout << "In BB scale:\nScale(" << scale.x << "," << scale.y << "," << scale.z << ")\n";
	std::cout << "Original values:\nMin(" << mx << "," << my << "," << mz << ") Max(" << mmx << "," << mmy << "," << mmz << ")\n";

	minx = mx * scale.x;
	maxx = mmx * scale.x;

	miny = my * scale.y;
	maxy = mmy * scale.y;

	minz = mz * scale.z;
	maxz = mmz * scale.z;

	std::cout << "After scale:\nMin(" << minx << "," << miny << "," << minz << ") Max(" << maxx << "," << maxy << "," << maxz << ")" << std::endl;
}
*/

void BoundingBox::transform(const Vec3 & scale, const Vec3 & translate)
{
	minx = mx * scale.x;
	maxx = mmx * scale.x;

	miny = my * scale.y;
	maxy = mmy * scale.y;

	minz = mz * scale.z;
	maxz = mmz * scale.z;

	minx = minx + translate.x;
	maxx = maxx + translate.x;

	miny = miny + translate.y;
	maxy = maxy + translate.y;

	minz = minz + translate.z;
	maxz = maxz + translate.z;
}

GLfloat * BoundingBox::generateVertices() const
{
	//GLfloat *vertices = new GLfloat[8 * 3]
	//{
	//	-minx, -miny, -minz,	//0 - bot left	-z
	//	minx, -miny, -minz,		//1 - bot right	-z
	//	minx, miny, -minz,		//2 - top right	-z
	//	-minx, miny, -minz,		//3 - top left	-z
	//	-minx, -miny, minz,		//4 - bot left	+z
	//	minx, -miny, minz,		//5 - bot right	+z
	//	minx, miny, minz,		//6 - top right	+z
	//	-minx, miny, minz		//7 - top left	+z
	//};

	GLfloat *vertices = new GLfloat[8 * 3]
	{
		minx, miny, minz,		//0 - bot left	-z
		maxx, miny, minz,		//1 - bot right	-z
		maxx, maxy, minz,		//2 - top right	-z
		minx, maxy, minz,		//3 - top left	-z
		minx, miny, maxz,		//4 - bot left	+z
		maxx, miny, maxz,		//5 - bot right	+z
		maxx, maxy, maxz,		//6 - top right	+z
		minx, maxy, maxz		//7 - top left	+z
	};

	return vertices;
}

GLuint * BoundingBox::generateIndices() const
{
	GLuint *indices = new GLuint[24]
	{
		0,1,
		1,2,
		2,3,
		3,0,

		4,5,
		5,6,
		6,7,
		7,4,

		0,4,
		1,5,
		2,6,
		3,7,
	};

	return indices;
}

float BoundingBox::getMinX() const
{
	return minx;
}

float BoundingBox::getMinY() const
{
	return miny;
}

float BoundingBox::getMinZ() const
{
	return minz;
}

float BoundingBox::getMaxX() const
{
	return maxx;
}

float BoundingBox::getMaxY() const
{
	return maxy;
}

float BoundingBox::getMaxZ() const
{
	return maxz;
}

std::string BoundingBox::toString() const
{
	return ("--BoundingBox--\nMin(" + std::to_string(minx) + "," + std::to_string(miny) + "," + std::to_string(minz) + ") Max(" + std::to_string(maxx) + "," + std::to_string(maxy) + "," + std::to_string(maxz) + ")\n--End BoundingBox--");
}
