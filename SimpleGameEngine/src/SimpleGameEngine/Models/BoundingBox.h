#pragma once
#include <GL/glew.h>
#include "../Math/Vec3.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	class BoundingBox
	{
	private:
		float minx, miny, minz, maxx, maxy, maxz;
		float mx, my, mz, mmx, mmy, mmz;	//These are the initial values that the bounding box gets when model is created
											//DO NOT CHANGE THESE
	public:
		BoundingBox();
		BoundingBox(float iminx, float iminy, float iminz, float imaxx, float imaxy, float imaxz);
		~BoundingBox();



		//TODO: This makes this base values equal to the others transformed values!!
		BoundingBox(const BoundingBox &other);
		//TODO: This makes this base values equal to the others transformed values!!
		BoundingBox& operator=(const BoundingBox &other);
		
		// WOW I was really bad at programming
		//int intersect(const Vec3 &ray, Camera *cam) const;

		//used original values for both (so scale wouldn't be saved)
		//void translate(const Vec3 &translate);
		//void scale(const Vec3 &scale);

		//scales first (from original vals), then translates (from scaled vals)
		void transform(const Vec3 &scale, const Vec3 &translate);

		//generate bounding box vertex array to render it on screen
		GLfloat* generateVertices() const;

		GLuint* generateIndices() const;

		float getMinX() const;
		float getMinY() const;
		float getMinZ() const;
		float getMaxX() const;
		float getMaxY() const;
		float getMaxZ() const;

		std::string toString() const;
	};
}
