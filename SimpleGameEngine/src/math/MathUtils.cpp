#include "MathUtils.h"



MathUtils::MathUtils()
{
}


MathUtils::~MathUtils()
{
}

float MathUtils::toRadians(float degrees)
{
	return (degrees * PI / 180);
}

// FROM THINMATRIX!! //
float MathUtils::barryCentric(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, const Vec2 &pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
