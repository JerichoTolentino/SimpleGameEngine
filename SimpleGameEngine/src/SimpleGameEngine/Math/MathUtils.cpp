#include "sgepch.h"
#include "MathUtils.h"

namespace SimpleGameEngine::Math
{
	const float MathUtils::PI = 3.14159265358979323846;

	float MathUtils::ToRadians(float degrees)
	{
		return (float)(degrees * PI / 180);
	}

	float MathUtils::ToDegrees(float radians)
	{
		return (float) (radians * 180 / PI);
	}

	float MathUtils::CalculateBaryCentricCoordinates(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, const Vec2 &pos)
	{
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
}
