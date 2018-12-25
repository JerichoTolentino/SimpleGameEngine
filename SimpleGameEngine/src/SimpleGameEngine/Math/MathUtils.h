#pragma once
#include <math.h>

#include "Vec2.h"
#include "Vec3.h"

namespace SimpleGameEngine::Math
{
	class MathUtils
	{
	public:
		static const float PI;



		/// <summary>
		/// Converts from degrees to radians.
		/// </summary>
		/// <param name="degrees">The degrees to convert from.</param>
		/// <returns></returns>
		static float ToRadians(float degrees);

		/// <summary>
		/// Converts from radians to degrees.
		/// </summary>
		/// <param name="radians">The radians to convert from.</param>
		/// <returns></returns>
		static float ToDegrees(float radians);

		/// <summary>
		/// Gets the barycentric coordinates of the specified position.
		/// </summary>
		/// <param name="p1">An edge of the triangle.</param>
		/// <param name="p2">An edge of the triangle.</param>
		/// <param name="p3">An edge of the triangle.</param>
		/// <param name="pos">The position vector relative to the triangle.</param>
		/// <returns></returns>
		static float CalculateBaryCentricCoordinates(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, const Vec2 &pos);
	};
}
