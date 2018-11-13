#pragma once
#include "../Models/BoundingBox.h"

namespace SimpleGameEngine::Logic
{
	class IntersectionTester
	{
	public:
		/// <summary>
		/// Checks if two <see cref="BoundingBox"/>s intersect.
		/// Returns true if they do, false otherwise.
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		bool test(const Models::BoundingBox & a, const Models::BoundingBox & b);
	};
}
