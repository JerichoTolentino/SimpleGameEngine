#pragma once
#include "../Models/BoundingBox.h"

namespace SimpleGameEngine::Logic
{
	class IntersectionTester
	{
	private:
		IntersectionTester();
	public:
		~IntersectionTester();

		/// <summary>
		/// Checks if two <see cref="BoundingBox"/>s intersect.
		/// Returns true if they do, false otherwise.
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		bool test(Models::BoundingBox a, Models::BoundingBox b);
	};
}
