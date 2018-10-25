/*
CLASS: MathUtils
AUTHOR: Jericho J. Tolentino
CREATED: May 9, 2017

A class that provides useful math functions.
*/

#pragma once
#include <math.h>
#include "Vec2.h"
#include "Vec3.h"
#define PI 3.14159265358979323846

class MathUtils
{
private:
	MathUtils();
public:
	~MathUtils();

	static float toRadians(float degrees);

	// FROM THINMATRIX!! //
	static float barryCentric(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, const Vec2 &pos);
};

